#pragma once
#include "Primitives.h"
#include "STL.h"

namespace harmony
{
	enum class AssetType : uint8
	{
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
	struct AssetHandle
	{
		AssetType	mType;
		str_hash	mPathHash;

		AssetHandle();
		AssetHandle(const String& p, const AssetType& type);

		bool operator==(const AssetHandle& o) const {
			return mType == o.mType && mPathHash == o.mPathHash;
		}

		bool operator<(const AssetHandle& o) const {
			return mType < o.mType && mPathHash < o.mPathHash;
		}
	};

	/// <summary>
	/// Allow asset to be loaded by asset manager system
	/// Giving concrete path and type of asset
	/// </summary>
	struct SerializableAssetHandle
	{
		AssetHandle mHandle;
		String		mPath;

		SerializableAssetHandle(const String& p, const AssetType& type);
	};

	class Asset
	{
	public:

	};

}