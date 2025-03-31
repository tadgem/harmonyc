#include "harmony_test.h"

using namespace harmony;

TestResult SampleTest()
{
	auto a = glm::vec3(0.0f);
	auto b = glm::vec3(0.0f);

	HNY_LOG_WARN(RED_PRINT_CODE "Hello Rachel! \n");

	TEST_ASSERT(a == b, "2 Identical Vec3s should match");
	return TestResult::Pass();
}

TEST_APP_BEGIN("Core Engine")

ADD_TEST(SampleTest);

TEST_APP_END()