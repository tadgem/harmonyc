#include "harmony_test.h"

using namespace harmony;

TestResult SampleTest()
{
	auto a = glm::vec3(0.0f);
	auto b = glm::vec3(1.0f);

	float f = 1.4f;
	String s = "Blah Bleh Blue";
	HNY_LOG_WARN(RED_PRINT_CODE "Hello Aaron!" CYAN_PRINT_CODE "%s : %f\n", s.c_str(), f);


	TEST_ASSERT(a == b, "2 Identical Vec3s should match");
	return TestResult::Pass();
}

TestResult SampleTest2()
{
	return TestResult::Pass();
}

TEST_APP_BEGIN("Core Engine")

ADD_TEST(SampleTest);
ADD_TEST(SampleTest2)
TEST_APP_END()