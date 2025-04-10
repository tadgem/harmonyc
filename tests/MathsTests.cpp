#include "HarmonyTest.h"

using namespace harmony;

TestResult Vector2ElementAccess(Engine* e)
{
	Vector2 v(1.0f, 2.0f);

	TEST_ASSERT(v.x == 1.0f && v.y == 2.0f, "Element access in to Vector2 Failed.");

	return TestResult::Pass();
}

TestResult Vector2ElementArrayAccess(Engine* e)
{
	Vector2 v(1.0f, 2.0f);

	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f, "Array access in to Vector2 Failed.");

	return TestResult::Pass();
}

TestResult Vector2Magnitude(Engine* e)
{
	constexpr SCALAR_TYPE EXPECTED_MAGNITUDE = 2.23606797749979;

	Vector2 v(1.0f, 2.0f);

	TEST_ASSERT(FLOATING_POINT_ROUGHLY_EQUAL(v.Magnitude(), EXPECTED_MAGNITUDE), "Vector2 Magnitude is incorrect");

	return TestResult::Pass();
}

TestResult Vector2ScalarMultiplication(Engine* e)
{
	Vector2 v(1.0f, 2.0f);

	Vector2 scaled = v * 2.0f;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.x, 2.0) && 
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.y, 4.0), "Vector2 Scalar multiplication failed");

	return TestResult::Pass();
}

TestResult Vector3ElementAccess(Engine* e)
{
	Vector3 v(1.0f, 2.0f, 3.0f);

	TEST_ASSERT(v.x == 1.0f && v.y == 2.0f && v.z == 3.0f,  "Element access in to Vector3 Failed.");

	return TestResult::Pass();
}

TestResult Vector3ElementArrayAccess(Engine* e)
{
	Vector3 v(1.0f, 2.0f, 3.0f);

	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f && v[2] == 3.0f, "Array access in to Vector3 Failed.");

	return TestResult::Pass();
}

TestResult Vector3Magnitude(Engine* e)
{
	constexpr SCALAR_TYPE EXPECTED_MAGNITUDE = 3.741657386773941;

	Vector3 v(1.0f, 2.0f, 3.0f);

	TEST_ASSERT(FLOATING_POINT_ROUGHLY_EQUAL(v.Magnitude(), EXPECTED_MAGNITUDE), "Vector3 Magnitude is incorrect");
	return TestResult::Pass();
}

TestResult Vector3ScalarMultiplication(Engine* e)
{
	Vector3 v(1.0f, 2.0f, 3.0f);

	Vector3 scaled = v * 2.0f;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.x, 2.0) && 
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.y, 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.z, 6.0), "Vector3 Scalar multiplication failed");

	return TestResult::Pass();
}

TestResult Vector4ElementAccess(Engine* e)
{
	Vector4 v(1.0f, 2.0f, 3.0f, 4.0f);

	TEST_ASSERT(v.x == 1.0f && v.y == 2.0f && v.z == 3.0f && v.w == 4.0f, "Element access in to Vector3 Failed.");

	return TestResult::Pass();
}

TestResult Vector4ElementArrayAccess(Engine* e)
{
	Vector4 v(1.0f, 2.0f, 3.0f, 4.0f);

	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f && v[2] == 3.0f && v[3] == 4.0f, "Array access in to Vector3 Failed.");

	return TestResult::Pass();
}

TestResult Vector4Magnitude(Engine* e)
{
	constexpr SCALAR_TYPE EXPECTED_MAGNITUDE = 5.4772257804870605;
	Vector4 v(1.0f, 2.0f, 3.0f, 4.0f);
	auto mag = v.Magnitude();
	TEST_ASSERT(FLOATING_POINT_ROUGHLY_EQUAL(v.Magnitude(), EXPECTED_MAGNITUDE), "Vector4 Magnitude is incorrect");
	return TestResult::Pass();
}

TestResult Vector4ScalarMultiplication(Engine* e)
{
	Vector4 v(1.0f, 2.0f, 3.0f, 4.0f);

	Vector4 scaled = v * 2.0f;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.x, 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.y, 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.z, 6.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.z, 8.0), "Vector4 Scalar multiplication failed");

	return TestResult::Pass();
}

TEST_APP_BEGIN_SUITE("Maths", MEGABYTES(32))

ADD_TEST(Vector2ElementAccess)
ADD_TEST(Vector2ElementArrayAccess)
ADD_TEST(Vector2Magnitude)
ADD_TEST(Vector2ScalarMultiplication)
ADD_TEST(Vector3ElementAccess)
ADD_TEST(Vector3ElementArrayAccess)
ADD_TEST(Vector3Magnitude)
ADD_TEST(Vector3ScalarMultiplication)
ADD_TEST(Vector4ElementAccess)
ADD_TEST(Vector4ElementArrayAccess)
ADD_TEST(Vector4Magnitude)
ADD_TEST(Vector4ScalarMultiplication)

TEST_APP_END_SUITE()