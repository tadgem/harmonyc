#include "Assets.h"

namespace harmony
{
	SerializableAssetHandle::SerializableAssetHandle(const String& p, const AssetType& type)
		: mPath(p), mHandle(p, type)
	{

	}

	AssetHandle::AssetHandle() : mType(AssetType::Unknown), mPathHash(INT64_MAX) {}

	AssetHandle::AssetHandle(const String& p, const AssetType& type) :
		mPathHash(HashString(p)), mType(type)
	{

	}

	Asset::Asset(const String& path, const AssetType& type) :
		mPath(path), mHandle(path, type)
	{
	}

}