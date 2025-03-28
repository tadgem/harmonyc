#pragma once
#include "Primitives.h"
#include "Assets.h"



namespace harmony
{
	using AssetIntermediateCallback		= void (*)(AssetIntermediate*);
	using AssetLoadedCallback	= void (*)(Asset*);
	using AssetUnloadCallback	= void (*)(Asset*);
	
	enum class AssetLoadProgress { NotLoaded, Loading, Loaded, Unloading };

	struct AssetLoadInfo {
		String		mPath;
		AssetType	mType;

		bool operator==(const AssetLoadInfo& o) const {
			return mPath == o.mPath && mType== o.mType;
		}

		void operator=(const AssetLoadInfo& o)
		{
			mPath = o.mPath;
			mType = o.mType;
		}

		bool operator<(const AssetLoadInfo& o) const {
			return mPath.size() < o.mPath.size();
		}

		AssetHandle ToHandle();
	};

	struct AssetLoadResult {
		AssetIntermediate*					mLoadedAssetIntermediate = nullptr;
		// additional assets that may be required to completely load this asset
		Vector<AssetLoadInfo>				mNewAssetsToLoad;
		// synchronous tasks associated with this asset e.g. submit texture mem to GPU in openGL
		Vector<AssetIntermediateCallback>	mSynchronousAssetCallbacks;

	};

	class AssetManager 
	{
		AssetManager();

		AssetHandle LoadAsset(
			const String& path,
			const AssetType& assetType,
			AssetIntermediateCallback onAssetLoaded = nullptr);

		void				UnloadAsset(const AssetHandle& handle);
		Asset*				GetAsset(const AssetHandle& handle);
		AssetLoadProgress	GetAssetLoadProgress(const AssetHandle& handle);

		bool				AnyAssetsLoading();
		bool				AnyAssetsUnloading();

		/// <summary>
		/// Synchronous calls that will wait until
		/// all pending asset manager loads /unloads are finished
		/// </summary>
		void WaitAllAssets();
		void WaitAllUnloads();
		void UnloadAllAssets();
		
	protected:
		friend struct Engine;
		HashMap<AssetHandle, Future<AssetLoadResult>>	pPendingLoadTasks;
		HashMap<AssetHandle, Unique<Asset>>				pLoadedAssets;
		HashMap<AssetHandle, AssetLoadResult>			pPendingSyncLoadCallbacks;
		HashMap<AssetHandle, AssetUnloadCallback>		pPendingUnloadCallbacks;
		HashMap<AssetHandle, AssetIntermediateCallback>	pOnAssetLoadedCallbacks;
		Vector<AssetLoadInfo>							pQueuedLoads;
		
		static constexpr uint16 pCallbackTasksPerUpdate = 1;
		static constexpr uint16 pMaxAsyncTasksInFlight  = 8;
		
		void Update();

		void Shutdown();

		void HandleCallbacks();

		void HandlePendingLoads();

		void HandleAsyncTasks();

		void DispatchAssetLoadTask(const AssetHandle& handle, AssetLoadInfo& info);

	private:
		void TransitionAssetToLoaded(const AssetHandle& handle,
			Asset* asset_to_transition);

	};
}