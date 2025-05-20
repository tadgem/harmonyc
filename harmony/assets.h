#pragma once
#include "Primitives.h"
#include "STL.h"

namespace harmony {
enum class AssetType : uint8 {
  Unknown,
  Model,
  Texture,
  Shader,
  Audio,
  Text,
  Binary
};

/// <summary>
/// Lightweight identifier for an arbitrary asset
/// use in collections for fast look up
/// </summary>
struct AssetHandle {
  AssetType mType;
  str_hash mPathHash;

  AssetHandle();
  AssetHandle(const String &p, const AssetType &type);

  bool operator==(const AssetHandle &o) const {
    return mType == o.mType && mPathHash == o.mPathHash;
  }

  bool operator<(const AssetHandle &o) const {
    return mType < o.mType && mPathHash < o.mPathHash;
  }
};

/// <summary>
/// Allow asset to be loaded by asset manager system
/// Giving concrete path and type of asset
/// </summary>
struct SerializableAssetHandle {
  AssetHandle mHandle;
  String mPath;

  SerializableAssetHandle(const String &p, const AssetType &type);
};

class Asset {
public:
  Asset(const String &path, const AssetType &type);
  virtual ~Asset() {};

  const String mPath;
  const AssetHandle mHandle;
};

template <typename _Ty, AssetType _AssetTypeEnum> class AssetT : public Asset {
public:
  _Ty mData;

  AssetT(const String &path, const _Ty &data)
      : Asset(path, _AssetTypeEnum), mData(data) {};

  ~AssetT() {};
};

/// <summary>
/// Allows intermediate data for assets that require submission in multiple
/// phases e.g. load texture from disk to ram -> transfer from ram to GPU Once
/// AssetIntermediate has finished, the asset is moved to the ready state.
/// </summary>
class AssetIntermediate {
public:
  Asset *mAssetData;
  AssetIntermediate(Asset *asset) : mAssetData(asset) {}

  virtual ~AssetIntermediate() {}
};

template <typename _AssetTy, typename _IntermediateType,
          AssetType _AssetTypeEnum>
class AssetIntermediateT : public AssetIntermediate {
public:
  _IntermediateType mIntermediate;

  AssetIntermediateT(Asset *data, const _IntermediateType &inter)
      : AssetIntermediate(data), mIntermediate(inter) {}

  AssetT<_AssetTy, _AssetTypeEnum> GetConcreteAsset() {
    return static_cast<AssetT<_AssetTy, _AssetTypeEnum>>(mAssetData);
  }
};

} // namespace harmony

/// <summary>
/// Allow AssetHandle to be used as a key in unordered_map
/// </summary>
template <> struct std::hash<harmony::AssetHandle> {
  size_t operator()(const harmony::AssetHandle &ah) const {
    return std::hash<int64>()(ah.mPathHash) ^
           std::hash<uint8>()(static_cast<uint8>(ah.mType));
  }
};
