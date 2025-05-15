#pragma once
#include "Primitives.h"
#include "Macros.h"
#include "SDL3/SDL.h"

namespace harmony
{
	template<typename _ScalarType>
	_ScalarType Abs(const _ScalarType& n)
	{
		return n < 0 ? -n : n;
	}

	template<typename _ScalarType>
	_ScalarType Sqrt(const _ScalarType& n)
	{
		HNY_ASSERT(n >= 0.0, "Cannot find square root of a negative or zero number");
		const int MAX_SQRT_ITERATIONS = 20;
		const _ScalarType ACCEPTABLE_DIFFERENCE = 0.00001;
		if (n == 0.0) { 
			return 0.0;
		};

		_ScalarType high = n;
		_ScalarType low = 0.0;
		_ScalarType guess = n / 2.0;

		while (Abs((guess * guess) - n) > ACCEPTABLE_DIFFERENCE)
		{
			if (guess * guess > n)
			{
				high = guess;
			}
			else {
				low = guess;
			}
			_ScalarType new_guess = (high + low) / 2.0;
			
			// getting stuck in an infinite loop
			if (new_guess == guess)
			{
				break;
			}

			guess = new_guess;
		}

		return guess;
	}

	template<typename _ScalarType, size_t _Dim>
	struct vector_t
	{
		_ScalarType values[_Dim];
		
		_ScalarType& operator[](int index)
		{
			HNY_ASSERT(index < _Dim, "Index out of range for Vector");
			return values[index]; 
		}
			
		const _ScalarType& operator[](int index) const
		{
			HNY_ASSERT(index < _Dim, "Index out of range for Vector"); 
			return values[index]; 
		}

		_ScalarType Magnitude() {
			
			_ScalarType _sqr_val = 0.0;
			for (auto n = 0; n < _Dim; n++)
			{
				_sqr_val += values[n] * values[n];
			}
			return SDL_sqrtf(_sqr_val);
		}

                void Normalize()
                {
                  auto mag = Magnitude();
                  for(auto i = 0; i < _Dim; i++)
                  {
                    values[i] /= mag;
                  }
                }

                vector_t<_ScalarType, _Dim> Normalized()
                {
                  auto mag = Magnitude();
                  vector_t<_ScalarType, _Dim> v {};

                  for(auto i = 0; i < _Dim; i++)
                  {
                    v[i] = values[i] / mag;
                  }
                  return v;
                }

		_ScalarType Dot(const vector_t<_ScalarType, _Dim>& other)
		{
			_ScalarType ret = 0.0;
			
			for (int i = 0; i < _Dim; i++)
			{
				ret += values[i] * other.values[i];
			}

			return ret;
		}

		_ScalarType DegreesBetween(const vector_t<_ScalarType, _Dim>& other)
		{
			auto dot = Dot(other);
			return std::acos(dot);
		}

		auto operator*(const _ScalarType& s)
		{
			auto _ret = *this; 
			
			for (auto n = 0; n < _Dim; n++)
			{
				_ret[n] *= s;
			}
			return _ret;
		}
		
		vector_t<_ScalarType, _Dim>& operator*=(const _ScalarType& s)
		{
			for (auto n = 0; n < _Dim; n++)
			{
				values[n] *= s;
			}
			return (*this);
		}

		vector_t<_ScalarType, _Dim> operator*(const vector_t<_ScalarType, _Dim>& s)
		{
			vector_t<_ScalarType, _Dim> _ret = *this; 
			
			for (auto n = 0; n < _Dim; n++)
			{
				_ret[n] *= s[n]; 
			}
			return _ret; 
		}
			
		vector_t<_ScalarType, _Dim>& operator*=(const vector_t<_ScalarType, _Dim>& s)
		{
			for (auto n = 0; n < _Dim; n++)
			{
				values[n] *= s[n];
			}
			return (*this);
		}

		vector_t<_ScalarType, _Dim> operator+(const vector_t<_ScalarType, _Dim>& s)
		{
			vector_t<_ScalarType, _Dim> _ret = *this;

			for (auto n = 0; n < _Dim; n++)
			{
				_ret[n] += s[n];
			}
			return _ret;
		}

		vector_t<_ScalarType, _Dim>& operator+=(const vector_t<_ScalarType, _Dim>& s)
		{
			for (auto n = 0; n < _Dim; n++)
			{
				values[n] += s[n];
			}
			return (*this);
		}

		vector_t<_ScalarType, _Dim> operator-(const vector_t<_ScalarType, _Dim>& s)
		{
			vector_t<_ScalarType, _Dim> _ret = *this;

			for (auto n = 0; n < _Dim; n++)
			{
				_ret[n] -= s[n];
			}
			return _ret;
		}

		vector_t<_ScalarType, _Dim>& operator-=(const vector_t<_ScalarType, _Dim>& s)
		{
			for (auto n = 0; n < _Dim; n++)
			{
				values[n] -= s[n];
			}
			return (*this);
		}

	};

	typedef vector_t<f32, 2> Vector2;
	typedef vector_t<f32, 3> Vector3;
	typedef vector_t<f32, 4> Vector4;


	/// <summary>
	/// Matrix Definitions (Column Major)
	/// </summary>
	template<typename _ScalarType, size_t _Cols, size_t _Rows>
	struct matrix_t
	{
		union
		{
			vector_t<_ScalarType, _Rows>	columns[_Cols];
			_ScalarType						values[_Rows*_Cols];
		};

