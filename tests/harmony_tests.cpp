#include "harmony_test.h"

using namespace harmony;

TestResultEnum SampleTest()
{
	auto a = glm::vec3(0.0f);
	auto b = glm::vec3(0.0f);

	TEST_ASSERT(a == b, "2 Identical Vec3s should match");
	return TestResultEnum::Pass;
}

TEST_APP_BEGIN("Core Engine")

ADD_TEST(SampleTest);

TEST_APP_END()