#include "harmony_test.h"

using namespace harmony;


TestResult AssetManagerLoadUnloadFunctionsUsed(Engine* e)
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

TestResult SampleTest2(Engine* e)
{
	return TestResult::Pass();
}

//void* __cdecl operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line) {
//	printf("Unassigned Allocation!\n");
//	return mi_malloc(size);
//} void* __cdecl operator new[](size_t size, unsigned __int64, unsigned __int64, char const*, int, unsigned int, char const*, int) {
//	printf("Unassigned Allocation!\n");
//	return mi_malloc(size);
//}
//
//
//int main() {
//	TestHashMap<TestString, harmony::TestResult> sResults{}; 
//	TestString sCurrentTestName = ""; 
//	printf("\x1B[34m" "[harmony][info ] " "\x1B[0m" "%s Tests\n", "Core Engine Functionality");
//
//	{ 
//		harmony::Engine e = harmony::Engine::Init(1280, 720, false, 512 * 1024ULL * 1024ULL); 
//		harmony::Timer timer_AssetManagerLoadUnloadFunctionsUsed; 
//		auto result_AssetManagerLoadUnloadFunctionsUsed = AssetManagerLoadUnloadFunctionsUsed(&e); 
//		f64 time_taken_AssetManagerLoadUnloadFunctionsUsed = timer_AssetManagerLoadUnloadFunctionsUsed.ElapsedMillisecondsF(); 
//		result_AssetManagerLoadUnloadFunctionsUsed.mElapsedMs = time_taken_AssetManagerLoadUnloadFunctionsUsed; 
//		sResults["AssetManagerLoadUnloadFunctionsUsed"] = result_AssetManagerLoadUnloadFunctionsUsed; 
//	}
//
//	for (auto [name, result] : sResults) {
//		printf("\x1B[34m" "[harmony][info ] " "\x1B[0m" "Test %s, Result : %s, Time Taken : %f ms\n", name.c_str(), result.mResult == harmony::TestResultEnum::Fail ? "Fail" : "Pass", result.mElapsedMs); if (result.mResult != harmony::TestResultEnum::Pass) {
//			printf("\x1B[34m" "[harmony][info ] " "\x1B[0m" "    Test Message : %s\n", result.mResultMessage.c_str());
//		}
//	}
//};

TEST_APP_BEGIN_SUITE("Core Engine Functionality")

{
	harmony::Engine e = harmony::Engine::Init(1280, 720, false, 512 * 1024ULL * 1024ULL); harmony::Timer timer_AssetManagerLoadUnloadFunctionsUsed; auto result_AssetManagerLoadUnloadFunctionsUsed = AssetManagerLoadUnloadFunctionsUsed(&e); f64 time_taken_AssetManagerLoadUnloadFunctionsUsed = timer_AssetManagerLoadUnloadFunctionsUsed.ElapsedMillisecondsF(); result_AssetManagerLoadUnloadFunctionsUsed.mElapsedMs = time_taken_AssetManagerLoadUnloadFunctionsUsed; sResults["AssetManagerLoadUnloadFunctionsUsed"] = result_AssetManagerLoadUnloadFunctionsUsed;
};
ADD_TEST(SampleTest2)

TEST_APP_END_SUITE()