#pragma once
#include "Primitives.h"
#include "Macros.h"
#include "SDL3/SDL.h"

#define SCALAR_TYPE f64

namespace harmony
{
	/// <summary>
	/// Vector Definitions
	/// </summary>
	struct Vector2
	{
		union {
			struct {
				SCALAR_TYPE x, y;
			};
			SCALAR_TYPE values[2];
		};

		Vector2() : x(0.0), y(0.0) {}
		Vector2(const SCALAR_TYPE& initialValue) : x(initialValue), y(initialValue) {}
		Vector2(const SCALAR_TYPE& _x, const SCALAR_TYPE& _y) : x(_x), y(_y) {}

		SCALAR_TYPE& operator[](int index)
		{
			HNY_ASSERT(index < 2, "Index out of range for Vector2");
			return values[index];
		}

		const SCALAR_TYPE& operator[](int index) const
		{
			HNY_ASSERT(index < 2, "Index out of range for Vector2");
			return values[index];
		}

		SCALAR_TYPE Magnitude() { return SDL_sqrtf(x * x + y * y); }

		Vector2	operator*(const SCALAR_TYPE& s)
		{
			return Vector2(x * s, y * s);
		}
	};

	struct Vector3
	{
		union {
			struct {
				SCALAR_TYPE x, y, z;
			};
			SCALAR_TYPE values[3];
		};

		Vector3() : x(0.0), y(0.0), z(0.0) {}
		Vector3(const SCALAR_TYPE& initialValue) : x(initialValue), y(initialValue), z(initialValue) {}
		Vector3(const SCALAR_TYPE& _x, const SCALAR_TYPE& _y, const SCALAR_TYPE& _z) : x(_x), y(_y), z(_z) {}

		SCALAR_TYPE& operator[](int index)
		{
			HNY_ASSERT(index < 3, "Index out of range for Vector3");
			return values[index];
		}

		const SCALAR_TYPE& operator[](int index) const
		{
			HNY_ASSERT(index < 3, "Index out of range for Vector3");
			return values[index];
		}

		SCALAR_TYPE Magnitude() { return SDL_sqrtf(x * x + y * y + z * z); }

		Vector3	operator*(const SCALAR_TYPE& s)
		{
			return Vector3(x * s, y * s, z * s);
		}
	};


	struct Vector4
	{
		union {
			struct {
				SCALAR_TYPE x, y, z, w;
			};
			SCALAR_TYPE values[4];
		};

		Vector4() : x(0.0), y(0.0), z(0.0), w(0.0) {}
		Vector4(const SCALAR_TYPE& initialValue) : x(initialValue), y(initialValue), z(initialValue), w(initialValue) {}
		Vector4(const SCALAR_TYPE& _x, const SCALAR_TYPE& _y, const SCALAR_TYPE& _z, const SCALAR_TYPE& _w) : x(_x), y(_y), z(_z), w(_w) {}

		SCALAR_TYPE& operator[](int index)
		{
			HNY_ASSERT(index < 4, "Index out of range for Vector4");
			return values[index];
		}

		const SCALAR_TYPE& operator[](int index) const
		{
			HNY_ASSERT(index < 4, "Index out of range for Vector4");
			return values[index];
		}

		SCALAR_TYPE Magnitude() { return SDL_sqrtf(x * x + y * y + z * z + w * w); }

		Vector4	operator*(const SCALAR_TYPE& s)
		{
			return Vector4(x * s, y * s, z *s, w * s);
		}
	};

	/// <summary>
	/// Matrix Definitions (Column Major)
	/// </summary>
	struct Matrix2x2
	{
		union
		{
			Vector2		columns[2];
			SCALAR_TYPE			values[4];
		};
	};

	//struct Matrix3x3
	//{
	//	union
	//	{
	//		Vector3		columns[3];
	//		SCALAR_TYPE			values[9];
	//	};
	//};

	//struct Matrix4x4
	//{
	//	union
	//	{
	//		Vector4		columns[4];
	//		SCALAR_TYPE			values[16];
	//	};
	//};

	// what ops do we need
	// all vecs, addition, subtraction, multiplication, division
	// matrices, multiplication, inversion, matrix_cast (e.g. 4x4 -> 3x3)

}