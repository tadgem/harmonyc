#include "HarmonyTest.h"

using namespace harmony;

/// <summary>
/// Math function tests
/// </summary>
/// <param name="e"></param>
/// <returns></returns>
TestResult SqrtTest(Engine* e)
{
	f64 sqr = 9.0;
	f64 sqr_root = Sqrt(sqr);
	TEST_ASSERT(FLOATING_POINT_ROUGHLY_EQUAL(sqr_root, 3.0), "Incorrect square root computed");

	return TestResult::Pass();
}

TestResult AbsTest(Engine* e)
{
	f64 sqr = -9.0;

	TEST_ASSERT(FLOATING_POINT_ROUGHLY_EQUAL(Abs(sqr), 9.0), "Incorrect square root computed");

	return TestResult::Pass();
}

/// <summary>
/// Vector Tests
/// </summary>
/// <param name="e"></param>
/// <returns></returns>

TestResult Vector2fElementAccess(Engine* e)
{
	Vector2f v = { 1.0f, 2.0f } ;

	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f, "Element access in to Vector2f Failed.");

	return TestResult::Pass();
}

TestResult Vector2fElementArrayAccess(Engine* e)
{
	Vector2f v{ 1.0f, 2.0f };

	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f, "Array access in to Vector2f Failed.");

	return TestResult::Pass();
}

TestResult Vector2fMagnitude(Engine* e)
{
	constexpr f32 EXPECTED_MAGNITUDE = 2.23606797749979;

	Vector2f v {1.0f, 2.0f};

	TEST_ASSERT(FLOATING_POINT_ROUGHLY_EQUAL(v.Magnitude(), EXPECTED_MAGNITUDE), "Vector2f Magnitude is incorrect");

	return TestResult::Pass();
}

TestResult Vector2fScalarMultiplication(Engine* e)
{
	Vector2f v{ 1.0f, 2.0f };

	Vector2f scaled = v * 2.0f;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[0], 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[1], 4.0), "Vector2f Scalar multiplication failed");

	return TestResult::Pass();
}

TestResult Vector2fMultiplication(Engine* e)
{
	Vector2f v1{ 1.0f, 2.0f };
	Vector2f v2{ 1.0f, 2.0f };

	Vector2f added = v1 * v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 1.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 4.0), "Vector2f multiplication failed");

	return TestResult::Pass();
}


TestResult Vector2fAddition(Engine* e)
{
	Vector2f v1{ 1.0f, 2.0f };
	Vector2f v2{ 1.0f, 2.0f };

	Vector2f added = v1 + v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 4.0), "Vector2f addition failed");

	return TestResult::Pass();
}

TestResult Vector2fSubtraction(Engine* e)
{
	Vector2f v1{ 1.0f, 2.0f };
	Vector2f v2{ 1.0f, 2.0f };

	Vector2f subbed = v1 - v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(subbed[0], 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(subbed[1], 0.0), "Vector2f subtraction failed");

	return TestResult::Pass();
}

TestResult Vector2fDot(Engine* e)
{
	Vector2f v1{ 0.0f, 1.0f };
	Vector2f v2{ 0.0f, 1.0f };

	auto dot1 = v1.Dot(v2);
	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(dot1, 1.0), "Vector2f Dot product failed when vectors should be positively parallel");

	Vector2f v3{ 1.0f, 0.0f };
	auto dot2 = v1.Dot(v3);

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(dot2, 0.0), "Vector2f Dot product failed when vectors should be orthogonal");

	Vector2f v4{ 0.0f, -1.0f };
	auto dot3 = v1.Dot(v4);

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(dot3, -1.0), "Vector2f Dot product failed when vectors should be negatively parallel");

	return TestResult::Pass();
}

TestResult Vector3fElementAccess(Engine* e)
{

	Vector3f v{ 1.0f, 2.0f, 3.0f };

	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f && v[2] == 3.0f,  "Element access in to Vector3f Failed.");

	return TestResult::Pass();
}

TestResult Vector3fElementArrayAccess(Engine* e)
{
	Vector3f v{ 1.0f, 2.0f, 3.0f };


	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f && v[2] == 3.0f, "Array access in to Vector3f Failed.");

	return TestResult::Pass();
}

