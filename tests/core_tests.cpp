#include "harmony_test.h"

using namespace harmony;
using TestBinaryAsset = AssetT<Vector<char>, AssetType::Binary>;
using TestBinaryIntermediate = AssetIntermediateT<Vector<char>, char, AssetType::Binary>;

TestResult AssetManagerTest1(Engine* e)
{
	AssetManager am;

	static bool load_called = false;
	static bool unload_called = false;

	auto test_load_func = [](const String& path) {
		mi_thread_init();
		load_called = true;
		auto data = Vector<char>{};
		TestBinaryAsset* asset = HNY_NEW(TestBinaryAsset, path, data);
		TestBinaryIntermediate* intermediate = HNY_NEW(TestBinaryIntermediate, asset, 0);
		return AssetLoadResult{ intermediate, {}, {} };
		mi_thread_done();
	};

	auto test_unload_func = [](Asset* a) { unload_called = true; };

	am.ProvideAssetTypeLoadFunction(
		AssetType::Binary,
		test_load_func,
		test_unload_func
	);

	auto handle = am.LoadAsset("test.bin", AssetType::Binary);

	while (am.AnyAssetsLoading())
	{
		am.Update();
	}

	am.UnloadAsset(handle);

	while (am.AnyAssetsUnloading())
	{
		am.Update();
	}
	
	TEST_ASSERT(load_called && unload_called, "Load functions provided but were not called when loading asset of specified type.")

	return TestResult::Pass();
}

TestResult AssetManagerTestDataLoaded(Engine* e)
{
	AssetManager am;

	auto test_load_func = [](const String& path) {
		Vector<char> data = Utils::LoadBinaryFromPath(path.c_str());
		TestBinaryAsset* asset = HNY_NEW(TestBinaryAsset, path, data);
		TestBinaryIntermediate* intermediate = HNY_NEW(TestBinaryIntermediate, asset, 0);
		return AssetLoadResult{ intermediate, {}, {} };
		};

	auto test_unload_func = [](Asset* a) {
		};

	am.ProvideAssetTypeLoadFunction(
		AssetType::Binary,
		test_load_func,
		test_unload_func
	);

	auto handle = am.LoadAsset("test.bin", AssetType::Binary);

	while (am.AnyAssetsLoading())
	{
		am.Update();
	}

	auto* bin_asset = am.GetAsset<TestBinaryAsset>(handle);

	auto bin_size = bin_asset->mData.size();

	TEST_ASSERT(bin_size == 16, "Data loaded was not the correct size");
	return TestResult::Pass();
}

TEST_APP_BEGIN_SUITE("Core Engine Functionality")

ADD_TEST(AssetManagerTest1)
ADD_TEST(AssetManagerTestDataLoaded)

TEST_APP_END_SUITE()