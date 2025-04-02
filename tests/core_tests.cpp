#include "harmony_test.h"

using namespace harmony;


TestResult AssetManagerTest1(Engine* e)
{
	AssetManager am;
	using TestBinaryAsset = AssetT<char, AssetType::Binary>;
	using TestBinaryIntermediate = AssetIntermediateT<char, char, AssetType::Binary>;
	static bool load_called = false;
	static bool unload_called = false;

	auto test_load_func = [](const String& path) { 
		load_called = true;
		TestBinaryAsset* asset = HNY_NEW(TestBinaryAsset, path, 0);
		TestBinaryIntermediate* intermediate = HNY_NEW(TestBinaryIntermediate, asset, 0);
		return AssetLoadResult{ intermediate, {}, {} };
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

TestResult AssetManagerTest2(Engine* e)
{
	return AssetManagerTest1(e);
}

TestResult AssetManagerTest3(Engine* e)
{
	return AssetManagerTest1(e);
}
TestResult AssetManagerTest4(Engine* e)
{
	return AssetManagerTest1(e);
}
TestResult AssetManagerTest5(Engine* e)
{
	return AssetManagerTest1(e);
}
TestResult AssetManagerTest6(Engine* e)
{
	return AssetManagerTest1(e);
}
TestResult AssetManagerTest7(Engine* e)
{
	return AssetManagerTest1(e);
}
TestResult AssetManagerTest8(Engine* e)
{
	return AssetManagerTest1(e);
}
TestResult AssetManagerTest9(Engine* e)
{
	return AssetManagerTest1(e);
}
TestResult AssetManagerTest10(Engine* e)
{
	return AssetManagerTest1(e);
}
TestResult AssetManagerTest11(Engine* e)
{
	return AssetManagerTest1(e);
}
TestResult AssetManagerTest12(Engine* e)
{
	return AssetManagerTest1(e);
}
TestResult AssetManagerTest13(Engine* e)
{
	return AssetManagerTest1(e);
}
TestResult AssetManagerTest14(Engine* e)
{
	return AssetManagerTest1(e);
}

TEST_APP_BEGIN_SUITE("Core Engine Functionality")

ADD_TEST(AssetManagerTest1)
ADD_TEST(AssetManagerTest2)
ADD_TEST(AssetManagerTest3)
ADD_TEST(AssetManagerTest4)
ADD_TEST(AssetManagerTest5)
ADD_TEST(AssetManagerTest6)
ADD_TEST(AssetManagerTest7)
ADD_TEST(AssetManagerTest8)
ADD_TEST(AssetManagerTest9)
ADD_TEST(AssetManagerTest10)
ADD_TEST(AssetManagerTest11)
ADD_TEST(AssetManagerTest12)
ADD_TEST(AssetManagerTest13)
ADD_TEST(AssetManagerTest14)

TEST_APP_END_SUITE()