TestResult Vector3fMagnitude(Engine* e)
{
	constexpr f32 EXPECTED_MAGNITUDE = 3.741657386773941;

	Vector3f v{ 1.0f, 2.0f, 3.0f };


	TEST_ASSERT(FLOATING_POINT_ROUGHLY_EQUAL(v.Magnitude(), EXPECTED_MAGNITUDE), "Vector3f Magnitude is incorrect");
	return TestResult::Pass();
}

TestResult Vector3fScalarMultiplication(Engine* e)
{
	Vector3f v{ 1.0f, 2.0f, 3.0f };
	Vector3f scaled = v * 2.0f;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[0], 2.0) && 
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[1], 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[2], 6.0), "Vector3f Scalar multiplication failed");

	return TestResult::Pass();
}

TestResult Vector3fMultiplication(Engine* e)
{
	Vector3f v1{ 1.0f, 2.0f, 3.0f };
	Vector3f v2{ 1.0f, 2.0f, 3.0f };

	Vector3f added = v1 * v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 1.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[2], 9.0), "Vector3f multiplication failed");

	return TestResult::Pass();
}


TestResult Vector3fAddition(Engine* e)
{
	Vector3f v1{ 1.0f, 2.0f, 3.0f };
	Vector3f v2{ 1.0f, 2.0f, 3.0f };

	Vector3f added = v1 + v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[2], 6.0), "Vector3f addition failed");

	return TestResult::Pass();
}

TestResult Vector3fSubtraction(Engine* e)
{
	Vector3f v1{ 1.0f, 2.0f, 3.0f };
	Vector3f v2{ 1.0f, 2.0f, 3.0f };

	Vector3f added = v1 - v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[2], 0.0), "Vector3f subtraction failed");

	return TestResult::Pass();
}

TestResult Vector3fDot(Engine* e)
{
	Vector3f v1{ 0.0f, 1.0f, 0.0f};
	Vector3f v2{ 0.0f, 1.0f, 0.0f};

	auto dot1 = v1.Dot(v2);

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(dot1, 1.0), "Vector3f Dot product failed when vectors should be positively parallel");

	Vector3f v3{ 1.0f, 0.0f, 0.0f};
	auto dot2 = v1.Dot(v3);

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(dot2, 0.0), "Vector3f Dot product failed when vectors should be orthogonal");

	Vector3f v4{ 0.0f, -1.0f , 0.0f};
	auto dot3 = v1.Dot(v4);

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(dot3, -1.0), "Vector3f Dot product failed when vectors should be negatively parallel");

	return TestResult::Pass();
}

TestResult Vector4fElementAccess(Engine* e)
{
	Vector4f v{ 1.0f, 2.0f, 3.0f, 4.0f };

	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f && v[2] == 3.0f && v[3] == 4.0f, "Element access in to Vector3f Failed.");

	return TestResult::Pass();
}

TestResult Vector4fElementArrayAccess(Engine* e)
{
	Vector4f v{ 1.0f, 2.0f, 3.0f, 4.0f };

	TEST_ASSERT(v[0] == 1.0f && v[1] == 2.0f && v[2] == 3.0f && v[3] == 4.0f, "Array access in to Vector3f Failed.");

	return TestResult::Pass();
}

TestResult Vector4fMagnitude(Engine* e)
{
	constexpr f32 EXPECTED_MAGNITUDE = 5.4772257804870605;
	Vector4f v{ 1.0f, 2.0f, 3.0f, 4.0f };
	auto mag = v.Magnitude();
	TEST_ASSERT(FLOATING_POINT_ROUGHLY_EQUAL(v.Magnitude(), EXPECTED_MAGNITUDE), "Vector4f Magnitude is incorrect");
	return TestResult::Pass();
}

TestResult Vector4fScalarMultiplication(Engine* e)
{
	Vector4f v{ 1.0f, 2.0f, 3.0f, 4.0f };

	Vector4f scaled = v * 2.0f;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[0], 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[1], 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[2], 6.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(scaled[3], 8.0), "Vector4f Scalar multiplication failed");

	return TestResult::Pass();
}


