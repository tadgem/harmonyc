#pragma once
#include "Primitives.h"
#include "Macros.h"
#include "SDL3/SDL.h"

namespace harmony
{
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


	// what ops do we need
	// all vecs, addition, subtraction, multiplication, division
	// matrices, multiplication, inversion, matrix_cast (e.g. 4x4 -> 3x3)

}