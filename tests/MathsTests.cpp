#include "HarmonyTest.h"

using namespace harmony;

/// <summary>
/// Vector Tests
/// </summary>
/// <param name="e"></param>
/// <returns></returns>

TestResult Vector2ElementAccess(Engine* e)
{
	Vector2 v = { 1.0f, 2.0f } ;

	TEST_ASSERT(v.x == 1.0f && v.y == 2.0f, "Element access in to Vector2 Failed.");

	return TestResult::Pass();
}

TestResult Vector2ElementArrayAccess(Engine* e)
{
	Vector2 v{ 1.0f, 2.0f };

	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f, "Array access in to Vector2 Failed.");

	return TestResult::Pass();
}

TestResult Vector2Magnitude(Engine* e)
{
	constexpr SCALAR_TYPE EXPECTED_MAGNITUDE = 2.23606797749979;

	Vector2 v {1.0f, 2.0f};

	TEST_ASSERT(FLOATING_POINT_ROUGHLY_EQUAL(v.Magnitude(), EXPECTED_MAGNITUDE), "Vector2 Magnitude is incorrect");

	return TestResult::Pass();
}

TestResult Vector2ScalarMultiplication(Engine* e)
{
	Vector2 v{ 1.0f, 2.0f };

	Vector2 scaled = v * 2.0f;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.x, 2.0) && 
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.y, 4.0), "Vector2 Scalar multiplication failed");

	return TestResult::Pass();
}

TestResult Vector2Multiplication(Engine* e)
{
	Vector2 v1{ 1.0f, 2.0f };
	Vector2 v2{ 1.0f, 2.0f };

	Vector2 added = v1 * v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added.x, 1.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.y, 4.0), "Vector2 multiplication failed");

	return TestResult::Pass();
}


TestResult Vector2Addition(Engine* e)
{
	Vector2 v1{ 1.0f, 2.0f };
	Vector2 v2{ 1.0f, 2.0f };

	Vector2 added = v1 + v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added.x, 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.y, 4.0), "Vector2 addition failed");

	return TestResult::Pass();
}

TestResult Vector2Subtraction(Engine* e)
{
	Vector2 v1{ 1.0f, 2.0f };
	Vector2 v2{ 1.0f, 2.0f };

	Vector2 subbed = v1 - v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(subbed.x, 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(subbed.y, 0.0), "Vector2 subtraction failed");

	return TestResult::Pass();
}

TestResult Vector3ElementAccess(Engine* e)
{
	Vector3 v{ 1.0f, 2.0f, 3.0f };

	TEST_ASSERT(v.x == 1.0f && v.y == 2.0f && v.z == 3.0f,  "Element access in to Vector3 Failed.");

	return TestResult::Pass();
}

TestResult Vector3ElementArrayAccess(Engine* e)
{
	Vector3 v{ 1.0f, 2.0f, 3.0f };


	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f && v[2] == 3.0f, "Array access in to Vector3 Failed.");

	return TestResult::Pass();
}

TestResult Vector3Magnitude(Engine* e)
{
	constexpr SCALAR_TYPE EXPECTED_MAGNITUDE = 3.741657386773941;

	Vector3 v{ 1.0f, 2.0f, 3.0f };


	TEST_ASSERT(FLOATING_POINT_ROUGHLY_EQUAL(v.Magnitude(), EXPECTED_MAGNITUDE), "Vector3 Magnitude is incorrect");
	return TestResult::Pass();
}

TestResult Vector3ScalarMultiplication(Engine* e)
{
	Vector3 v{ 1.0f, 2.0f, 3.0f };
	Vector3 scaled = v * 2.0f;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.x, 2.0) && 
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.y, 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.z, 6.0), "Vector3 Scalar multiplication failed");

	return TestResult::Pass();
}

TestResult Vector3Multiplication(Engine* e)
{
	Vector3 v1{ 1.0f, 2.0f, 3.0f };
	Vector3 v2{ 1.0f, 2.0f, 3.0f };

	Vector3 added = v1 * v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added.x, 1.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.y, 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.z, 9.0), "Vector3 multiplication failed");

	return TestResult::Pass();
}


TestResult Vector3Addition(Engine* e)
{
	Vector3 v1{ 1.0f, 2.0f, 3.0f };
	Vector3 v2{ 1.0f, 2.0f, 3.0f };

	Vector3 added = v1 + v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added.x, 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.y, 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.z, 6.0), "Vector3 addition failed");

	return TestResult::Pass();
}

TestResult Vector3Subtraction(Engine* e)
{
	Vector3 v1{ 1.0f, 2.0f, 3.0f };
	Vector3 v2{ 1.0f, 2.0f, 3.0f };

	Vector3 added = v1 - v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added.x, 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.y, 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.z, 0.0), "Vector3 subtraction failed");

	return TestResult::Pass();
}