		vector_t<_ScalarType, _Rows>& operator[](int index)
		{
			HNY_ASSERT(index < _Cols, "Index out of range for Vector##VEC_DIM");
			return columns[index];
		}

		const vector_t<_ScalarType, _Rows>& operator[](int index) const
		{
			HNY_ASSERT(index < _Cols, "Index out of range for Vector##VEC_DIM"); 
			return columns[index]; 
		}

		auto Transpose()
		{
			matrix_t<_ScalarType, _Rows, _Cols> result{};

			for (int column = 0; column < _Cols; column++)
			{
				for (int row = 0; row < _Rows; row++)
				{
					result[row][column] = columns[column][row];
				}
			}

			return result;
		}

		auto operator*(const f32& s)
		{
			auto _ret = *this;
			
			for (auto n = 0; n < _Cols*_Rows; n++)
			{
				_ret.values[n] *= s; 
			}
				return _ret; 
		}
			
		auto & operator*=(const f32& s)
		{
			for (auto n = 0; n < _Cols*_Rows; n++)
			{
				values[n] *= s; 
			}
			return (*this); 
		}

		template<size_t _OtherCols, size_t _OtherRows>
		auto operator*(const matrix_t<_ScalarType, _OtherCols, _OtherRows>& s)
		{			
			HNY_ASSERT(_Cols == _OtherRows, "Matrix cannot be multiplied, LHS.ColumnCount != RHS.RowCount");

			matrix_t<_ScalarType, _Cols, _OtherRows> result = {};

			for (int column = 0; column < _Cols; column++)
			{
				for (int row = 0; row < _OtherRows; row++)
				{
					f32 add_v = 0.0;
					for (int add = 0; add < _Cols; add++)
					{
						// add the add'th element of the LHS current column * RHS current row
						add_v += columns[add][row] * s.columns[column][add];
					}

					result[column][row] = add_v;
				}
			}

			return result;


		}


		auto operator+(const f32& s)
		{
			auto _ret = *this;

			for (auto n = 0; n < _Cols * _Rows; n++)
			{
				_ret.values[n] += s;
			}
			return _ret;
		}

		auto& operator+=(const f32& s)
		{
			for (auto n = 0; n < _Cols * _Rows; n++)
			{
				values[n] += s;
			}
			return (*this);
		}

		auto operator-(const f32& s)
		{
			auto _ret = *this;

			for (auto n = 0; n < _Cols * _Rows; n++)
			{
				_ret.values[n] -= s;
			}
			return _ret;
		}

		auto& operator-=(const f32& s)
		{
			for (auto n = 0; n < _Cols * _Rows; n++)
			{
				values[n] -= s;
			}
			return (*this);
		}
	};

	typedef matrix_t<f32, 2, 2> Matrix2x2;
	typedef matrix_t<f32, 3, 3> Matrix3x3;
	typedef matrix_t<f32, 4, 4> Matrix4x4;

        template<typename _ScalarType>
        matrix_t<_ScalarType, 4, 4> Translate(vector_t<_ScalarType, 3> t)
        {
          return matrix_t<_ScalarType, 4,4> {
            { 1,  0,  0,  t.x },
            { 0,  1,  0,  t.y },
            { 0,  0,  1,  t.z },
            { 0,  0,  0,  1   }
          };
        }

        template<typename _ScalarType>
        matrix_t<_ScalarType, 4,4> Scale(vector_t<_ScalarType, 3> s)
        {
          return matrix_t<_ScalarType, 4,4>
          {
            { s.x,  0.0,  0.0,  0.0},
            { 0.0,  s.y,  0.0,  0.0},
            { 0.0,  0.0,  s.z,  0.0},
            { 0.0,  0.0,  0.0,  1.0}
          };
        }

        // see https://registry.khronos.org/OpenGL-Refpages/gl2.1/
        template<typename _ScalarType>
        matrix_t<_ScalarType, 4, 4> Rotate(_ScalarType deg, vector_t<_ScalarType, 3> axis)
        {
          const _ScalarType c = cos(deg);
          const _ScalarType s = sin(deg);

          if(axis.Magnitude() > 1.0)
          {
            axis.Normalize();
          }

          const _ScalarType oneMinusC = 1.0 - c;
          const _ScalarType xs = axis.x * s;
          const _ScalarType ys = axis.y * s;
          const _ScalarType zs = axis.z * s;

          const _ScalarType _00 = axis.x * axis.x * oneMinusC + c;
          const _ScalarType _10 = axis.x * axis.y * oneMinusC - zs;
          const _ScalarType _20 = axis.x * axis.z * oneMinusC + ys;

          const _ScalarType _01 = axis.y * axis.x * oneMinusC + zs;
          const _ScalarType _11 = axis.y * axis.y * oneMinusC + c;
          const _ScalarType _21 = axis.y * axis.z * oneMinusC - xs;

          const _ScalarType _02 = axis.x * axis.z * oneMinusC - ys;
          const _ScalarType _12 = axis.y * axis.z * oneMinusC + xs;
          const _ScalarType _22 = axis.z * axis.z * oneMinusC + c;

          return matrix_t<_ScalarType, 4,4> {
              { _00 , _10, _20,  0.0 },
              { _01,  _11, _21,  0.0 },
              { _02,  _12, _22,  0.0 },
              { 0.0,  0.0, 0.0,  1.0 }
          };
        }

}