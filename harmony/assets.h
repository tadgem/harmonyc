#pragma once
#include "primitives.h"

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

	struct AssetHandle
	{
		AssetType	mType;
		str_hash	mPathHash;

		bool operator==(const AssetHandle& o) const {
			return mType == o.mType && mPathHash == o.mPathHash;
		}

		bool operator<(const AssetHandle& o) const {
			return mType < o.mType && mPathHash < o.mPathHash;
		}

		static AssetHandle Invalid() { return { AssetType::Unknown, UINT64_MAX }; }
	};

	struct SerializableAssetHandle
	{

	};

}