TestResult Vector4ElementAccess(Engine* e)
{
	Vector4 v{ 1.0f, 2.0f, 3.0f, 4.0f };

	TEST_ASSERT(v.x == 1.0f && v.y == 2.0f && v.z == 3.0f && v.w == 4.0f, "Element access in to Vector3 Failed.");

	return TestResult::Pass();
}

TestResult Vector4ElementArrayAccess(Engine* e)
{
	Vector4 v{ 1.0f, 2.0f, 3.0f, 4.0f };

	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f && v[2] == 3.0f && v[3] == 4.0f, "Array access in to Vector3 Failed.");

	return TestResult::Pass();
}

TestResult Vector4Magnitude(Engine* e)
{
	constexpr SCALAR_TYPE EXPECTED_MAGNITUDE = 5.4772257804870605;
	Vector4 v{ 1.0f, 2.0f, 3.0f, 4.0f };
	auto mag = v.Magnitude();
	TEST_ASSERT(FLOATING_POINT_ROUGHLY_EQUAL(v.Magnitude(), EXPECTED_MAGNITUDE), "Vector4 Magnitude is incorrect");
	return TestResult::Pass();
}

TestResult Vector4ScalarMultiplication(Engine* e)
{
	Vector4 v{ 1.0f, 2.0f, 3.0f, 4.0f };

	Vector4 scaled = v * 2.0f;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.x, 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.y, 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.z, 6.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled.w, 8.0), "Vector4 Scalar multiplication failed");

	return TestResult::Pass();
}


TestResult Vector4Multiplication(Engine* e)
{
	Vector4 v1{ 1.0f, 2.0f, 3.0f, 4.0f };
	Vector4 v2{ 1.0f, 2.0f, 3.0f, 4.0f };

	Vector4 added = v1 * v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added.x, 1.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.y, 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.z, 9.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.w, 16.0), "Vector4 multiplication failed");

	return TestResult::Pass();
}


TestResult Vector4Addition(Engine* e)
{
	Vector4 v1{ 1.0f, 2.0f, 3.0f, 4.0f };
	Vector4 v2{ 1.0f, 2.0f, 3.0f, 4.0f };

	Vector4 added = v1 + v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added.x, 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.y, 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.z, 6.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.w, 8.0), "Vector4 addition failed");

	return TestResult::Pass();
}

TestResult Vector4Subtraction(Engine* e)
{
	Vector4 v1{ 1.0f, 2.0f, 3.0f, 4.0f };
	Vector4 v2{ 1.0f, 2.0f, 3.0f, 4.0f };
   
	Vector4 added = v1 - v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added.x, 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.y, 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.z, 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added.w, 0.0), "Vector4 subtraction failed");

	return TestResult::Pass();
}

/// <summary>
/// Matrix tests
/// </summary>
TestResult Matrix2x2ElementAccess(Engine* e)
{
	Matrix2x2 a { 1,3,2,4 };
	
	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(a[0][0], 1) && 
		FLOATING_POINT_ROUGHLY_EQUAL(a[0][1], 3) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[1][0], 2) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[1][1], 4)
		, "Element access in to Matrix2x2 Failed.");

	return TestResult::Pass();
}

TestResult Matrix2x2Multiplication(Engine* e)
{
	Matrix2x2 a{ 1,3,2,4 };
	Matrix2x2 b{ 5,7,6,8 };
	Matrix2x2 c = a * b;
	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][0], 19) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][1], 43) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][0], 22) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][1], 50)
		, "Matrix2x2 multiplication Failed.");

	return TestResult::Pass();
}


TEST_APP_BEGIN_SUITE("Maths", MEGABYTES(32))
// Vector Tests
//ADD_TEST(Vector2ElementAccess)
//ADD_TEST(Vector2ElementArrayAccess)
//ADD_TEST(Vector2Magnitude)
//ADD_TEST(Vector2ScalarMultiplication)
//ADD_TEST(Vector2Multiplication)
//ADD_TEST(Vector2Addition)
//ADD_TEST(Vector2Subtraction)
//ADD_TEST(Vector3ElementAccess)
//ADD_TEST(Vector3ElementArrayAccess)
//ADD_TEST(Vector3Magnitude)
//ADD_TEST(Vector3ScalarMultiplication)
//ADD_TEST(Vector3Multiplication)
//ADD_TEST(Vector3Addition)
//ADD_TEST(Vector3Subtraction)
//ADD_TEST(Vector4ElementAccess)
//ADD_TEST(Vector4ElementArrayAccess)
//ADD_TEST(Vector4Magnitude)
//ADD_TEST(Vector4ScalarMultiplication)
//ADD_TEST(Vector4Multiplication)
//ADD_TEST(Vector4Addition)
//ADD_TEST(Vector4Subtraction)

// Matrix Tests

ADD_TEST(Matrix2x2ElementAccess)
ADD_TEST(Matrix2x2Multiplication)
TEST_APP_END_SUITE()