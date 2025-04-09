#include "HarmonyTest.h"

using namespace harmony;
using	TestBinaryAsset			= AssetT<Vector<char>, AssetType::Binary>;
using	TestBinaryIntermediate	= AssetIntermediateT<Vector<char>, char, AssetType::Binary>;

struct	TestComponent
{
	int		x;
	float	y;
	double	z;
};

TestResult AssetManagerProvidedFunctionsUsed(Engine* e)
{
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

	e->mAssetManager->ProvideAssetTypeLoadFunction(
		AssetType::Binary,
		test_load_func,
		test_unload_func
	);

	auto handle = e->mAssetManager->LoadAsset("test.bin", AssetType::Binary);

	while (e->mAssetManager->AnyAssetsLoading())
	{
		e->mAssetManager->Update();
	}

	e->mAssetManager->UnloadAsset(handle);

	while (e->mAssetManager->AnyAssetsUnloading())
	{
		e->mAssetManager->Update();
	}
	
	TEST_ASSERT(load_called && unload_called, "Load functions provided but were not called when loading asset of specified type.")

	return TestResult::Pass();
}

TestResult AssetManagerTestDataLoaded(Engine* e)
{
	auto test_load_func = [](const String& path) {
		Vector<char> data = Utils::LoadBinaryFromPath(path.c_str());
		TestBinaryAsset* asset = HNY_NEW(TestBinaryAsset, path, data);
		TestBinaryIntermediate* intermediate = HNY_NEW(TestBinaryIntermediate, asset, 0);
		return AssetLoadResult{ intermediate, {}, {} };
		};

	auto test_unload_func = [](Asset* a) {
		};

	e->mAssetManager->ProvideAssetTypeLoadFunction(
		AssetType::Binary,
		test_load_func,
		test_unload_func
	);

	auto handle = e->mAssetManager->LoadAsset("test.bin", AssetType::Binary);

	while (e->mAssetManager->AnyAssetsLoading())
	{
		e->mAssetManager->Update();
	}

	auto* bin_asset = e->mAssetManager->GetAsset<TestBinaryAsset>(handle);

	auto bin_size = bin_asset->mData.size();

	TEST_ASSERT(bin_size == 16, "Data loaded was not the correct size");
	return TestResult::Pass();
}

TestResult CanCreateAndDestroyEntity(Engine* e)
{
	// Note: This test adds a dummy component
	// FLECS seemingly doesnt allocate any space
	// for a component-less entity.
	Scene s = Scene("Test");

	auto entity = s.CreateEntity();
	entity.AddComponent<TestComponent>();

	int entityCount = s.mWorld.count<TestComponent>();
	TEST_ASSERT(entityCount == 1, "Expected an entity to have been created");

	entity.Destroy();

	TEST_ASSERT(s.mWorld.count<TestComponent>() == 0, "Expected an entity to have been destroyed");

	return TestResult::Pass();
}

TestResult CanMutateComponentData(Engine* e)
{
	// Note: This test adds a dummy component
	// FLECS seemingly doesnt allocate any space
	// for a component-less entity.
	Scene s = Scene("Test");
	constexpr int EXPECTED_RESULT = 12345;

	auto entity = s.CreateEntity();
	
	{
		TestComponent& tc = entity.AddComponent<TestComponent>();
		tc.x = EXPECTED_RESULT;
	}
	
	TestComponent& tc = entity.GetComponent<TestComponent>();
	
	TEST_ASSERT(tc.x = EXPECTED_RESULT, "Component was not mutated as expected");

	return TestResult::Pass();
}

TestResult CanIterateOverComponentData(Engine* e)
{
	Scene s = Scene("Test");
	auto entity = s.CreateEntity();
	TestComponent& tc = entity.AddComponent<TestComponent>();

	bool function_called = false;
	
	auto testComponentFunction = [&function_called](flecs::iter& it, size_t, TestComponent& tc)
	{
		function_called = true;
	};

	s.mWorld.system<TestComponent>().
		each(testComponentFunction);

	s.mWorld.progress();

	TEST_ASSERT(function_called, 
		"Provided a system callback for ecs world, progressed world, but function was not called");

	return TestResult::Pass();
}

TEST_APP_BEGIN_SUITE("Core Engine Functionality")

ADD_TEST(AssetManagerProvidedFunctionsUsed)
ADD_TEST(AssetManagerTestDataLoaded)
ADD_TEST(CanCreateAndDestroyEntity)
ADD_TEST(CanMutateComponentData)
ADD_TEST(CanIterateOverComponentData)

TEST_APP_END_SUITE()