#pragma once
#include "Primitives.h"

namespace harmony
{
	/// <summary>
	/// Vector Definitions
	/// </summary>
	struct Vector2
	{
		f32 x, y;
	};

	struct Vector3
	{
		f32 x, y, z;
	};

	struct Vector4
	{
		f32 x, y, x ,w;
	};

	/// <summary>
	/// Matrix Definitions (Column Major)
	/// </summary>
	struct Matrix2x2
	{
		union
		{
			Vector2		columns[2];
			f32			values[4];
		};
	};

	struct Matrix3x3
	{
		union
		{
			Vector3		columns[3];
			f32			values[9];
		};
	};

	struct Matrix4x4
	{
		union
		{
			Vector4		columns[4];
			f32			values[16];
		};
	};

	// what ops do we need
	// all vecs, addition, subtraction, multiplication, division
	// matrices, multiplication, inversion, matrix_cast (e.g. 4x4 -> 3x3)

}