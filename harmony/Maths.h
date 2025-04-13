#pragma once
#include "Primitives.h"
#include "Macros.h"
#include "SDL3/SDL.h"

#define SCALAR_TYPE f32

#define VECTOR_OP_IMPL(VEC_DIM) \
SCALAR_TYPE& operator[](int index)\
{\
	HNY_ASSERT(index < ##VEC_DIM, "Index out of range for Vector##VEC_DIM");\
	return values[index];\
}\
\
const SCALAR_TYPE& operator[](int index) const\
{\
	HNY_ASSERT(index < ##VEC_DIM, "Index out of range for Vector##VEC_DIM");\
	return values[index];\
}\
\
SCALAR_TYPE Magnitude() {\
	SCALAR_TYPE _sqr_val = 0.0;\
	for (auto n = 0; n < ##VEC_DIM; n++)\
	{\
		_sqr_val += values[n] * values[n];\
	}\
	return SDL_sqrtf(_sqr_val);\
}\
\
Vector##VEC_DIM	operator*(const SCALAR_TYPE& s)\
{\
	Vector##VEC_DIM _ret = *this;\
	\
	for (auto n = 0; n < ##VEC_DIM; n++)\
	{\
		_ret[n] *= s;\
	}\
	return _ret;\
}\
\
Vector##VEC_DIM& operator*=(const SCALAR_TYPE& s)\
{\
	for (auto n = 0; n < ##VEC_DIM; n++)\
	{\
		values[n] *= s;\
	}\
	return (*this);\
}\
\
Vector##VEC_DIM	operator*(const Vector##VEC_DIM& s)\
{\
	Vector##VEC_DIM _ret = *this;\
		\
	for (auto n = 0; n < ##VEC_DIM; n++)\
	{\
		_ret[n] *= s[n];\
	}\
	return _ret;\
}\
\
Vector##VEC_DIM& operator*=(const Vector##VEC_DIM& s)\
{\
	for (auto n = 0; n < ##VEC_DIM; n++)\
	{\
		values[n] *= s[n];\
	}\
	return (*this);\
}\
Vector##VEC_DIM	operator+(const Vector##VEC_DIM& s)\
{\
	Vector##VEC_DIM _ret = *this;\
		\
	for (auto n = 0; n < ##VEC_DIM; n++)\
	{\
		_ret[n] += s[n];\
	}\
	return _ret;\
}\
Vector##VEC_DIM& operator+=(const Vector##VEC_DIM& s)\
{\
	for (auto n = 0; n < ##VEC_DIM; n++)\
	{\
		values[n] += s[n];\
	}\
	return (*this);\
}\
Vector##VEC_DIM	operator-(const Vector##VEC_DIM& s)\
{\
	Vector##VEC_DIM _ret = *this;\
		\
	for (auto n = 0; n < ##VEC_DIM; n++)\
	{\
		_ret[n] -= s[n];\
	}\
	return _ret;\
}\
Vector##VEC_DIM& operator-=(const Vector##VEC_DIM& s)\
{\
	for (auto n = 0; n < ##VEC_DIM; n++)\
	{\
		values[n] -= s[n];\
	}\
	return (*this);\
}\

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
		VECTOR_OP_IMPL(2)
	};

	struct Vector3
	{
		union {
			struct {
				SCALAR_TYPE x, y, z;
			};
			SCALAR_TYPE values[3];
		};

		VECTOR_OP_IMPL(3)
	};


	struct Vector4
	{
		union {
			struct {
				SCALAR_TYPE x, y, z, w;
			};
			SCALAR_TYPE values[4];
		};

		VECTOR_OP_IMPL(4)
	};

	/// <summary>
	/// Matrix Definitions (Column Major)
	/// </summary>
	struct Matrix2x2
	{
		union
		{
			Vector2				columns[2];
			SCALAR_TYPE			values[4];
		};

		const Vector2& operator[](int index) const
		{
			HNY_ASSERT(index < 2, "Index out of range for Vector##VEC_DIM"); 
			return columns[index]; 
		}

		Matrix2x2 operator*(const SCALAR_TYPE& s)
		{
			Matrix2x2 _ret = *this;
			
			for (auto n = 0; n < 4; n++)
			{
				_ret.values[n] *= s; 
			}
				return _ret; 
		}
			
		Matrix2x2& operator*=(const SCALAR_TYPE& s)
		{
			for (auto n = 0; n < 4; n++)
			{
				values[n] *= s; 
			}
			return (*this); 
		}

		Matrix2x2 operator*(const Matrix2x2& s)
		{
			Matrix2x2 _ret{};


			for (auto c = 0; c < 2; c++)
			{
				for (auto r = 0; r < 2; r++)
				{
					_ret.columns[c][r] = 
						
						columns[c][r] * s.columns[r][c] + 
						columns[1][0] * s.columns[0][1];
					
				}
			}
			return _ret;
		}

		Matrix2x2& operator*=(const Matrix2x2& s)
		{
			for (auto c = 0; c < 2; c++)
			{
				for (auto r = 0; r < 2; r++)
				{
					columns[c][r] *= s[r][c];
				}
			}
			return (*this);
		}

		Matrix2x2 operator+(const SCALAR_TYPE& s)
		{
			Matrix2x2 _ret = *this;

			for (auto n = 0; n < 4; n++)
			{
				_ret.values[n] += s;
			}
			return _ret;
		}

		Matrix2x2& operator+=(const SCALAR_TYPE& s)
		{
			for (auto n = 0; n < 4; n++)
			{
				values[n] += s;
			}
			return (*this);
		}

		Matrix2x2 operator-(const SCALAR_TYPE& s)
		{
			Matrix2x2 _ret = *this;

			for (auto n = 0; n < 4; n++)
			{
				_ret.values[n] -= s;
			}
			return _ret;
		}

		Matrix2x2& operator-=(const SCALAR_TYPE& s)
		{
			for (auto n = 0; n < 4; n++)
			{
				values[n] -= s;
			}
			return (*this);
		}



	};

	// what ops do we need
	// all vecs, addition, subtraction, multiplication, division
	// matrices, multiplication, inversion, matrix_cast (e.g. 4x4 -> 3x3)

}