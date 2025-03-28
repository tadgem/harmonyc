#include "AssetManager.h"
#include "Assert.h"
namespace harmony
{
	AssetHandle AssetLoadInfo::ToHandle()
	{
		return AssetHandle(mPath, mType);
	}

	AssetHandle AssetManager::LoadAsset(const String& path, const AssetType& assetType, AssetIntermediateCallback onAssetLoaded)
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
        // TODO: impl.

        HNY_ASSERT(false, "Should not be reached");
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
        HNY_ASSERT_NOT_REACHED();
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
        HNY_ASSERT_NOT_REACHED();
    }

    void AssetManager::DispatchAssetLoadTask(const AssetHandle& handle, AssetLoadInfo& info)
    {
        HNY_ASSERT_NOT_REACHED();
    }

    void AssetManager::TransitionAssetToLoaded(const AssetHandle& handle, Asset* asset_to_transition)
    {
        HNY_ASSERT_NOT_REACHED();
    }
    
}
