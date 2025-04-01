#pragma once
#include "Assets.h"
#include "Primitives.h"

namespace harmony {
using AssetIntermediateCallback = void (*)(AssetIntermediate *);
using OnAssetLoadedCallback = void (*)(Asset *);
using OnAssetUnloadedCallback = void (*)(Asset *);
enum class AssetLoadProgress { NotLoaded, Loading, Loaded, Unloading };

struct AssetLoadInfo {
  String mPath;
  AssetType mType;

  bool operator==(const AssetLoadInfo &o) const {
    return mPath == o.mPath && mType == o.mType;
  }

  void operator=(const AssetLoadInfo &o) {
    mPath = o.mPath;
    mType = o.mType;
  }

  bool operator<(const AssetLoadInfo &o) const {
    return mPath.size() < o.mPath.size();
  }

  AssetHandle ToHandle();
};

struct AssetLoadResult {
  AssetIntermediate *mLoadedAssetIntermediate = nullptr;
  // additional assets that may be required to completely load this asset
  Vector<AssetLoadInfo> mNewAssetsToLoad;
  // synchronous tasks associated with this asset e.g. submit texture mem to GPU
  // in openGL
  Vector<AssetIntermediateCallback> mSynchronousAssetCallbacks;
};

using LoadAssetCallback = AssetLoadResult (*)(const String &path);
using UnloadAssetCallback = void (*)(Asset *a);

class AssetManager {
public:
  AssetManager() = default;

  bool ProvideAssetTypeLoadFunction(const AssetType &type,
                                    LoadAssetCallback onLoad,
                                    UnloadAssetCallback onUnload);

  AssetHandle LoadAsset(const String &path, const AssetType &assetType,
                        OnAssetLoadedCallback onAssetLoaded = nullptr);

  void UnloadAsset(const AssetHandle &handle);
  Asset *GetAsset(const AssetHandle &handle);
  AssetLoadProgress GetAssetLoadProgress(const AssetHandle &handle);

  bool AnyAssetsLoading();
  bool AnyAssetsUnloading();

  /// <summary>
  /// Synchronous calls that will wait until
  /// all pending asset manager loads /unloads are finished
  /// </summary>
  void WaitAllAssets();
  void WaitAllUnloads();
  void UnloadAllAssets();


  void Update();
  void Shutdown();

protected:
  friend struct Engine;
  HashMap<AssetType, Pair<LoadAssetCallback, UnloadAssetCallback>>
      pAssetTypeLoadFuncs;
  HashMap<AssetHandle, Future<AssetLoadResult>> pPendingLoadTasks;
  HashMap<AssetHandle, Unique<Asset>> pLoadedAssets;
  HashMap<AssetHandle, AssetLoadResult> pPendingSyncLoadCallbacks;
  HashMap<AssetHandle, OnAssetUnloadedCallback> pPendingUnloadCallbacks;
  HashMap<AssetHandle, OnAssetLoadedCallback> pOnAssetLoadedCallbacks;
  Vector<AssetLoadInfo> pQueuedLoads;

  static constexpr uint16 pCallbackTasksPerUpdate = 1;
  static constexpr uint16 pMaxAsyncTasksInFlight = 8;


  void HandleCallbacks();

  void HandlePendingLoads();

  void HandleAsyncTasks();

  void DispatchAssetLoadTask(const AssetHandle &handle, AssetLoadInfo &info);

private:
  void TransitionAssetToLoaded(const AssetHandle &handle,
                               Asset *asset_to_transition);
};
} // namespace harmony