TestResult Vector4fMultiplication(Engine* e)
{
	Vector4f v1{ 1.0f, 2.0f, 3.0f, 4.0f };
	Vector4f v2{ 1.0f, 2.0f, 3.0f, 4.0f };

	Vector4f added = v1 * v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 1.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[2], 9.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[3], 16.0), "Vector4f multiplication failed");

	return TestResult::Pass();
}


TestResult Vector4fAddition(Engine* e)
{
	Vector4f v1{ 1.0f, 2.0f, 3.0f, 4.0f };
	Vector4f v2{ 1.0f, 2.0f, 3.0f, 4.0f };

	Vector4f added = v1 + v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 2.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 4.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[2], 6.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[3], 8.0), "Vector4f addition failed");

	return TestResult::Pass();
}

TestResult Vector4fSubtraction(Engine* e)
{
	Vector4f v1{ 1.0f, 2.0f, 3.0f, 4.0f };
	Vector4f v2{ 1.0f, 2.0f, 3.0f, 4.0f };
   
	Vector4f added = v1 - v2;

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(added[0], 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[1], 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[2], 0.0) &&
		FLOATING_POINT_ROUGHLY_EQUAL(added[3], 0.0), "Vector4f subtraction failed");

	return TestResult::Pass();
}

TestResult Vector4fDot(Engine* e)
{
	Vector4f v1{ 0.0f, 1.0f, 0.0f , 0.0f};
	Vector4f v2{ 0.0f, 1.0f, 0.0f , 0.0f};

	auto dot1 = v1.Dot(v2);

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(dot1, 1.0), "Vector4f Dot product failed when vectors should be positively parallel");

	Vector4f v3{ 1.0f, 0.0f, 0.0f , 0.0f};
	auto dot2 = v1.Dot(v3);

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(dot2, 0.0), "Vector4f Dot product failed when vectors should be orthogonal");

	Vector4f v4{ 0.0f, -1.0f , 0.0f, 0.0f };
	auto dot3 = v1.Dot(v4);

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(dot3, -1.0), "Vector4f Dot product failed when vectors should be negatively parallel");

	return TestResult::Pass();
}

/// <summary>
/// Matrix tests
/// </summary>
TestResult Matrix2x2fElementAccess(Engine* e)
{
	Matrix2x2f a { 1,3,2,4 };
	
	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(a[0][0], 1) && 
		FLOATING_POINT_ROUGHLY_EQUAL(a[0][1], 3) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[1][0], 2) &&
		FLOATING_POINT_ROUGHLY_EQUAL(a[1][1], 4)
		, "Element access in to Matrix2x2f Failed.");

	return TestResult::Pass();
}

TestResult Matrix2x2fMultiplication(Engine* e)
{
	Matrix2x2f a{ 1,3,2,4 };
	Matrix2x2f b{ 5,7,6,8 };
	Matrix2x2f c = a * b;
	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][0], 19) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][1], 43) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][0], 22) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][1], 50)
		, "Matrix2x2f multiplication Failed.");

	return TestResult::Pass();
}

TestResult Matrix2x2fTranspose(Engine* e)
{
	Matrix2x2f a{ 1,3,2,4 };
	Matrix2x2f c = a.Transpose();
	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][0], 1) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][1], 2) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][0], 3) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][1], 4)
		, "Matrix2x2f Transpose Failed.");

	return TestResult::Pass();
}

TestResult Matrix3x3fElementAccess(Engine* e)
{
	Matrix3x3f a{ 1,4,7,2,5,8,3,6,9 };

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
		, "Element access in to Matrix3x3f Failed.");

	return TestResult::Pass();
}

TestResult Matrix3x3fMultiplication(Engine* e)
{
	Matrix3x3f a{ 1,4,7,2,5,8,3,6,9 };
	Matrix3x3f b{ 2,5,8,3,6,9,4,7,10 };

	Matrix3x3f c = a * b;
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
		, "Matrix3x3f multiplication Failed.");

	return TestResult::Pass();
}

