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

	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f, "Element access in to Vector2 Failed.");

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
	constexpr f32 EXPECTED_MAGNITUDE = 2.23606797749979;

	Vector2 v {1.0f, 2.0f};

	TEST_ASSERT(FLOATING_POINT_ROUGHLY_EQUAL(v.Magnitude(), EXPECTED_MAGNITUDE), "Vector2 Magnitude is incorrect");

	return TestResult::Pass();
}

TestResult Vector2ScalarMultiplication(Engine* e)
{
	Vector2 v{ 1.0f, 2.0f };

	Vector2 scaled = v * 2.0f;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[0], 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[1], 4.0), "Vector2 Scalar multiplication failed");

	return TestResult::Pass();
}

TestResult Vector2Multiplication(Engine* e)
{
	Vector2 v1{ 1.0f, 2.0f };
	Vector2 v2{ 1.0f, 2.0f };

	Vector2 added = v1 * v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 1.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 4.0), "Vector2 multiplication failed");

	return TestResult::Pass();
}


TestResult Vector2Addition(Engine* e)
{
	Vector2 v1{ 1.0f, 2.0f };
	Vector2 v2{ 1.0f, 2.0f };

	Vector2 added = v1 + v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 4.0), "Vector2 addition failed");

	return TestResult::Pass();
}

TestResult Vector2Subtraction(Engine* e)
{
	Vector2 v1{ 1.0f, 2.0f };
	Vector2 v2{ 1.0f, 2.0f };

	Vector2 subbed = v1 - v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(subbed[0], 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(subbed[1], 0.0), "Vector2 subtraction failed");

	return TestResult::Pass();
}

TestResult Vector3ElementAccess(Engine* e)
{
	Vector3 v{ 1.0f, 2.0f, 3.0f };

	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f && v[2] == 3.0f,  "Element access in to Vector3 Failed.");

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
	constexpr f32 EXPECTED_MAGNITUDE = 3.741657386773941;

	Vector3 v{ 1.0f, 2.0f, 3.0f };


	TEST_ASSERT(FLOATING_POINT_ROUGHLY_EQUAL(v.Magnitude(), EXPECTED_MAGNITUDE), "Vector3 Magnitude is incorrect");
	return TestResult::Pass();
}

TestResult Vector3ScalarMultiplication(Engine* e)
{
	Vector3 v{ 1.0f, 2.0f, 3.0f };
	Vector3 scaled = v * 2.0f;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[0], 2.0) && 
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[1], 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[2], 6.0), "Vector3 Scalar multiplication failed");

	return TestResult::Pass();
}

TestResult Vector3Multiplication(Engine* e)
{
	Vector3 v1{ 1.0f, 2.0f, 3.0f };
	Vector3 v2{ 1.0f, 2.0f, 3.0f };

	Vector3 added = v1 * v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 1.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[2], 9.0), "Vector3 multiplication failed");

	return TestResult::Pass();
}


TestResult Vector3Addition(Engine* e)
{
	Vector3 v1{ 1.0f, 2.0f, 3.0f };
	Vector3 v2{ 1.0f, 2.0f, 3.0f };

	Vector3 added = v1 + v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[2], 6.0), "Vector3 addition failed");

	return TestResult::Pass();
}

TestResult Vector3Subtraction(Engine* e)
{
	Vector3 v1{ 1.0f, 2.0f, 3.0f };
	Vector3 v2{ 1.0f, 2.0f, 3.0f };

	Vector3 added = v1 - v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[2], 0.0), "Vector3 subtraction failed");

	return TestResult::Pass();
}


TestResult Vector4ElementAccess(Engine* e)
{
	Vector4 v{ 1.0f, 2.0f, 3.0f, 4.0f };

	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f && v[2] == 3.0f && v[3] == 4.0f, "Element access in to Vector3 Failed.");

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
	constexpr f32 EXPECTED_MAGNITUDE = 5.4772257804870605;
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
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[0], 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[1], 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[2], 6.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[3], 8.0), "Vector4 Scalar multiplication failed");

	return TestResult::Pass();
}


TestResult Vector4Multiplication(Engine* e)
{
	Vector4 v1{ 1.0f, 2.0f, 3.0f, 4.0f };
	Vector4 v2{ 1.0f, 2.0f, 3.0f, 4.0f };

	Vector4 added = v1 * v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 1.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[2], 9.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[3], 16.0), "Vector4 multiplication failed");

	return TestResult::Pass();
}


TestResult Vector4Addition(Engine* e)
{
	Vector4 v1{ 1.0f, 2.0f, 3.0f, 4.0f };
	Vector4 v2{ 1.0f, 2.0f, 3.0f, 4.0f };

	Vector4 added = v1 + v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[2], 6.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[3], 8.0), "Vector4 addition failed");

	return TestResult::Pass();
}

TestResult Vector4Subtraction(Engine* e)
{
	Vector4 v1{ 1.0f, 2.0f, 3.0f, 4.0f };
	Vector4 v2{ 1.0f, 2.0f, 3.0f, 4.0f };
   
	Vector4 added = v1 - v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[2], 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[3], 0.0), "Vector4 subtraction failed");

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

TestResult Matrix3x3ElementAccess(Engine* e)
{
	Matrix3x3 a{ 1,4,7,2,5,8,3,6,9 };

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(a[0][0], 1) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[0][1], 4) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[0][2], 7) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[1][0], 2) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[1][1], 5) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[1][2], 8) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[2][0], 3) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[2][1], 6) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[2][2], 9)
		, "Element access in to Matrix3x3 Failed.");

	return TestResult::Pass();
}

TestResult Matrix3x3Multiplication(Engine* e)
{
	Matrix3x3 a{ 1,4,7,2,5,8,3,6,9 };
	Matrix3x3 b{ 2,5,8,3,6,9,4,7,10 };

	Matrix3x3 c = a * b;
	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][0], 36) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][1], 81) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][2], 126) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][0], 42) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][1], 96) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][2], 150) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[2][0], 48) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[2][1], 111) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[2][2], 174)
		, "Matrix3x3 multiplication Failed.");

	return TestResult::Pass();
}

TestResult Matrix4x4ElementAccess(Engine* e)
{
	Matrix4x4 a{ 1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16 };

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(a[0][0], 1)  &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[0][1], 5)  &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[0][2], 9)  &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[0][3], 13) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[1][0], 2)  &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[1][1], 6)  &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[1][2], 10) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[1][3], 14) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[2][0], 3)  &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[2][1], 7)  &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[2][2], 11) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[2][3], 15) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[3][0], 4)  &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[3][1], 8)  &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[3][2], 12) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[3][3], 16) 
		, "Element access in to Matrix4x4 Failed.");

	return TestResult::Pass();
}

TestResult Matrix4x4Multiplication(Engine* e)
{
	Matrix4x4 a{ 1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16 };
	Matrix4x4 b{ 2,6,10,14,3,7,11,15,4,8,12,16,5,9,13,17 };

	Matrix4x4 c = a * b;
	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][0], 100) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][1], 228) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][2], 356) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][3], 484) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][0], 110) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][1], 254) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][2], 398) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][3], 542) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[2][0], 120) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[2][1], 280) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[2][2], 440) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[2][3], 600) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[3][0], 130) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[3][1], 306) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[3][2], 482) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[3][3], 658)
		, "Matrix4x4 multiplication Failed.");

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
ADD_TEST(Matrix3x3ElementAccess)
ADD_TEST(Matrix3x3Multiplication)
ADD_TEST(Matrix4x4ElementAccess)
ADD_TEST(Matrix4x4Multiplication)
TEST_APP_END_SUITE()