#include "AssetManager.h"
#include "Assert.h"
namespace harmony
{
	AssetHandle AssetLoadInfo::ToHandle()
	{
		return AssetHandle(mPath, mType);
	}

	AssetHandle AssetManager::LoadAsset(const String& path, const AssetType& assetType, AssetLoadedCallback onAssetLoaded)
	{
        if (!Filesystem::exists(path.c_str())) {
            return {};
        }

        String wd (Filesystem::current_path().string().c_str());
        String tmp_path = path;
        if (path.find(wd) != std::string::npos) {
            tmp_path.erase(tmp_path.find(wd), wd.length());

            for (int i = 0; i < 2; i++) {
                if (tmp_path[0] != '\\' && tmp_path[0] != '/') {
                    break;
                }
                tmp_path.erase(0, 1);
            }
        }

        AssetHandle handle(tmp_path, assetType);
        AssetLoadInfo load_info{ tmp_path, assetType };

        auto it = stl::find(pQueuedLoads.begin(), pQueuedLoads.end(), load_info);

        for (auto& queued_load : pQueuedLoads) {
            if (load_info == queued_load) {
                return queued_load.ToHandle();
            }
        }

        pQueuedLoads.push_back(load_info);

        if (onAssetLoaded != nullptr) {
            pOnAssetLoadedCallbacks.emplace(handle, onAssetLoaded);
        }

        return handle;
	}

    void AssetManager::UnloadAsset(const AssetHandle& handle)
    {
        if (pLoadedAssets.find(handle) == pLoadedAssets.end()) {
            return;
        }

        switch (handle.mType) {
        case AssetType::Model:
            pPendingUnloadCallbacks.emplace(handle, nullptr);
            break;
        case AssetType::Texture:
            pPendingUnloadCallbacks.emplace(handle, nullptr);
            break;
        case AssetType::Shader:
            pPendingUnloadCallbacks.emplace(handle, nullptr);
            break;
        default:
            break;
        }
    }

    Asset* AssetManager::GetAsset(const AssetHandle& handle)
    {
        if (pLoadedAssets.find(handle) == pLoadedAssets.end()) {
            return nullptr;
        }

        return pLoadedAssets[handle].get();
    }

    AssetLoadProgress AssetManager::GetAssetLoadProgress(const AssetHandle& handle)
    {
        for (auto& queued : pQueuedLoads) {
            if (queued.ToHandle() == handle) {
                return AssetLoadProgress::Loading;
            }
        }

        if (pPendingLoadTasks.find(handle) != pPendingLoadTasks.end() ||
            pPendingSyncLoadCallbacks.find(handle) != pPendingSyncLoadCallbacks.end()) {
            return AssetLoadProgress::Loading;
        }

        if (pPendingUnloadCallbacks.find(handle) !=
            pPendingUnloadCallbacks.end()) {
            return AssetLoadProgress::Unloading;
        }

        if (pLoadedAssets.find(handle) != pLoadedAssets.end()) {
            return AssetLoadProgress::Loaded;
        }

        return AssetLoadProgress::NotLoaded;
    }
    
    bool AssetManager::AnyAssetsLoading()
    {
        return !pPendingLoadTasks.empty() || !pPendingSyncLoadCallbacks.empty() ||
            !pPendingUnloadCallbacks.empty() || !pQueuedLoads.empty();
    }

    bool AssetManager::AnyAssetsUnloading()
    {
        return !pPendingUnloadCallbacks.empty();
    }

    void AssetManager::WaitAllAssets()
    {
        while (AnyAssetsLoading()) {
            Update();
        }
    }

    void AssetManager::WaitAllUnloads()
    {
        while (AnyAssetsUnloading()) {
            Update();
        }
    }

    void AssetManager::UnloadAllAssets()
    {
        Vector<AssetHandle> assetsRemaining{};

        for (auto& [handle, asset] : pLoadedAssets) {
            assetsRemaining.push_back(handle);
        }

        for (auto& handle : assetsRemaining) {
            UnloadAsset(handle);
        }

        WaitAllUnloads();
    }

    void AssetManager::Update()
    {
        if (!AnyAssetsLoading()) {
            return;
        }

        HandleCallbacks();
        HandlePendingLoads();
        HandleAsyncTasks();
    }

    void AssetManager::Shutdown()
    {
        WaitAllAssets();
        WaitAllUnloads();
        UnloadAllAssets();
    }