TestResult Matrix3x3fTranspose(Engine* e)
{
	Matrix3x3f a{ 1,4,7,2,5,8,3,6,9 };
	Matrix3x3f c = a.Transpose();

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][0], 1) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][1], 2) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][2], 3) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][0], 4) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][1], 5) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][2], 6) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[2][0], 7) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[2][1], 8) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[2][2], 9)
		, "Matrix3x3f Transpose Failed.");

	return TestResult::Pass();
}

TestResult Matrix4x4fElementAccess(Engine* e)
{
	Matrix4x4f a{ 1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16 };

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
		, "Element access in to Matrix4x4f Failed.");

	return TestResult::Pass();
}

TestResult Matrix4x4fMultiplication(Engine* e)
{
	Matrix4x4f a{ 1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16 };
	Matrix4x4f b{ 2,6,10,14,3,7,11,15,4,8,12,16,5,9,13,17 };

	Matrix4x4f c = a * b;
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
		, "Matrix4x4f multiplication Failed.");

	return TestResult::Pass();
}

TestResult Matrix4x4fTranspose(Engine* e)
{
	Matrix4x4f a{ 1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16 };
	auto c = a.Transpose();

	TEST_ASSERT(
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][0], 1) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][1], 2) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][2], 3) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[0][3], 4) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][0], 5) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][1], 6) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][2], 7) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[1][3], 8) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[2][0], 9) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[2][1], 10) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[2][2], 11) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[2][3], 12) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[3][0], 13) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[3][1], 14) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[3][2], 15) &&
		FLOATING_POINT_ROUGHLY_EQUAL(c[3][3], 16)
		, "Matrix4x4f Transpose Failed.");

	return TestResult::Pass();
}

TestResult TranslationMatrixTest(Engine* e)
{
	Vector3f posRotScale = {1.0, 2.0, 3.0};
	Matrix4x4f trans = Translate(posRotScale);

	Matrix4x4f rot = Rotate(posRotScale.Magnitude(), posRotScale.Normalized());

	Matrix4x4f scale = Scale(posRotScale);

	Matrix4x4f model = trans * rot * scale;
	return TestResult::Pass();
}


TEST_APP_BEGIN_SUITE("Maths", MEGABYTES(32))

// Maths function tests
ADD_TEST(SqrtTest)
ADD_TEST(AbsTest)


// Vector Tests
//ADD_TEST(Vector2fElementAccess)
//ADD_TEST(Vector2fElementArrayAccess)
//ADD_TEST(Vector2fMagnitude)
//ADD_TEST(Vector2fScalarMultiplication)
//ADD_TEST(Vector2fMultiplication)
//ADD_TEST(Vector2fAddition)
//ADD_TEST(Vector2fSubtraction)
ADD_TEST(Vector2fDot)
//ADD_TEST(Vector3fElementAccess)
//ADD_TEST(Vector3fElementArrayAccess)
//ADD_TEST(Vector3fMagnitude)
//ADD_TEST(Vector3fScalarMultiplication)
//ADD_TEST(Vector3fMultiplication)
//ADD_TEST(Vector3fAddition)
//ADD_TEST(Vector3fSubtraction)
ADD_TEST(Vector3fDot)
//ADD_TEST(Vector4fElementAccess)
//ADD_TEST(Vector4fElementArrayAccess)
//ADD_TEST(Vector4fMagnitude)
//ADD_TEST(Vector4fScalarMultiplication)
//ADD_TEST(Vector4fMultiplication)
//ADD_TEST(Vector4fAddition)
//ADD_TEST(Vector4fSubtraction)
ADD_TEST(Vector4fDot)

// Matrix Tests

//ADD_TEST(Matrix2x2fElementAccess)
//ADD_TEST(Matrix2x2fMultiplication)
//ADD_TEST(Matrix2x2fTranspose)
//ADD_TEST(Matrix3x3fElementAccess)
//ADD_TEST(Matrix3x3fMultiplication)
//ADD_TEST(Matrix3x3fTranspose)
//ADD_TEST(Matrix4x4fElementAccess)
//ADD_TEST(Matrix4x4fMultiplication)
//ADD_TEST(Matrix4x4fTranspose)

// Transformation Tests
ADD_TEST(TranslationMatrixTest)
TEST_APP_END_SUITE()