    void AssetManager::HandleCallbacks()
    {
        uint16 processedCallbacks = 0;
        Vector<AssetHandle> clears;

        for (auto& [handle, asset] : pPendingSyncLoadCallbacks) {
            if (processedCallbacks == pCallbackTasksPerUpdate)
                break;

            for (uint16 i = 0; i < pCallbackTasksPerUpdate - processedCallbacks; i++) {
                if (i >= asset.mSynchronousAssetCallbacks.size())
                    break;
                asset.mSynchronousAssetCallbacks.back()(
                    asset.mLoadedAssetIntermediate);
                asset.mSynchronousAssetCallbacks.pop_back();
                processedCallbacks++;
            }

            if (asset.mSynchronousAssetCallbacks.empty()) {
                clears.push_back(handle);
            }
        }
        for (auto& handle : clears) {
            TransitionAssetToLoaded(handle,
                pPendingSyncLoadCallbacks[handle]
                .mLoadedAssetIntermediate->mAssetData);
            delete pPendingSyncLoadCallbacks[handle].mLoadedAssetIntermediate;
            pPendingSyncLoadCallbacks.erase(handle);
        }
        clears.clear();

        for (auto& [handle, callback] : pPendingUnloadCallbacks) {
            if (processedCallbacks == pCallbackTasksPerUpdate)
                break;
            callback(pLoadedAssets[handle].get());
            clears.push_back(handle);
            processedCallbacks++;
        }

        for (auto& handle : clears) {
            pPendingUnloadCallbacks.erase(handle);
            pLoadedAssets[handle].reset();
            pLoadedAssets.erase(handle);
        }
    }

    void AssetManager::HandlePendingLoads()
    {
        while (pPendingLoadTasks.size() <= pMaxAsyncTasksInFlight && !pQueuedLoads.empty()) {
            auto& info = pQueuedLoads.front();
            DispatchAssetLoadTask(info.ToHandle(), info);
            pQueuedLoads.erase(pQueuedLoads.begin());
        }
    }

    void AssetManager::HandleAsyncTasks()
    {
        Vector<AssetHandle> finished;
        for (auto& [handle, future] : pPendingLoadTasks) {
            if (IsFutureReady(future)) {
                finished.push_back(handle);
            }
        }

        for (auto& handle : finished) {
            AssetLoadResult asyncReturn = pPendingLoadTasks[handle].get();
            // enqueue new loads
            for (auto& newLoad : asyncReturn.mNewAssetsToLoad) {
                LoadAsset(newLoad.mPath, newLoad.mType);
            }

            if (asyncReturn.mSynchronousAssetCallbacks.empty() &&
                asyncReturn.mLoadedAssetIntermediate == nullptr) {
                TransitionAssetToLoaded(
                    handle, asyncReturn.mLoadedAssetIntermediate->mAssetData);
                delete asyncReturn.mLoadedAssetIntermediate;
                asyncReturn.mLoadedAssetIntermediate = nullptr;
            }
            else {
                pPendingSyncLoadCallbacks.emplace(handle, asyncReturn);
            }

            pPendingLoadTasks.erase(handle);
        }
    }

    AssetLoadResult LoadModel(const String& path)
    {
        return {};
    }

    AssetLoadResult LoadTexture(const String& path)
    {
        return {};
    }

    AssetLoadResult LoadShader(const String& path)
    {
        return {};
    }

    void AssetManager::DispatchAssetLoadTask(const AssetHandle& handle, AssetLoadInfo& info)
    {
        switch (info.mType) {
        case AssetType::Model:
            pPendingLoadTasks.emplace(
                handle, stl::move(std::async(std::launch::async,
                    LoadModel, info.mPath)));
            break;
        case AssetType::Texture:
            pPendingLoadTasks.emplace(
                handle, stl::move(std::async(std::launch::async,
                    LoadTexture, info.mPath)));
            break;
        case AssetType::Shader:
            pPendingLoadTasks.emplace(
                handle, std::move(std::async(std::launch::async,
                    LoadShader, info.mPath)));
            break;
        default:
            HNY_ASSERT_NOT_REACHED();
            break;
        }
    }

    void AssetManager::TransitionAssetToLoaded(const AssetHandle& handle, Asset* asset_to_transition)
    {
        pLoadedAssets.emplace(
            handle, std::move(Unique<Asset>(asset_to_transition)));

        // TODO: Log Asset Loaded
        if (pOnAssetLoadedCallbacks.find(handle) == pOnAssetLoadedCallbacks.end()) {
            return;
        }

        for (auto& [ah, loaded_callback] : pOnAssetLoadedCallbacks) {
            loaded_callback(pLoadedAssets[ah].get());
        }

        pOnAssetLoadedCallbacks.erase(handle);
    }
    
}
