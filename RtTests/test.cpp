#include "pch.h"
#include "include_all.hpp"

namespace TuplePointVector 
{
	TEST(TupleTest, HandlesPointAssignment)
	{
		Point4 tp{ 4.3, -4.2, 3.1 };

		EXPECT_TRUE(is_equal(tp.x, 4.3)) << "X member did not assign";
		EXPECT_TRUE(is_equal(tp.y, -4.2)) << "Y member did not assign";
		EXPECT_TRUE(is_equal(tp.z, 3.1)) << "Z member did not assign";
		EXPECT_TRUE(is_equal(tp.w, 1.0)) << "W member did not assign";
	}

	TEST(TupleTest, HandlesVectorAssignment)
	{
		Vector4 tp{ 4.3, -4.2, 3.1 };

		EXPECT_TRUE(is_equal(tp.x, 4.3)) << "X member did not assign";
		EXPECT_TRUE(is_equal(tp.y, -4.2)) << "Y member did not assign";
		EXPECT_TRUE(is_equal(tp.z, 3.1)) << "Z member did not assign";
		EXPECT_TRUE(is_equal(tp.w, 0.0)) << "W member did not assign";
	}

	TEST(TupleTest, HandlesTupleAdd)
	{
		Point4 a{ 3.0, -2.0, 5.0 };
		Vector4 b{ -2.0, 3.0, 1.0 };
		Point4 c = a + b;

		EXPECT_TRUE(c == Point4(1.0, 1.0, 6.0)) << "Tuple addition bad";
	}

	TEST(TupleTest, HandlesTupleSubPP)
	{
		Point4 p1{ 3.0, 2.0, 1.0 };
		Point4 p2{ 5.0, 6.0, 7.0 };
		Vector4 v = p1 - p2;

		EXPECT_TRUE(v == Vector4(-2.0, -4.0, -6.0)) << "Tuple Point4 Point4 subtraction bad";
	}

	TEST(TupleTest, HandlesTupleSubPV)
	{
		Point4 p1{ 3.0, 2.0, 1.0 };
		Vector4 v1{ 5.0, 6.0, 7.0 };
		Point4 p2 = p1 - v1;

		EXPECT_TRUE(p2 == Point4(-2.0, -4.0, -6.0)) << "Tuple Point4 Vector4 subtraction bad";
	}

	TEST(TupleTest, HandlesTupleSubVV)
	{
		Vector4 v1{ 3.0, 2.0, 1.0 };
		Vector4 v2{ 5.0, 6.0, 7.0 };
		Vector4 v = v1 - v2;

		EXPECT_TRUE(v == Vector4(-2.0, -4.0, -6.0)) << "Tuple Vector4 Vector4 subtraction bad";
	}

	TEST(TupleTest, HandlesTupleNegation)
	{
		Vector4 a{ 1.0, -2.0, 3.0 };
		a = -a;

		EXPECT_TRUE(a == Vector4(-1.0, 2.0, -3.0)) << "Vector negation bad";
	}

	TEST(TupleTest, HandlesTupleScalarMult)
	{
		TestTuple a{ 1.0, -2.0, 3.0, -4.0 };

		EXPECT_TRUE(a * 3.5 == TestTuple(3.5, -7.0, 10.5, -14.0)) << "Tuple scalar multiplication bad";
		EXPECT_TRUE(a * 0.5 == TestTuple(0.5, -1.0, 1.5, -2.0)) << "Tuple scalar multiplication bad";
		EXPECT_TRUE(0.5 * a == TestTuple(0.5, -1.0, 1.5, -2.0)) << "scalar Tuple multiplication bad";
	}

	TEST(TupleTest, HandlesTupleScalarDiv)
	{
		TestTuple a{ 1.0, -2.0, 3.0, -4.0 };

		EXPECT_TRUE(a / 2.0 == TestTuple(0.5, -1.0, 1.5, -2.0)) << "scalar Tuple division bad";
	}

	TEST(TupleTest, HandlesTupleMagnitude)
	{
		Vector4 v1{ 1.0, 0.0, 0.0 };
		Vector4 v2{ 0.0, 0.0, 1.0 };
		Vector4 v3{ 1.0, 2.0, 3.0 };
		Vector4 v4{ -1.0, -2.0, -3.0 };

		EXPECT_TRUE(is_equal(magnitude(v1), 1.0)) << "Tuple magnitude bad";
		EXPECT_TRUE(is_equal(magnitude(v2), 1.0)) << "Tuple magnitude bad";
		EXPECT_TRUE(is_equal(magnitude(v3), sqrt(14.0))) << "Tuple magnitude bad";
		EXPECT_TRUE(is_equal(magnitude(v4), sqrt(14.0))) << "Tuple magnitude bad";
	}

	TEST(TupleTest, HandlesTupleNormalize)
	{
		Vector4 v1{ 4.0, 0.0, 0.0 };
		Vector4 v2{ 1.0, 2.0, 3.0 };
		Vector4 v1_n = normalize(v1);
		Vector4 v2_n = normalize(v2);

		EXPECT_TRUE(is_equal(magnitude(v2_n), 1.0)) << "Tuple normalize bad";
		EXPECT_TRUE(v2_n == Vector4(0.26726, 0.53452, 0.80178)) << "Tuple normalize bad";
		EXPECT_TRUE(v1_n == Vector4(1.0, 0.0, 0.0)) << "Tuple normalize bad";
	}

	TEST(TupleTest, HandlesTupleDot)
	{
		Vector4 a{ 1.0, 2.0, 3.0 };
		Vector4 b{ 2.0, 3.0, 4.0 };

		EXPECT_TRUE(is_equal(dot(a, b), 20.0)) << "Tuple dot bad";
	}

	TEST(TupleTest, HandlesTupleCross)
	{
		Vector4 a{ 1.0, 2.0, 3.0 };
		Vector4 b{ 2.0, 3.0, 4.0 };

		EXPECT_TRUE(cross(a, b) == Vector4(-1.0, 2.0, -1.0)) << "Tuple cross bad";
		EXPECT_TRUE(cross(b, a) == Vector4(1.0, -2.0, 1.0)) << "Tuple cross bad";
	}
}

namespace CanvasDrawing
{
	TEST(TupleTest, HandlesColorassignment)
	{
		Color4 c{ -0.5, 0.4, 1.7 };

		EXPECT_TRUE(is_equal(c.x, -0.5)) << "X Color4 asingment bad";
		EXPECT_TRUE(is_equal(c.y, 0.4)) << "Y Color4 asingment bad";
		EXPECT_TRUE(is_equal(c.z, 1.7)) << "Z Color4 asingment bad";
	}

	TEST(TupleTest, HandlesColorArithmetic)
	{
		Color4 c1{ 0.9, 0.6, 0.75 };
		Color4 c2{ 0.7, 0.1, 0.25 };
		Color4 c3{ 0.2, 0.3, 0.4 };

		Color4 c4 = c1 + c2;
		Color4 c5 = c1 - c2;
		Color4 c6 = c3 * 2.0;

		EXPECT_TRUE(c4 == Color4(1.6, 0.7, 1.0)) << "Color4 addition bad";
		EXPECT_TRUE(c5 == Color4(0.2, 0.5, 0.5)) << "Color4 subtraction bad";
		EXPECT_TRUE(c6 == Color4(0.4, 0.6, 0.8)) << "Color4 multiplication bad";
	}

	TEST(TupleTest, HandlesTupleHadamard)
	{
		Color4 a1{ 1.0, 0.2, 0.4 };
		Color4 a2{ 0.9, 1.0, 0.1 };

		EXPECT_TRUE(hadamard(a1, a2) == Color4(0.9, 0.2, 0.04)) << "Tuple hadamard bad";
	}

	TEST(CanvasTest, HandlesCanvas)
	{
		ImgBuf img_buf_test(20, 10);

		EXPECT_TRUE(img_buf_test.m_width == 20) << "Canvas width bad";
		EXPECT_TRUE(img_buf_test.m_height == 10) << "Canvas height bad";

		img_buf_test.write_pixel(2, 5, Color4(1, 0, 0));

		EXPECT_TRUE(img_buf_test.pixel_at(2, 5) == Color4(1.0, 0.0, 0.0)) << "Canvas pixel assignment bad";
	}
}

namespace Matrices
{
	TEST(MatrixTest, HandlesMatrixassignment)
	{
		mat4x4 a1{
			1.0 , 2.0 , 3.0 , 4.0,
			5.5 , 6.5 , 7.5 , 8.5,
			9.0 , 10.0, 11.0, 12.0,
			13.5, 14.5, 15.5, 16.5 };

		mat3x3 a2{
			-3.0,  5.0,  0.0,
			 1.0, -2.0, -7.0,
			 0.0,  1.0,  1.0
		};

		mat2x2 a3{
			-3.0,  5.0,
			 1.0, -2.0
		};

		EXPECT_TRUE(is_equal(1.0, a1.m_data[0][0])) << "Bad 4x4 assignment at 0,0";
		EXPECT_TRUE(is_equal(4.0, a1.m_data[0][3])) << "Bad 4x4 assignment at 0,3";
		EXPECT_TRUE(is_equal(5.5, a1.m_data[1][0])) << "Bad 4x4 assignment at 1,0";
		EXPECT_TRUE(is_equal(7.5, a1.m_data[1][2])) << "Bad 4x4 assignment at 1,2";
		EXPECT_TRUE(is_equal(11.0, a1.m_data[2][2])) << "Bad 4x4 assignment at 2,2";
		EXPECT_TRUE(is_equal(13.5, a1.m_data[3][0])) << "Bad 4x4 assignment at 3,0";
		EXPECT_TRUE(is_equal(15.5, a1.m_data[3][2])) << "Bad 4x4 assignment at 3,2";

		EXPECT_TRUE(is_equal(-3.0, a2.m_data[0][0])) << "Bad 3x3 assignment at 0,0";
		EXPECT_TRUE(is_equal(-2.0, a2.m_data[1][1])) << "Bad 3x3 assignment at 1,1";
		EXPECT_TRUE(is_equal(1.0, a2.m_data[2][2])) << "Bad 3x3 assignment at 2,2";

		EXPECT_TRUE(is_equal(-3.0, a3.m_data[0][0])) << "Bad 2x2 assignment at 0,0";
		EXPECT_TRUE(is_equal(5.0, a3.m_data[0][1])) << "Bad 2x2 assignment at 0,1";
		EXPECT_TRUE(is_equal(1.0, a3.m_data[1][0])) << "Bad 2x2 assignment at 1,0";
		EXPECT_TRUE(is_equal(-2.0, a3.m_data[1][1])) << "Bad 2x2 assignment at 1,1";
	}

	TEST(MatrixTest, HandlesMatrixComparison)
	{
		mat4x4 a1{
			1.0 , 2.0 , 3.0 , 4.0,
			5.0 , 6.0 , 7.0 , 8.0,
			9.0 , 10.0, 11.0, 12.0,
			13.0, 14.0, 15.0, 16.0
		};

		mat4x4 a2{
			1.0 , 2.0 , 3.0 , 4.0,
			5.0 , 6.0 , 7.0 , 8.0,
			9.0 , 10.0, 11.0, 12.0,
			13.0, 14.0, 15.0, 16.0
		};

		mat4x4 a3{
			2.0 ,3.0, 4.0 ,5.0,
			6.0 ,7.0, 8.0 ,9.0,
			8.0 ,7.0, 6.0, 5.0,
			4.0, 3.0, 2.0, 1.0
		};


		EXPECT_TRUE(a1 == a2) << "matrix equality bad";
		EXPECT_TRUE(a1 != a3) << "matrix inequality bad";
	}

	TEST(MatrixTest, HandlesMatrixMult)
	{
		mat4x4 m1{
			1.0, 2.0, 3.0, 4.0,
			5.0, 6.0, 7.0, 8.0,
			9.0, 8.0, 7.0, 6.0,
			5.0, 4.0, 3.0, 2.0
		};

		mat4x4 m2{
			-2.0, 1.0, 2.0, 3.0,
			 3.0, 2.0, 1.0,-1.0,
			 4.0, 3.0, 6.0, 5.0,
			 1.0, 2.0, 7.0, 8.0
		};

		mat4x4 m3 = m1 * m2;

		mat4x4 m4{
			20.0, 22.0, 50.0,  48.0,
			44.0, 54.0, 114.0, 108.0,
			40.0, 58.0, 110.0, 102.0,
			16.0, 26.0, 46.0,  42.0
		};

		EXPECT_TRUE(m3 == m4) << "matrix matrix multiplication bad";

		mat4x4 m5{
			1.0, 2.0, 3.0, 4.0,
			2.0, 4.0, 4.0, 2.0,
			8.0, 6.0, 4.0, 1.0,
			0.0, 0.0, 0.0, 1.0
		};

		TestTuple t1{ 1.0, 2.0, 3.0, 1.0 };
		TestTuple t2 = m5 * t1;


		EXPECT_TRUE(t2 == TestTuple(18.0, 24.0, 33.0, 1.0)) << "matrix tuple multiplication bad";
	}

	TEST(MatrixTest, HandlesMatrixIdentity)
	{
		mat4x4 a1{
			1.0 , 2.0 , 3.0 , 4.0,
			5.0 , 6.0 , 7.0 , 8.0,
			9.0 , 10.0, 11.0, 12.0,
			13.0, 14.0, 15.0, 16.0
		};

		mat4x4 a2 = a1 * i4x4;

		EXPECT_TRUE(a1 == a2) << "Identity matrix bad";
	}

	TEST(MatrixTest, HandlesMatrixTranspose)
	{
		mat4x4 a1{
			0.0, 9.0, 3.0, 0.0,
			9.0, 8.0, 0.0, 8.0,
			1.0, 8.0, 5.0, 3.0,
			0.0, 0.0, 5.0, 8.0
		};

		mat4x4 a2 = a1.transpose();

		mat4x4 a3{
			0.0, 9.0, 1.0, 0.0,
			9.0, 8.0, 8.0, 0.0,
			3.0, 0.0, 5.0, 5.0,
			0.0, 8.0, 3.0, 8.0
		};

		EXPECT_TRUE(a2 == a3) << "matrix transpose bad";
	}

	TEST(MatrixTest, HandlesMatrixDeterminants)
	{
		mat2x2 a1{
		 1.0, 5.0,
		-3.0, 2.0
		};

		double a2 = a1.determinant();

		EXPECT_TRUE(is_equal(a2, 17.0)) << "matrix 2x2 determinant bad";
	}

	TEST(MatrixTest, HandlesMatrixSubmatrix)
	{
		mat3x3 a1{
			 1.0, 5.0,  0.0,
			-3.0, 2.0,  7.0,
			 0.0, 6.0, -3.0
		};

		mat2x2 a2 = a1.submatrix(0, 2);

		mat2x2 a3{
			-3.0, 2.0,
			 0.0, 6.0
		};

		mat4x4 a4{
			-6.0, 1.0,  1.0, 6.0,
			-8.0, 5.0,  8.0, 6.0,
			-1.0, 0.0,  8.0, 2.0,
			-7.0, 1.0, -1.0, 1.0
		};

		mat3x3 a5 = a4.submatrix(2, 1);

		mat3x3 a6{
			-6.0,  1.0, 6.0,
			-8.0,  8.0, 6.0,
			-7.0, -1.0, 1.0
		};

		EXPECT_TRUE(a3 == a2) << "matrix 3x3 submatrix bad";
		EXPECT_TRUE(a6 == a5) << "matrix 4x4 submatrix bad";
	}

	TEST(MatrixTest, HandlesMatrixMinors)
	{
		mat3x3 a1{
			3.0, 5.0, 0.0,
			2.0,-1.0,-7.0,
			6.0,-1.0, 5.0
		};

		double a2 = a1.minor(1, 0);

		EXPECT_TRUE(is_equal(a2, 25.0)) << "matrix 4x4 submatrix bad";
	}

	TEST(MatrixTest, HandlesMatrixCofactor)
	{
		mat3x3 a1{
			3.0, 5.0, 0.0,
			2.0,-1.0,-7.0,
			6.0,-1.0, 5.0
		};

		double a2 = a1.cofactor(0, 0);
		double a3 = a1.cofactor(1, 0);

		EXPECT_TRUE(is_equal(a2, -12.0)) << "matrix 4x4 submatrix bad";
		EXPECT_TRUE(is_equal(a3, -25.0)) << "matrix 4x4 submatrix bad";
	}

	TEST(MatrixTest, Handles4x4Matrix)
	{
		mat3x3 a1{
			 1.0, 2.0,  6.0,
			-5.0, 8.0, -4.0,
			 2.0, 6.0,  4.0
		};

		mat4x4 a2{
			-2.0, -8.0,  3.0,  5.0,
			-3.0,  1.0,  7.0,  3.0,
			 1.0,  2.0, -9.0,  6.0,
			-6.0,  7.0,  7.0, -9.0
		};

		double a3 = a1.cofactor(0, 0);
		double a4 = a1.cofactor(0, 1);
		double a5 = a1.cofactor(0, 2);
		double a6 = a1.determinant();

		double a7 = a2.cofactor(0, 0);
		double a8 = a2.cofactor(0, 1);
		double a9 = a2.cofactor(0, 2);
		double a10 = a2.cofactor(0, 3);
		double a11 = a2.determinant();

		EXPECT_TRUE(is_equal(a3, 56.0)) << "matrix 3x3 cofactor bad";
		EXPECT_TRUE(is_equal(a4, 12.0)) << "matrix 3x3 cofactor bad";
		EXPECT_TRUE(is_equal(a5, -46.0)) << "matrix 3x3 cofactor bad";
		EXPECT_TRUE(is_equal(a6, -196.0)) << "matrix 3x3 determinant bad";

		EXPECT_TRUE(is_equal(a7, 690.0)) << "matrix 4x4 cofactor bad";
		EXPECT_TRUE(is_equal(a8, 447.0)) << "matrix 4x4 cofactor bad";
		EXPECT_TRUE(is_equal(a9, 210.0)) << "matrix 4x4 cofactor bad";
		EXPECT_TRUE(is_equal(a10, 51.0)) << "matrix 4x4 cofactor bad";
		EXPECT_TRUE(is_equal(a11, -4071.0)) << "matrix 4x4 determinant bad";
	}

	TEST(MatrixTest, HandlesMatrixInverse)
	{
		mat4x4 a1{
			-5.0,  2.0,  6.0, -8.0,
			 1.0, -5.0,  1.0,  8.0,
			 7.0,  7.0, -6.0, -7.0,
			 1.0, -3.0,  7.0,  4.0
		};
		mat4x4 a2 = a1.inverse();
		mat4x4 a3 = {
			  0.21805,  0.45113,  0.24060, -0.04511,
			 -0.80827, -1.45677, -0.44361,  0.52068,
			 -0.07895, -0.22368, -0.05263,  0.19737,
			 -0.52256, -0.81391, -0.30075,  0.30639
		};

		EXPECT_TRUE(a2 == a3) << "matrix 4x4 inverse bad";

		mat4x4 a4{
			 3.0, -9.0,  7.0,  3.0,
			 3.0, -8.0,  2.0, -9.0,
			-4.0,  4.0,  4.0,  1.0,
			-6.0,  5.0, -1.0,  1.0
		};
		mat4x4 a5{
			8.0,  2.0, 2.0, 2.0,
			3.0, -1.0, 7.0, 0.0,
			7.0,  0.0, 5.0, 4.0,
			6.0, -2.0, 0.0, 5.0
		};
		mat4x4 a6 = a4 * a5;


		EXPECT_TRUE(a6 * a5.inverse() == a4) << "matrix 4x4 inverse bad";
	}
}

namespace MatrixTransform
{
	TEST(TransformationTest, HandlesTranslation)
	{
		mat4x4 a1 = translation(5.0, -3.0, 2.0);
		Point4 a2{ -3.0, 4.0, 5.0 };
		Point4 a3 = a1 * a2;

		Vector4 a4{ -3.0, 4.0, 5.0 };
		Vector4 a5 = a1 * a4;

		EXPECT_TRUE(a3 == Point4(2.0, 1.0, 7.0)) << "translation bad";
		EXPECT_TRUE(a4 == a5) << "translation bad";
	}

	TEST(TransformationTest, HandlesScaling)
	{
		mat4x4 a1 = scaling(2.0, 3.0, 4.0);
		Point4 a2{ -4.0, 6.0, 8.0 };
		Point4 a3 = a1 * a2;

		Vector4 a4{ -4.0, 6.0, 8.0 };
		Vector4 a5 = a1 * a4;

		EXPECT_TRUE(a3 == Point4(-8.0, 18.0, 32.0)) << "scaling bad";
		EXPECT_TRUE(a5 == Vector4(-8.0, 18.0, 32.0)) << "scaling bad";
	}

	TEST(TransformationTest, HandlesRotation)
	{
		double deg90 = PI / 2.0;
		double deg45 = PI / 4.0;

		mat4x4 a1 = rotation(deg90, 0.0, 0.0);
		Point4 a2{ 0.0, 1.0, 0.0 };

		mat4x4 a3 = rotation(0.0, deg90, 0.0);
		Point4 a4{ 0.0, 0.0, 1.0 };

		mat4x4 a5 = rotation(0.0, 0.0, deg90);
		Point4 a6{ 0.0, 1.0, 0.0 };

		Point4 a7 = a1 * a2;
		Point4 a8 = a3 * a4;
		Point4 a9 = a5 * a6;

		EXPECT_TRUE(a7 == Point4(0.0, 0.0, 1.0)) << "rotation bad";
		EXPECT_TRUE(a8 == Point4(1.0, 0.0, 0.0)) << "rotation bad";
		EXPECT_TRUE(a9 == Point4(-1.0, 0.0, 0.0)) << "rotation bad";

		mat4x4 a10 = rotation(deg45, 0.0, deg45);
		Point4 a11{ 0.0, 1.0, 0.0 };

		Point4 a12 = a10 * a11;

		EXPECT_TRUE(a12 == Point4(-0.5, 0.5, 0.7071)) << "rotation bad";
	}

	TEST(TransformationTest, HandlesShearing)
	{
		Point4 a1{ 2.0, 3.0, 4.0 };

		mat4x4 a2 = shearing(1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		mat4x4 a3 = shearing(0.0, 1.0, 0.0, 0.0, 0.0, 0.0);
		mat4x4 a4 = shearing(0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
		mat4x4 a5 = shearing(0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
		mat4x4 a6 = shearing(0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		mat4x4 a7 = shearing(0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

		EXPECT_TRUE(a2 * a1 == Point4(5.0, 3.0, 4.0)) << "shearing bad";
		EXPECT_TRUE(a3 * a1 == Point4(6.0, 3.0, 4.0)) << "shearing bad";
		EXPECT_TRUE(a4 * a1 == Point4(2.0, 5.0, 4.0)) << "shearing bad";
		EXPECT_TRUE(a5 * a1 == Point4(2.0, 7.0, 4.0)) << "shearing bad";
		EXPECT_TRUE(a6 * a1 == Point4(2.0, 3.0, 6.0)) << "shearing bad";
		EXPECT_TRUE(a7 * a1 == Point4(2.0, 3.0, 7.0)) << "shearing bad";
	}

	TEST(TransformationTest, HandlesMultipleTransform)
	{
		Point4 a1{ 1.0, 0.0, 1.0 };

		mat4x4 a2 = rotation(PI / 2.0, 0.0, 0.0);
		mat4x4 a3 = scaling(5.0, 5.0, 5.0);
		mat4x4 a4 = translation(10.0, 5.0, 7.0);

		Point4 a5 = (a4 * a3 * a2) * a1;

		EXPECT_TRUE(a5 == Point4(15.0, 0.0, 7.0)) << "shearing bad";
	}
}

namespace RaySphereIntersect
{
	TEST(RayTest, HandlesRayCreation)
	{
		Point4 a1{ Point4(1.0, 2.0, 3.0) };
		Vector4 a2{ Vector4(4.0, 5.0, 6.0) };
		Ray a3{ PVpair(a1, a2) };
		Ray a4{ PVpair(Point4(2.0, 3.0, 4.0), Vector4(1.0, 0.0, 0.0)) };

		EXPECT_TRUE(a3.m_origin_dir.origin == a1) << "Ray origin bad";
		EXPECT_TRUE(a3.m_origin_dir.direction == a2) << "Ray direction bad";
		EXPECT_TRUE(a4.position(0.0) == Point4(2.0, 3.0, 4.0)) << "Ray position bad";
		EXPECT_TRUE(a4.position(1.0) == Point4(3.0, 3.0, 4.0)) << "Ray position bad";
		EXPECT_TRUE(a4.position(-1.0) == Point4(1.0, 3.0, 4.0)) << "Ray position bad";
		EXPECT_TRUE(a4.position(2.5) == Point4(4.5, 3.0, 4.0)) << "Ray position bad";
	}

	TEST(RayTest, HandlesRaySphereIntersection)
	{
		Ray a1{ PVpair(Point4(0.0, 0.0, -5.0), Vector4(0.0, 0.0, 1.0)) };
		Sphere a2;
		a1.intersect(&a2);

		EXPECT_TRUE(a1.m_intersections.size() == 2) << "Ray Sphere Intersection bad";
		EXPECT_TRUE(is_equal(a1.m_intersections[0].m_time, 4.0)) << "Ray Sphere Intersection bad";
		EXPECT_TRUE(is_equal(a1.m_intersections[1].m_time, 6.0)) << "Ray Sphere Intersection bad";

		Ray a3{ PVpair(Point4(0.0, 1.0, -5.0), Vector4(0.0, 0.0, 1.0)) };
		Sphere a4;
		a3.intersect(&a4);

		EXPECT_TRUE(a3.m_intersections.size() == 2) << "Ray Sphere Intersection bad";
		EXPECT_TRUE(is_equal(a3.m_intersections[0].m_time, 5.0)) << "Ray Sphere Intersection bad";
		EXPECT_TRUE(is_equal(a3.m_intersections[1].m_time, 5.0)) << "Ray Sphere Intersection bad";

		Ray a5{ PVpair(Point4(0.0, 2.0, -5.0), Vector4(0.0, 0.0, 1.0)) };
		Sphere a6;
		a5.intersect(&a6);

		EXPECT_TRUE(a5.m_intersections.size() == 0) << "Ray Sphere Intersection bad";

		Ray a7{ PVpair(Point4(0.0, 0.0, 0.0), Vector4(0.0, 0.0, 1.0)) };
		Sphere a8;
		a7.intersect(&a8);

		EXPECT_TRUE(is_equal(a7.m_intersections[0].m_time, -1.0)) << "Ray Sphere Intersection bad";
		EXPECT_TRUE(is_equal(a7.m_intersections[1].m_time, 1.0)) << "Ray Sphere Intersection bad";

		Ray a9{ PVpair(Point4(0.0, 0.0, 5.0), Vector4(0.0, 0.0, 1.0)) };
		Sphere a10;
		a9.intersect(&a10);

		EXPECT_TRUE(is_equal(a9.m_intersections[0].m_time, -6.0)) << "Ray Sphere Intersection bad";
		EXPECT_TRUE(is_equal(a9.m_intersections[1].m_time, -4.0)) << "Ray Sphere Intersection bad";
	}

	TEST(RayTest, HandlesRayIntersection)
	{
		Sphere a1;
		Intersection a2{ 0.0, &a1 };

		EXPECT_TRUE(is_equal(a2.m_time, 0.0)) << "Ray Sphere Intersection bad";
	}

	TEST(RayTest, HandlesRayHits)
	{
		Sphere a1;
		Ray a2;
		Intersection a3{ -2.0, &a1 };
		Intersection a4{ -1.0, &a1 };
		a2.add_intersection(a4);
		a2.add_intersection(a3);
		Intersection a5 = a2.hit();

		EXPECT_TRUE(a5.m_time == INFINITY) << "Ray hits bad";

		Intersection a6{  5.0, &a1 };
		Intersection a7{  7.0, &a1 };
		Intersection a8{ -3.0, &a1 };
		Intersection a9{  2.0, &a1 };
		Ray a10;
		a10.add_intersection(a6);
		a10.add_intersection(a7);
		a10.add_intersection(a8);
		a10.add_intersection(a9);
		Intersection a11 = a10.hit();

		EXPECT_TRUE(a11.m_time == a9.m_time) << "Ray hits bad";
		EXPECT_TRUE(a11.m_obj == a9.m_obj) << "Ray hits bad";
	}

	TEST(RayTest, HandlesRayScale)
	{
		Ray a1{ PVpair(Point4(0.0, 0.0, -5.0), Vector4(0.0, 0.0, 1.0)) };
		Sphere a2{ scaling(2.0, 2.0, 2.0) };
		a1.intersect(&a2);

		EXPECT_TRUE(is_equal(a1.m_intersections[0].m_time, 3.0)) << "Ray hits bad";
		EXPECT_TRUE(is_equal(a1.m_intersections[1].m_time, 7.0)) << "Ray hits bad";
	}
}

namespace LightAndShading
{
	TEST(LightingTest, HandlesNormals)
	{
		Sphere a1;

		Point4 p1{ 1.0, 0.0, 0.0 };
		Vector4 v1{ 1.0, 0.0, 0.0 };
		Ray r1{ PVpair{ Point4(0.0, 0.0, 0.0) + 2 * v1, -v1} };
		EXPECT_TRUE(a1.normal_at_local(p1) == v1) << "normal bad";

		Point4 p2{ 0.0, 1.0, 0.0 };
		Vector4 v2{ 0.0, 1.0, 0.0 };
		EXPECT_TRUE(a1.normal_at_local(p2) == v2) << "normal bad";

		Point4 p3{ 0.0, 0.0, 1.0 };
		Vector4 v3{ 0.0, 0.0, 1.0 };
		EXPECT_TRUE(a1.normal_at_local(p3) == v3) << "normal bad";

		Point4 p4{ sqrt(3.0) / 3.0, sqrt(3.0) / 3.0, sqrt(3.0) / 3.0 };
		Vector4 v4{ sqrt(3.0) / 3.0, sqrt(3.0) / 3.0, sqrt(3.0) / 3.0 };
		EXPECT_TRUE(a1.normal_at_local(p4) == v4) << "normal bad";

		//Sphere a2{ translation(0.0, 1.0, 0.0) };
		//Point4 p5{ 0.0, 1.70711, -0.70711 };
		//Vector4 a3 = a2.normal_at_local(p5);
		//EXPECT_TRUE(a3 == Vector4(0, 0.70711, -0.70711)) << "normal bad";

		//Sphere a4{ scaling(1.0, 0.5, 1.0) * rotation(0.0, 0.0, PI / 5.0) };
		//Point4 p6{ 0.0, sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0 };
		//Vector4 a5 = a4.normal_at_local(p6);
		//EXPECT_TRUE(a5 == Vector4(0.0, 0.97014, -0.24254)) << "normal bad";
	}

	TEST(LightingTest, HandlesReflections)
	{
		Vector4 a1{ Vector4(1.0, -1.0, 0.0) };
		Vector4 a2{ Vector4(0.0, 1.0, 0.0) };
		Vector4 a3 = reflect(a1, a2);

		EXPECT_TRUE(a3 == Vector4(1.0, 1.0, 0.0)) << "reflection bad";

		Vector4 a4{ Vector4(0.0, -1.0, 0.0) };
		Vector4 a5{ Vector4(sqrt(2.0) / 2.0, sqrt(2.0) / 2.0, 0.0) };
		Vector4 a6 = reflect(a4, a5);

		EXPECT_TRUE(a6 == Vector4(1.0, 0.0, 0.0)) << "reflection bad";
	}

	TEST(LightingTest, HandlesPointLight)
	{
		Light a1{ Point4(0.0, 0.0, 0.0), Color4(1.0, 1.0, 1.0) };

		EXPECT_TRUE(a1.m_pos == Point4(0.0, 0.0, 0.0)) << "Point4 light position bad";
		EXPECT_TRUE(a1.m_intensity == Color4(1.0, 1.0, 1.0)) << "Point4 light intensity bad";
	}

	TEST(LightingTest, HandlesMaterials)
	{
		Sphere a1;
		Material a2;

		Point4 p1{ 0.0, 0.0, 0.0 };

		EXPECT_TRUE(pattern_at(a1.m_material.m_pattern, p1) == pattern_at(a2.m_pattern, p1)) << "Material albedo bad";
		EXPECT_TRUE(a1.m_material.m_ambient == a2.m_ambient) << "Material ambient bad";
		EXPECT_TRUE(a1.m_material.m_diffuse == a2.m_diffuse) << "Material diffuse bad";
		EXPECT_TRUE(a1.m_material.m_shininess == a2.m_shininess) << "Material shininess bad";
		EXPECT_TRUE(a1.m_material.m_specular == a2.m_specular) << "Material specular bad";
	}

	TEST(LightingTest, HandlesLightCalculation)
	{
		Material m1;
		Sphere s{ m1 };
		Intersection i{ 0.0, &s };
		Point4 a0{ Point4(0.0, 0.0, 0.0) };
		Vector4 a1{ Vector4(0.0, 0.0, -1.0) };
		Vector4 a2{ Vector4(0.0, 0.0, -1.0) };
		Light a3{ Point4(0.0, 0.0, -10.0), Color4(1.0, 1.0, 1.0) };
		Color4 a4{ lighting(i, a3, a0, a1, a2) };

		EXPECT_TRUE(a4 == Color4(1.9, 1.9, 1.9)) << "Material albedo bad";

		Vector4 a5{ Vector4(0.0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0) };
		Vector4 a6{ Vector4(0.0, 0.0, -1.0) };
		Light a7{ Point4(0.0, 0.0, -10.0), Color4(1.0, 1.0, 1.0) };
		Color4 a8{ lighting(i, a7, a0, a5, a6) };

		EXPECT_TRUE(a8 == Color4(1.0, 1.0, 1.0)) << "Material albedo bad";

		Vector4 a9{ Vector4(0.0, 0.0, -1.0) };
		Vector4 a10{ Vector4(0.0, 0.0, -1.0) };
		Light a11{ Point4(0.0, 10.0, -10.0), Color4(1.0, 1.0, 1.0) };
		Color4 a12{ lighting(i, a11, a0, a9, a10) };

		EXPECT_TRUE(a12 == Color4(0.7364, 0.7364, 0.7364)) << "Material albedo bad";

		Vector4 a13{ Vector4(0.0, -sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0) };
		Vector4 a14{ Vector4(0.0, 0.0, -1.0) };
		Light a15{ Point4(0.0, 10.0, -10.0), Color4(1.0, 1.0, 1.0) };
		Color4 a16{ lighting(i, a15, a0, a13, a14) };

		EXPECT_TRUE(a16 == Color4(1.6364, 1.6364, 1.6364)) << "Material albedo bad";

		Vector4 a17{ Vector4(0.0, 0.0, 1.0) };
		Vector4 a18{ Vector4(0.0, 0.0, -1.0) };
		Light a19{ Point4(0.0, 0.0, 10.0), Color4(1.0, 1.0, 1.0) };
		Color4 a20{ lighting(i, a19, a0, a17, a18) };

		EXPECT_TRUE(a20 == Color4(0.1, 0.1, 0.1)) << "Material albedo bad";
	}
}

namespace Scene
{
	TEST(WorldTest, HandlesWorldIntersection)
	{
		World w1;
		Light l{ Point4(-10.0, 10.0, -10.0), Color4(1.0, 1.0, 1.0) };
		w1.add_light(l);
		Sphere s1{ Material{ Color4(0.8, 1.0, 0.6) } };
		w1.add_object(s1);
		w1.m_shapes[0]->m_material.m_diffuse = 0.7;
		w1.m_shapes[0]->m_material.m_specular = 0.2;
		Sphere s2{ scaling(0.5, 0.5, 0.5) };
		w1.add_object(s2);

		Ray r1{ PVpair(Point4(0.0, 0.0, -5.0), Vector4(0.0, 0.0, 1.0)) };
		intersect(w1, r1);
		EXPECT_TRUE(r1.m_intersections.size() == 4) << "World intersect bad";
		EXPECT_TRUE(is_equal(r1.m_intersections[0].m_time, 4.0)) << "World intersect bad";
		EXPECT_TRUE(is_equal(r1.m_intersections[2].m_time, 4.5)) << "World intersect bad";
		EXPECT_TRUE(is_equal(r1.m_intersections[3].m_time, 5.5)) << "World intersect bad";
		EXPECT_TRUE(is_equal(r1.m_intersections[1].m_time, 6.0)) << "World intersect bad";
	}

	TEST(WorldTest, HandlesCompData)
	{
		Ray r1{ PVpair(Point4(0.0, 0.0, -5.0), Vector4(0.0, 0.0, 1.0)) };
		Sphere s1;
		Intersection i1{ 1.0, &s1 };
		r1.add_intersection(i1);
		CompData c1 = r1.get_comp_data();

		EXPECT_TRUE(c1.is_inside == false) << "Bad inside";

		Ray r2{ PVpair(Point4(0.0, 0.0, 0.0), Vector4(0.0, 0.0, 1.0)) };
		Sphere s2;
		Intersection i2{ 1.0, &s2 };
		r2.add_intersection(i2);
		CompData c2 = r2.get_comp_data();

		EXPECT_TRUE(c2.is_inside == true) << "Bad inside";
		EXPECT_TRUE(c2.pt == Point4(0.0, 0.0, 1.0)) << "Bad computed data";
		EXPECT_TRUE(c2.eyev == Vector4(0.0, 0.0, -1.0)) << "Bad computed data";
		EXPECT_TRUE(c2.normalv == Vector4(0.0, 0.0, -1.0)) << "Bad computed data";
	}

	TEST(WorldTest, HandlesWorldShading)
	{
		World w1;
		Light l{ Point4(-10.0, 10.0, -10.0), Color4(1.0, 1.0, 1.0) };
		w1.add_light(l);
		Sphere s1{ Material{ Color4(0.8, 1.0, 0.6) } };
		w1.add_object(s1);
		w1.m_shapes[0]->m_material.m_diffuse = 0.7;
		w1.m_shapes[0]->m_material.m_specular = 0.2;
		Sphere s2{ scaling(0.5, 0.5, 0.5) };
		w1.add_object(s2);

		Ray r1{ PVpair(Point4(0.0, 0.0, -5.0), Vector4(0.0, 0.0, 1.0)) };
		Intersection i1{ 4.0, w1.m_shapes[0] };
		r1.add_intersection(i1);
		CompData cd1 = r1.get_comp_data();
		Color4 c1 = w1.shade_hit(cd1, 1);
		EXPECT_TRUE(c1 == Color4(0.38066, 0.47583, 0.2855)) << "Shading bad";

		w1.m_point_lights[0] = Light{ Point4(0.0, 0.25, 0.0), Color4(1.0, 1.0, 1.0) };
		Ray r2{ PVpair(Point4(0.0, 0.0, 0.0), Vector4(0.0, 0.0, 1.0)) };
		Intersection i2{ 0.5, w1.m_shapes[1] };
		r2.add_intersection(i2);
		CompData cd2 = r2.get_comp_data();
		Color4 c2 = w1.shade_hit(cd2, 1);
		EXPECT_TRUE(c2 == Color4(0.90498, 0.90498, 0.90498)) << "Shading bad";

		w1.m_point_lights[0] = Light{ Point4(-10.0, 10.0, -10.0), Color4(1.0, 1.0, 1.0) };
		Ray r3 = Ray(PVpair(Point4(0.0, 0.0, -5.0), Vector4(0.0, 0.0, 1.0)));
		Color4 c3 = color_at(w1, r3, 1);
		EXPECT_TRUE(c3 == Color4(0.38066, 0.47583, 0.2855)) << "Shading bad";

		Ray r4 = Ray(PVpair(Point4(0.0, 0.0, 0.75), Vector4(0.0, 0.0, -1.0)));
		w1.m_shapes[0]->m_material.m_ambient = 1.0;
		w1.m_shapes[1]->m_material.m_ambient = 1.0;
		Color4 c4 = color_at(w1, r4, 1);
		Point4 p(0.0, 0.0, 0.0);
		EXPECT_TRUE(c4 == pattern_at(w1.m_shapes[1]->m_material.m_pattern, p)) << "Shading bad";
	}

	TEST(WorldTest, HandlesViewTransform)
	{
		Point4 fr1{ 0.0, 0.0, 0.0 };
		Point4 to1{ 0.0, 0.0, -1.0 };
		Vector4 up1{ 0.0, 1.0, 0.0 };
		mat4x4 t1 = view_transform(fr1, to1, up1);
		EXPECT_TRUE(t1 == i4x4) << "View transform bad";

		Point4 fr2{ 0.0, 0.0, 0.0 };
		Point4 to2{ 0.0, 0.0, 1.0 };
		Vector4 up2{ 0.0, 1.0, 0.0 };
		mat4x4 t2 = view_transform(fr2, to2, up2);
		EXPECT_TRUE(t2 == scaling(-1.0, 1.0, -1.0)) << "View transform bad";

		Point4 fr3{ 0.0, 0.0, 8.0 };
		Point4 to3{ 0.0, 0.0, 0.0 };
		Vector4 up3{ 0.0, 1.0, 0.0 };
		mat4x4 t3 = view_transform(fr3, to3, up3);
		EXPECT_TRUE(t3 == translation(0.0, 0.0, -8.0)) << "View transform bad";

		Point4 fr4{ 1.0, 3.0, 2.0 };
		Point4 to4{ 4.0, -2.0, 8.0 };
		Vector4 up4{ 1.0, 1.0, 0.0 };
		mat4x4 t4 = view_transform(fr4, to4, up4);
		mat4x4 t4res{
			-0.50709, 0.50709,  0.67612, -2.36643,
			 0.76772, 0.60609,  0.12122, -2.82843,
			-0.35857, 0.59761, -0.71714,  0.00000,
			 0.00000, 0.00000,  0.00000,  1.00000
		};
		EXPECT_TRUE(t4 == t4res) << "View transform bad";
	}

	TEST(CameraTest, HandlesCameraCreation)
	{
		Camera c{ 160, 120, PI / 2.0 };

		EXPECT_TRUE(c.m_hsize == 160) << "Camera creation bad";
		EXPECT_TRUE(c.m_vsize == 120) << "Camera creation bad";
		EXPECT_TRUE(is_equal(c.m_fov, PI / 2.0)) << "Camera creation bad";
		EXPECT_TRUE(c.m_transform == i4x4) << "Camera creation bad";

		Camera c2{ 200, 125, PI / 2.0 };
		EXPECT_TRUE(is_equal(c2.m_pixel_size, 0.01)) << "Camera creation bad";

		Camera c3{ 125, 200, PI / 2.0 };
		EXPECT_TRUE(is_equal(c3.m_pixel_size, 0.01)) << "Camera creation bad";
	}

	TEST(CameraTest, HandlesRayPerPixel)
	{
		Camera c1{ 201, 101, PI / 2.0 };
		Ray r1 = c1.ray_for_pixel(100, 50);
		EXPECT_TRUE(r1.m_origin_dir.origin == Point4(0.0, 0.0, 0.0)) << "Pixel ray bad";
		EXPECT_TRUE(r1.m_origin_dir.direction == Vector4(0.0, 0.0, -1.0)) << "Pixel ray bad";

		Camera c2{ 201, 101, PI / 2.0 };
		Ray r2 = c2.ray_for_pixel(0, 0);
		EXPECT_TRUE(r2.m_origin_dir.origin == Point4(0.0, 0.0, 0.0)) << "Pixel ray bad";
		EXPECT_TRUE(r2.m_origin_dir.direction == Vector4(0.66519, 0.33259, -0.66851)) << "Pixel ray bad";

		Camera c3{ 201, 101, PI / 2.0 };
		c3.m_transform = rotation(0.0, PI / 4.0, 0.0) * translation(0.0, -2.0, 5.0);
		Ray r3 = c3.ray_for_pixel(100, 50);
		EXPECT_TRUE(r3.m_origin_dir.origin == Point4(0.0, 2.0, -5.0)) << "Pixel ray bad";
		EXPECT_TRUE(r3.m_origin_dir.direction == Vector4(sqrt(2.0) / 2.0, 0.0, -sqrt(2.0) / 2.0)) << "Pixel ray bad";
	}

	TEST(RenderTest, HandlesRendering)
	{
		World w = default_world();
		Camera c{ 11, 11, PI / 2.0 };
		c.m_transform = view_transform(Point4(0.0, 0.0, -5.0), Point4(0.0, 0.0, 0.0), Vector4(0.0, 1.0, 0.0));
		ImgBuf img{ test_render(c, w, 1) };
		Color4 res = img.pixel_at(5, 5);
		EXPECT_TRUE(res == Color4(0.38066, 0.47583, 0.2855)) << "Rendering bad";
	}
}

namespace Shadows
{
	TEST(ShadowTest, HandlesShadow)
	{
		Material mat;
		Sphere s{ mat };
		Intersection i{ 0.0, &s };

		Point4 pos{ Point4(0.0, 0.0, 0.0) };
		Vector4 eyev{ Vector4(0.0, 0.0, -1.0) };
		Vector4 normalv{ Vector4(0.0, 0.0, -1.0) };
		Light light{ Light{ Point4(0.0, 0.0, -10.0), Color4(1.0, 1.0, 1.0) } };
		bool in_shadow = true;
		Color4 col = lighting(i, light, pos, eyev, normalv, in_shadow);

		EXPECT_TRUE(col == Color4(0.1, 0.1, 0.1)) << "Shadow bad";

		World w1 = default_world();
		Point4 p1{ 0.0, 10.0, 0.0 };
		EXPECT_FALSE(is_shadowed(w1, p1, w1.m_point_lights[0])) << "Shadow bad";

		World w2 = default_world();
		Point4 p2{ 10.0, -10.0, 10.0 };
		EXPECT_TRUE(is_shadowed(w2, p2, w2.m_point_lights[0])) << "Shadow bad";

		World w3 = default_world();
		Point4 p3{ -20.0, 20.0, -20.0 };
		EXPECT_FALSE(is_shadowed(w3, p3, w3.m_point_lights[0])) << "Shadow bad";

		World w4 = default_world();
		Point4 p4{ -2.0, 2.0, -2.0 };
		EXPECT_FALSE(is_shadowed(w4, p4, w4.m_point_lights[0])) << "Shadow bad";
	}
}

namespace Planes
{
	TEST(ShapesTest, HandlesSphere)
	{
		Sphere sph;

		EXPECT_TRUE(sph.m_transform == i4x4) << "Sphere bad";
	}

	TEST(ShapesTest, HandlesPlane)
	{
		Plane pl1;
		Ray r1{ PVpair(Point4(0.0, 10.0, 0.0), Vector4(0.0, 0.0, 1.0)) };
		r1.intersect(&pl1);
		EXPECT_TRUE(r1.m_intersections.size() == 0) << "Plane intersection bad";

		Plane pl2;
		Ray r2{ PVpair(Point4(0.0, 0.0, 0.0), Vector4(0.0, 0.0, 1.0)) };
		r2.intersect(&pl2);
		EXPECT_TRUE(r2.m_intersections.size() == 0) << "Plane intersection bad";

		Plane pl3;
		Ray r3{ PVpair(Point4(0.0, 1.0, 0.0), Vector4(0.0, -1.0, 0.0)) };
		r3.intersect(&pl3);
		EXPECT_TRUE(r3.m_intersections.size() == 1) << "Plane intersection bad";
		EXPECT_TRUE(r3.m_intersections[0].m_time == 1.0) << "Plane intersection bad";

		Plane pl4;
		Ray r4{ PVpair(Point4(0.0, -1.0, 0.0), Vector4(0.0, 1.0, 1.0)) };
		r4.intersect(&pl4);
		EXPECT_TRUE(r4.m_intersections.size() == 1) << "Plane intersection bad";
		EXPECT_TRUE(r4.m_intersections[0].m_time == 1.0) << "Plane intersection bad";
	}
}

namespace Patterns
{
	TEST(PatternTest, HandlesStripe)
	{
		Pattern pat{ stripe_pattern(WHITE, BLACK) };

		EXPECT_TRUE(pat.m_col1 == WHITE) << "stripe pattern bad";
		EXPECT_TRUE(pat.m_col2 == BLACK) << "stripe pattern bad";

		Point4 p1(0.0, 0.0, 0.0);
		Point4 p2(0.0, 1.0, 0.0);
		Point4 p3(0.0, 2.0, 0.0);
		EXPECT_TRUE(pattern_at(pat, p1) == WHITE) << "stripe pattern bad";
		EXPECT_TRUE(pattern_at(pat, p2) == WHITE) << "stripe pattern bad";
		EXPECT_TRUE(pattern_at(pat, p3) == WHITE) << "stripe pattern bad";

		Point4 p4(0.0, 0.0, 0.0);
		Point4 p5(0.0, 0.0, 1.0);
		Point4 p6(0.0, 0.0, 2.0);
		EXPECT_TRUE(pattern_at(pat, p4) == WHITE) << "stripe pattern bad";
		EXPECT_TRUE(pattern_at(pat, p5) == WHITE) << "stripe pattern bad";
		EXPECT_TRUE(pattern_at(pat, p6) == WHITE) << "stripe pattern bad";

		Point4 p7(0.0, 0.0, 0.0);
		Point4 p8(0.9, 0.0, 0.0);
		Point4 p9(1.0, 0.0, 0.0);
		Point4 p10(-0.1, 0.0, 0.0);
		Point4 p11(-1.0, 0.0, 0.0);
		Point4 p12(-1.1, 0.0, 0.0);
		EXPECT_TRUE(pattern_at(pat, p7) == WHITE) << "stripe pattern bad";
		EXPECT_TRUE(pattern_at(pat, p8) == WHITE) << "stripe pattern bad";
		EXPECT_TRUE(pattern_at(pat, p9) == BLACK) << "stripe pattern bad";
		EXPECT_TRUE(pattern_at(pat, p10) == BLACK) << "stripe pattern bad";
		EXPECT_TRUE(pattern_at(pat, p11) == BLACK) << "stripe pattern bad";
		EXPECT_TRUE(pattern_at(pat, p12) == WHITE) << "stripe pattern bad";
	}

	TEST(PatternTest, HandleLighting)
	{
		Material mat;
		mat.m_pattern = stripe_pattern(WHITE, BLACK);
		mat.m_ambient = 1.0;
		mat.m_diffuse = 0.0;
		mat.m_specular = 0.0;

		Sphere s{ mat };
		Intersection i{ 0.0, &s };

		Vector4 eyev{ 0.0, 0.0, -1.0 };
		Vector4 normalv{ 0.0, 0.0, -1.0 };
		Light lght{ Point4{ 0.0, 0.0, -10.0 }, Color4{ 1.0, 1.0, 1.0 } };

		Point4 pt1{ 0.9, 0.0, 0.0 };
		Color4 colt1 = lighting(i, lght, pt1, eyev, normalv, false);

		Point4 pt2{ 1.1, 0.0, 0.0 };
		Color4 colt2 = lighting(i, lght, pt2, eyev, normalv, false);

		EXPECT_TRUE(colt1 == WHITE) << "Lighting stripe pattern bad";
		EXPECT_TRUE(colt2 == BLACK) << "Lighting stripe pattern bad";
	}

	TEST(PatternTest, HandleTransform)
	{
		Sphere sph1{ Material{ stripe_pattern(WHITE, BLACK) }, 
					 scaling(2.0, 2.0, 2.0) };

		Point4 p1(1.5, 0.0, 0.0);
		Color4 c1{ pattern_at_shape(sph1.m_transform, sph1.m_material, p1) };
		EXPECT_TRUE(c1 == WHITE) << "Lighting stripe pattern bad";

		Sphere sph2{ Material{ stripe_pattern(WHITE, BLACK, scaling(2.0, 2.0, 2.0)) } };
		Point4 p2(1.5, 0.0, 0.0);
		Color4 c2{ pattern_at_shape(sph2.m_transform, sph2.m_material, p2) };
		EXPECT_TRUE(c2 == WHITE) << "Lighting stripe pattern bad";

		Sphere sph3{ Material{ stripe_pattern(WHITE, BLACK, translation(0.5, 0.0, 0.0)) }, 
					 scaling(2.0, 2.0, 2.0) };
		Point4 p3(2.5, 0.0, 0.0);
		Color4 c3{ pattern_at_shape(sph3.m_transform, sph3.m_material, p3) };
		EXPECT_TRUE(c3 == WHITE) << "Lighting stripe pattern bad";
	}

	TEST(PatternTest, HandleGradient)
	{
		Pattern pat{ gradient_pattern(WHITE, BLACK) };
		Point4 p1(0.00, 0.0, 0.0);
		Point4 p2(0.25, 0.0, 0.0);
		Point4 p3(0.50, 0.0, 0.0);
		Point4 p4(0.75, 0.0, 0.0);

		EXPECT_TRUE(pattern_at(pat, p1) == WHITE) << "Gradient pattern bad";
		EXPECT_TRUE(pattern_at(pat, p2) == Color4(0.75, 0.75, 0.75)) << "Gradient pattern bad";
		EXPECT_TRUE(pattern_at(pat, p3) == Color4(0.5, 0.5, 0.5)) << "Gradient pattern bad";
		EXPECT_TRUE(pattern_at(pat, p4) == Color4(0.25, 0.25, 0.25)) << "Gradient pattern bad";
	}

	TEST(PatternTest, HandleRing)
	{
		Pattern pat{ ring_pattern(WHITE, BLACK) };

		Point4 p1(0.0, 0.0, 0.0);
		Point4 p2(1.0, 0.0, 0.0);
		Point4 p3(0.0, 0.0, 1.0);
		Point4 p4(0.708, 0.0, 0.708);
		EXPECT_TRUE(pattern_at(pat, p1) == WHITE) << "Gradient pattern bad";
		EXPECT_TRUE(pattern_at(pat, p2) == BLACK) << "Gradient pattern bad";
		EXPECT_TRUE(pattern_at(pat, p3) == BLACK) << "Gradient pattern bad";
		EXPECT_TRUE(pattern_at(pat, p4) == BLACK) << "Gradient pattern bad";
	}

	TEST(PatternTest, HandleCheckers)
	{
		Pattern pat{ checkers_pattern(WHITE, BLACK) };

		Point4 p1(0.00, 0.0, 0.0);
		Point4 p2(0.99, 0.0, 0.0);
		Point4 p3(1.01, 0.0, 0.0);
		EXPECT_TRUE(pattern_at(pat, p1) == WHITE) << "Gradient pattern bad";
		EXPECT_TRUE(pattern_at(pat, p2) == WHITE) << "Gradient pattern bad";
		EXPECT_TRUE(pattern_at(pat, p3) == BLACK) << "Gradient pattern bad";

		Point4 p4(0.0, 0.00, 0.0);
		Point4 p5(0.0, 0.99, 0.0);
		Point4 p6(0.0, 1.01, 0.0);
		EXPECT_TRUE(pattern_at(pat, p4) == WHITE) << "Gradient pattern bad";
		EXPECT_TRUE(pattern_at(pat, p5) == WHITE) << "Gradient pattern bad";
		EXPECT_TRUE(pattern_at(pat, p6) == BLACK) << "Gradient pattern bad";

		Point4 p7(0.0, 0.0, 0.00);
		Point4 p8(0.0, 0.0, 0.99);
		Point4 p9(0.0, 0.0, 1.01);
		EXPECT_TRUE(pattern_at(pat, p7) == WHITE) << "Gradient pattern bad";
		EXPECT_TRUE(pattern_at(pat, p8) == WHITE) << "Gradient pattern bad";
		EXPECT_TRUE(pattern_at(pat, p9) == BLACK) << "Gradient pattern bad";
	}
}

namespace Reflections
{
	TEST(ReflectionsTest, HandlesReflective)
	{
		Material mat;
		EXPECT_TRUE(mat.m_reflective == 0.0) << "Reflective bad";
	}

	TEST(ReflectionsTest, HandlesReflectv)
	{
		Plane p;
		Ray r{ PVpair(Point4(0.0, 1.0, -1.0), Vector4(0.0, -std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0)) };
		Intersection i{ std::sqrt(2.0), &p };
		r.add_intersection(i);
		CompData cd{ r.get_comp_data() };
		EXPECT_TRUE(cd.reflectv == Vector4(0.0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0)) << "Reflective bad";
	}

	TEST(ReflectionsTest, HandlesNonReflectiveSurface)
	{
		World w{ default_world() };
		Ray r{ PVpair{ Point4(0.0, 0.0, 0.0), Vector4(0.0, 0.0, 1.0) } };
		Intersection i{ 1.0, w.m_shapes[1] };
		r.add_intersection(i);
		CompData cd = r.get_comp_data();
		Color4 refl_col = reflected_color(w, cd, 0);
		EXPECT_TRUE(refl_col == BLACK) << "Reflective bad";
	}

	TEST(ReflectionsTest, HandlesReflectiveSurface)
	{
		World w{ default_world() };
		Plane p;
		p.m_material.m_reflective = 0.5;
		p.m_transform = translation(0.0, -1.0, 0.0);
		w.add_object(p);
		Ray r{ PVpair{ Point4(0.0, 0.0, -3.0), Vector4(0.0, -sqrt(2.0) / 2.0, sqrt(2.0) / 2.0) } };
		Intersection i{ sqrt(2.0), w.m_shapes[2] };
		r.add_intersection(i);
		CompData cd = r.get_comp_data();
		Color4 refl_col = reflected_color(w, cd, 10);
		EXPECT_TRUE(refl_col == Color4(0.19033, 0.23791, 0.14274)) << "Reflective bad";
	}

	TEST(ReflectionsTest, HandlesReflectiveShadeHit)
	{
		World w{ default_world() };
		Plane p;
		p.m_material.m_reflective = 0.5;
		p.m_transform = translation(0.0, -1.0, 0.0);
		w.add_object(p);
		Ray r{ PVpair{ Point4(0.0, 0.0, -3.0), Vector4(0.0, -sqrt(2.0) / 2.0, sqrt(2.0) / 2.0) } };
		Intersection i{ sqrt(2.0), w.m_shapes[2] };
		r.add_intersection(i);
		CompData cd = r.get_comp_data();
		Color4 refl_col = w.shade_hit(cd, 1);
		EXPECT_TRUE(refl_col == Color4(0.87675, 0.92434, 0.82917)) << "Reflective bad";
	}
}

namespace Refraction
{
	TEST(RefractionTest, HandlesRefraction)
	{
		Sphere A{ glass_sphere() };
		A.m_transform = scaling(2.0, 2.0, 2.0);
		A.m_material.m_refractive = 1.5;
		Sphere B{ glass_sphere() };
		B.m_transform = translation(0.0, 0.0, -0.25);
		B.m_material.m_refractive = 2.0;
		Sphere C{ glass_sphere() };
		C.m_transform = translation(0.0, 0.0, 0.25);
		C.m_material.m_refractive = 2.5;

		World w;
		w.add_object(A);
		w.add_object(B);
		w.add_object(C);

		Ray r{ PVpair{ Point4(0.0, 0.0, -4.0), Vector4(0.0, 0.0, 1.0) } };

		intersect(w, r);

		const std::vector<double> indeces{ 1.0, 1.5, 2.0, 2.5, 2.5, 1.5, 1.0 };

		CompData cd = r.get_comp_data(0);
		EXPECT_NEAR(cd.n1, indeces[0], EPSILON) << "Refraction bad";
		EXPECT_NEAR(cd.n2, indeces[1], EPSILON) << "Refraction bad";

		cd = r.get_comp_data(1);
		EXPECT_NEAR(cd.n1, indeces[1], EPSILON) << "Refraction bad";
		EXPECT_NEAR(cd.n2, indeces[2], EPSILON) << "Refraction bad";

		cd = r.get_comp_data(2);
		EXPECT_NEAR(cd.n1, indeces[2], EPSILON) << "Refraction bad";
		EXPECT_NEAR(cd.n2, indeces[3], EPSILON) << "Refraction bad";

		cd = r.get_comp_data(3);
		EXPECT_NEAR(cd.n1, indeces[3], EPSILON) << "Refraction bad";
		EXPECT_NEAR(cd.n2, indeces[4], EPSILON) << "Refraction bad";

		cd = r.get_comp_data(4);
		EXPECT_NEAR(cd.n1, indeces[4], EPSILON) << "Refraction bad";
		EXPECT_NEAR(cd.n2, indeces[5], EPSILON) << "Refraction bad";

		cd = r.get_comp_data(5);
		EXPECT_NEAR(cd.n1, indeces[5], EPSILON) << "Refraction bad";
		EXPECT_NEAR(cd.n2, indeces[6], EPSILON) << "Refraction bad";
	}

	TEST(RefractionTest, HandlesUnderPoint)
	{
		Ray r{ PVpair{ Point4{ 0.0, 0.0, -5.0 }, Vector4{ 0.0, 0.0, 1.0 } } };
		Sphere sph{ glass_sphere() };
		sph.m_transform = translation(0.0, 0.0, 1.0);
		Intersection i{ 5.0, &sph };
		r.add_intersection(i);
		CompData cd = r.get_comp_data(0);
		EXPECT_GT(cd.under_pt.z, EPSILON / 2.0) << "Refraction bad";
		EXPECT_LT(cd.pt.z, cd.under_pt.z) << "Refraction bad";
	}

	TEST(RefractionTest, HandlesOpaqueObject)
	{
		World w{ default_world() };
		Ray r{ PVpair{ Point4{ 0.0, 0.0, -5.0 }, Vector4{ 0.0, 0.0, 1.0 } } };
		Intersection i1{ 4.0, w.m_shapes[0] };
		Intersection i2{ 6.0, w.m_shapes[0] };
		r.add_intersection(i1);
		r.add_intersection(i2);

		CompData cd = r.get_comp_data(0);
		Color4 color = refracted_color(w, cd, 5);

		EXPECT_TRUE(color == BLACK) << "Refraction opaque bad";
	}

	TEST(RefractionTest, HandlesMaxRecursiveDepth)
	{
		World w{ default_world() };
		w.m_shapes[0]->m_material.m_transparency = 1.0;
		w.m_shapes[0]->m_material.m_refractive = 1.5;
		Ray r{ PVpair{ Point4{ 0.0, 0.0, -5.0 }, Vector4{ 0.0, 0.0, 1.0 } } };
		Intersection i1{ 4.0, w.m_shapes[0] };
		Intersection i2{ 6.0, w.m_shapes[0] };
		r.add_intersection(i1);
		r.add_intersection(i2);

		CompData cd = r.get_comp_data(0);
		Color4 color = refracted_color(w, cd, 0);

		EXPECT_TRUE(color == BLACK) << "Refraction opaque bad";
	}

	TEST(RefractionTest, HandlesTotalInternalReflection)
	{
		World w{ default_world() };
		w.m_shapes[0]->m_material.m_transparency = 1.0;
		w.m_shapes[0]->m_material.m_refractive = 1.5;
		Ray r{ PVpair{ Point4{ 0.0, 0.0, -std::sqrt(2.0) / 2.0 }, Vector4{0.0, 1.0, 0.0}}};
		Intersection i1{ -std::sqrt(2.0) / 2.0, w.m_shapes[0] };
		Intersection i2{ std::sqrt(2.0) / 2.0, w.m_shapes[0] };
		r.add_intersection(i1);
		r.add_intersection(i2);

		CompData cd = r.get_comp_data(1);
		Color4 color = refracted_color(w, cd, 5);

		EXPECT_TRUE(color == BLACK) << "Refraction opaque bad";
	}

	TEST(RefractionTest, HandlesRefractedColor)
	{
		World w{ default_world() };
		w.m_shapes[0]->m_material.m_ambient = 1.0;
		w.m_shapes[0]->m_material.m_pattern = test_pattern();
		w.m_shapes[1]->m_material.m_transparency = 1.0;
		w.m_shapes[1]->m_material.m_refractive = 1.5;
		Ray r{ PVpair{ Point4{ 0.0, 0.0, 0.1 }, Vector4{0.0, 1.0, 0.0}} };

		Intersection i1(-0.9899, w.m_shapes[0]);
		Intersection i2(-0.4899, w.m_shapes[1]);
		Intersection i3(0.4899, w.m_shapes[1]);
		Intersection i4(0.9899, w.m_shapes[0]);

		r.add_intersection(i1);
		r.add_intersection(i2);
		r.add_intersection(i3);
		r.add_intersection(i4);

		CompData cd = r.get_comp_data(2);
		Color4 color = refracted_color(w, cd, 5);

		EXPECT_TRUE(color == Color4(0.0, 0.99888, 0.04721)) << "Refraction opaque bad";
	}

	TEST(RefractionTest, HandlesRefractedShadeHit)
	{
		World w{ default_world() };
		Plane p;
		p.m_transform = translation(0.0, -1.0, 0.0);
		p.m_material.m_transparency = 0.5;
		p.m_material.m_refractive = 1.5;
		w.add_object(p);
		Sphere ball;
		ball.m_material.m_pattern = no_pat(Color4(1.0, 0.0, 0.0));
		ball.m_material.m_ambient = 0.5;
		ball.m_transform = translation(0.0, -3.5, -0.5);
		w.add_object(ball);

		Ray r{ PVpair{ Point4(0.0, 0.0, -3.0), Vector4(0.0, -std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0) } };
		Intersection i{ sqrt(2.0), w.m_shapes[2] };
		r.add_intersection(i);

		CompData cd{ r.get_comp_data(0) };

		Color4 color = w.shade_hit(cd, 5);

		EXPECT_TRUE(color == Color4(0.93642, 0.68642, 0.68642)) << "Refraction shader hit bad";
	}

	TEST(RefractionTest, HandlesSchlick)
	{
		Sphere sph{ glass_sphere() };
		Ray r{ PVpair{Point4(0.0, 0.0, std::sqrt(2.0) / 2.0), Vector4(0.0, 1.0, 0.0)} };
		Intersection i1{ -std::sqrt(2.0) / 2.0, &sph };
		Intersection i2{ std::sqrt(2.0) / 2.0, &sph };

		r.add_intersection(i1);
		r.add_intersection(i2);

		CompData cd = r.get_comp_data(1);

		double reflectance = schlick(cd);

		EXPECT_TRUE(is_equal(reflectance, 1.0));
	}

	TEST(RefractionTest, HandlesSchlickPerependicular)
	{
		Sphere sph{ glass_sphere() };
		Ray r{ PVpair{Point4(0.0, 0.0, 0.0), Vector4(0.0, 1.0, 0.0)} };
		Intersection i1{ -1.0, &sph };
		Intersection i2{ 1.0, &sph };

		r.add_intersection(i1);
		r.add_intersection(i2);

		CompData cd = r.get_comp_data(1);

		double reflectance = schlick(cd);

		EXPECT_TRUE(is_equal(reflectance, 0.04));
	}

	TEST(RefractionTest, HandlesSchlickSlightAngle)
	{
		Sphere sph{ glass_sphere() };
		Ray r{ PVpair{Point4(0.0, 0.99, -2.0), Vector4(0.0, 0.0, 1.0)} };
		Intersection i1{ 1.8589, &sph };

		r.add_intersection(i1);

		CompData cd = r.get_comp_data(0);

		double reflectance = schlick(cd);

		EXPECT_TRUE(is_equal(reflectance, 0.48873));
	}

	TEST(RefractionTest, HandlesShadeHitReflectance)
	{
		World w{ default_world() };
		Ray r{ PVpair{Point4(0.0, 0.0, -3.0), Vector4(0.0, -std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0)} };
		Plane p;
		p.m_transform = translation(0.0, -1.0, 0.0);
		p.m_material.m_reflective = 0.5;
		p.m_material.m_transparency = 0.5;
		p.m_material.m_refractive = 1.5;
		w.add_object(p);

		Sphere s;
		s.m_material.m_pattern = no_pat(Color4(1.0, 0.0, 0.0));
		s.m_material.m_ambient = 0.5;
		s.m_transform = translation(0.0, -3.5, -0.5);
		w.add_object(s);

		Intersection i{ std::sqrt(2.0), w.m_shapes[2] };
		r.add_intersection(i);

		CompData cd{ r.get_comp_data(0) };

		Color4 col = w.shade_hit(cd, 5);

		EXPECT_TRUE(col == Color4(0.93391, 0.69643, 0.69243));
	}
}

namespace Cubes
{
	TEST(CubeTest, HandlesIntersection)
	{
		Cube c1;
		Ray r1{ PVpair{ Point4(5.0, 0.5, 0.0) , Vector4(-1.0, 0.0, 0.0) } };
		r1.intersect(&c1);
		EXPECT_TRUE(is_equal(r1.m_intersections[0].m_time, 4.0)) << "Cube intersection bad";
		EXPECT_TRUE(is_equal(r1.m_intersections[1].m_time, 6.0)) << "Cube intersection bad";

		Cube c2;
		Ray r2{ PVpair{ Point4(-5.0, 0.5, 0.0) , Vector4(1.0, 0.0, 0.0) } };
		r2.intersect(&c2);
		EXPECT_TRUE(is_equal(r2.m_intersections[0].m_time, 4.0)) << "Cube intersection bad";
		EXPECT_TRUE(is_equal(r2.m_intersections[1].m_time, 6.0)) << "Cube intersection bad";

		Cube c3;
		Ray r3{ PVpair{ Point4(0.5, 5.0, 0.0) , Vector4(0.0, -1.0, 0.0) } };
		r3.intersect(&c3);
		EXPECT_TRUE(is_equal(r3.m_intersections[0].m_time, 4.0)) << "Cube intersection bad";
		EXPECT_TRUE(is_equal(r3.m_intersections[1].m_time, 6.0)) << "Cube intersection bad";

		Cube c4;
		Ray r4{ PVpair{ Point4(0.5, -5.0, 0.0) , Vector4(0.0, 1.0, 0.0) } };
		r4.intersect(&c4);
		EXPECT_TRUE(is_equal(r4.m_intersections[0].m_time, 4.0)) << "Cube intersection bad";
		EXPECT_TRUE(is_equal(r4.m_intersections[1].m_time, 6.0)) << "Cube intersection bad";

		Cube c5;
		Ray r5{ PVpair{ Point4(0.5, 0.0, 5.0) , Vector4(0.0, 0.0, -1.0) } };
		r5.intersect(&c5);
		EXPECT_TRUE(is_equal(r5.m_intersections[0].m_time, 4.0)) << "Cube intersection bad";
		EXPECT_TRUE(is_equal(r5.m_intersections[1].m_time, 6.0)) << "Cube intersection bad";

		Cube c6;
		Ray r6{ PVpair{ Point4(0.5, 0.0, -5.0) , Vector4(0.0, 0.0, 1.0) } };
		r6.intersect(&c6);
		EXPECT_TRUE(is_equal(r6.m_intersections[0].m_time, 4.0)) << "Cube intersection bad";
		EXPECT_TRUE(is_equal(r6.m_intersections[1].m_time, 6.0)) << "Cube intersection bad";

		Cube c7;
		Ray r7{ PVpair{ Point4(0.0, 0.5, 0.0) , Vector4(0.0, 0.0, 1.0) } };
		r7.intersect(&c7);
		EXPECT_TRUE(is_equal(r7.m_intersections[0].m_time, -1.0)) << "Cube intersection bad";
		EXPECT_TRUE(is_equal(r7.m_intersections[1].m_time, 1.0)) << "Cube intersection bad";
	}

	TEST(CubeTest, HandlesNoIntersection)
	{
		Cube c1;
		Ray r1{ PVpair{ Point4(-2.0, 0.0, 0.0) , Vector4(0.2673, 0.5345, 0.8018) } };
		r1.intersect(&c1);
		EXPECT_TRUE(r1.m_intersections.size() == 0) << "Cube intersection bad";

		Cube c2;
		Ray r2{ PVpair{ Point4(0.0, -2.0, 0.0) , Vector4(0.8018, 0.2673, 0.5345) } };
		r2.intersect(&c2);
		EXPECT_TRUE(r2.m_intersections.size() == 0) << "Cube intersection bad";

		Cube c3;
		Ray r3{ PVpair{ Point4(0.0, 0.0, -2.0) , Vector4(0.5345, 0.8018, 0.2673) } };
		r3.intersect(&c3);
		EXPECT_TRUE(r3.m_intersections.size() == 0) << "Cube intersection bad";

		Cube c4;
		Ray r4{ PVpair{ Point4(2.0, 0.0, 2.0) , Vector4(0.0, 0.0, -1.0) } };
		r4.intersect(&c4);
		EXPECT_TRUE(r4.m_intersections.size() == 0) << "Cube intersection bad";

		Cube c5;
		Ray r5{ PVpair{ Point4(0.0, 2.0, 2.0) , Vector4(0.0, -1.0, 0.0) } };
		r5.intersect(&c5);
		EXPECT_TRUE(r5.m_intersections.size() == 0) << "Cube intersection bad";

		Cube c6;
		Ray r6{ PVpair{ Point4(2.0, 2.0, 0.0) , Vector4(-1.0, 0.0, 0.0) } };
		r6.intersect(&c6);
		EXPECT_TRUE(r6.m_intersections.size() == 0) << "Cube intersection bad";
	}

	TEST(CubeTest, HandlesNormal)
	{
		Cube c1;
		Point4 p1{ 1.0, 0.5, -0.8 };
		Vector4 n1 = c1.normal_at_local(p1);
		EXPECT_TRUE(n1 == Vector4(1.0, 0.0, 0.0)) << "Cube normal bad";

		Cube c2;
		Point4 p2{ -1.0, -0.2, 0.9 };
		Vector4 n2 = c2.normal_at_local(p2);
		EXPECT_TRUE(n2 == Vector4(-1.0, 0.0, 0.0)) << "Cube normal bad";

		Cube c3;
		Point4 p3{ -0.4, 1.0, -0.1 };
		Vector4 n3 = c3.normal_at_local(p3);
		EXPECT_TRUE(n3 == Vector4(0.0, 1.0, 0.0)) << "Cube normal bad";

		Cube c4;
		Point4 p4{ 0.3, -1.0, -0.7 };
		Vector4 n4 = c4.normal_at_local(p4);
		EXPECT_TRUE(n4 == Vector4(0.0, -1.0, 0.0)) << "Cube normal bad";

		Cube c5;
		Point4 p5{ -0.6, 0.3, 1.0 };
		Vector4 n5 = c5.normal_at_local(p5);
		EXPECT_TRUE(n5 == Vector4(0.0, 0.0, 1.0)) << "Cube normal bad";

		Cube c6;
		Point4 p6{ 0.4, 0.4, -1.0 };
		Vector4 n6 = c6.normal_at_local(p6);
		EXPECT_TRUE(n6 == Vector4(0.0, 0.0, -1.0)) << "Cube normal bad";

		Cube c7;
		Point4 p7{ 1.0, 1.0, 1.0 };
		Vector4 n7 = c7.normal_at_local(p7);
		EXPECT_TRUE(n7 == Vector4(1.0, 0.0, 0.0)) << "Cube normal bad";

		Cube c8;
		Point4 p8{ -1.0, -1.0, -1.0 };
		Vector4 n8 = c8.normal_at_local(p8);
		EXPECT_TRUE(n8 == Vector4(-1.0, 0.0, 0.0)) << "Cube normal bad";
	}
}

namespace Cylinders
{
	TEST(CylinderTest, HandlesNoIntersection)
	{
		Cylinder c1;
		Ray r1{ PVpair{ Point4(1.0, 0.0, 0.0) , Vector4(0.0, 1.0, 0.0) } };
		r1.intersect(&c1);
		EXPECT_TRUE(r1.m_intersections.size() == 0) << "Cylinder intersection bad";

		Cylinder c2;
		Ray r2{ PVpair{ Point4(0.0, 0.0, 0.0) , Vector4(0.0, 1.0, 0.0) } };
		r2.intersect(&c2);
		EXPECT_TRUE(r2.m_intersections.size() == 0) << "Cylinder intersection bad";

		Cylinder c3;
		Ray r3{ PVpair{ Point4(0.0, 0.0, -5.0) , Vector4(1.0, 1.0, 1.0) } };
		r3.intersect(&c3);
		EXPECT_TRUE(r3.m_intersections.size() == 0) << "Cylinder intersection bad";
	}

	TEST(CylinderTest, HandlesIntersection)
	{
		Cylinder c1;
		Ray r1{ PVpair{ Point4(1.0, 0.0, -5.0) , Vector4(0.0, 0.0, 1.0) } };
		r1.intersect(&c1);
		EXPECT_TRUE(is_equal(r1.m_intersections[0].m_time, 5.0)) << "Cylinder intersection bad";
		EXPECT_TRUE(is_equal(r1.m_intersections[1].m_time, 5.0)) << "Cylinder intersection bad";

		Cylinder c2;
		Ray r2{ PVpair{ Point4(0.0, 0.0, -5.0) , Vector4(0.0, 0.0, 1.0) } };
		r2.intersect(&c2);
		EXPECT_TRUE(is_equal(r2.m_intersections[0].m_time, 4.0)) << "Cylinder intersection bad";
		EXPECT_TRUE(is_equal(r2.m_intersections[1].m_time, 6.0)) << "Cylinder intersection bad";

		Cylinder c3;
		Ray r3{ PVpair{ Point4(0.5, 0.0, -5.0) , normalize(Vector4(0.1, 1.0, 1.0)) } };
		r3.intersect(&c3);
		EXPECT_TRUE(is_equal(r3.m_intersections[0].m_time, 6.80798)) << "Cylinder intersection bad";
		EXPECT_TRUE(is_equal(r3.m_intersections[1].m_time, 7.08872)) << "Cylinder intersection bad";
	}

	TEST(CylinderTest, HandlesNormal)
	{
		Cylinder c1;
		Point4 p1{ 1.0, 0.0, 0.0 };
		Vector4 n1 = c1.normal_at_local(p1);
		EXPECT_TRUE(n1 == Vector4(1.0, 0.0, 0.0)) << "Cylinder normal bad";

		Cylinder c2;
		Point4 p2{ 0.0, 5.0, -1.0 };
		Vector4 n2 = c2.normal_at_local(p2);
		EXPECT_TRUE(n2 == Vector4(0.0, 0.0, -1.0)) << "Cylinder normal bad";

		Cylinder c3;
		Point4 p3{ 0.0, -2.0, 1.0 };
		Vector4 n3 = c3.normal_at_local(p3);
		EXPECT_TRUE(n3 == Vector4(0.0, 0.0, 1.0)) << "Cylinder normal bad";

		Cylinder c4;
		Point4 p4{ -1.0, 1.0, 0.0 };
		Vector4 n4 = c4.normal_at_local(p4);
		EXPECT_TRUE(n4 == Vector4(-1.0, 0.0, 0.0)) << "Cylinder normal bad";
	}

	TEST(CylinderTest, HandlesCylinderLimits)
	{
		Cylinder c1;
		c1.m_minimum = 1.0;
		c1.m_maximum = 2.0;
		Ray r1{ PVpair{ Point4(0.0, 1.5, 0.0) , normalize(Vector4(0.1, 1.0, 0.0)) } };
		r1.intersect(&c1);
		EXPECT_TRUE(r1.m_intersections.size() == 0) << "Cylinder intersection bad";

		Ray r2{ PVpair{ Point4(0.0, 3.0, -5.0) , normalize(Vector4(0.0, 0.0, 1.0)) } };
		r2.intersect(&c1);
		EXPECT_TRUE(r2.m_intersections.size() == 0) << "Cylinder intersection bad";

		Ray r3{ PVpair{ Point4(0.0, 0.0, -5.0) , normalize(Vector4(0.0, 0.0, 1.0)) } };
		r3.intersect(&c1);
		EXPECT_TRUE(r3.m_intersections.size() == 0) << "Cylinder intersection bad";

		Ray r4{ PVpair{ Point4(0.0, 2.0, -5.0) , normalize(Vector4(0.0, 0.0, 1.0)) } };
		r4.intersect(&c1);
		EXPECT_TRUE(r4.m_intersections.size() == 0) << "Cylinder intersection bad";

		Ray r5{ PVpair{ Point4(0.0, 1.0, -5.0) , normalize(Vector4(0.0, 0.0, 1.0)) } };
		r5.intersect(&c1);
		EXPECT_TRUE(r5.m_intersections.size() == 0) << "Cylinder intersection bad";

		Ray r6{ PVpair{ Point4(0.0, 1.5, -2.0) , normalize(Vector4(0.0, 0.0, 1.0)) } };
		r6.intersect(&c1);
		EXPECT_TRUE(r6.m_intersections.size() == 2) << "Cylinder intersection bad";
	}

	TEST(CylinderTest, HandlesClosedCylinderLimits)
	{
		Cylinder c1;
		c1.m_minimum = 1.0;
		c1.m_maximum = 2.0;
		c1.m_closed = true;
		Ray r1{ PVpair{ Point4(0.0, 3.0, 0.0) , normalize(Vector4(0.0, -1.0, 0.0)) } };
		r1.intersect(&c1);
		EXPECT_TRUE(r1.m_intersections.size() == 2) << "Cylinder intersection bad";

		Ray r2{ PVpair{ Point4(0.0, 3.0, -2.0) , normalize(Vector4(0.0, -1.0, 2.0)) } };
		r2.intersect(&c1);
		EXPECT_TRUE(r2.m_intersections.size() == 2) << "Cylinder intersection bad";

		Ray r3{ PVpair{ Point4(0.0, 4.0, -2.0) , normalize(Vector4(0.0, -1.0, 1.0)) } };
		r3.intersect(&c1);
		EXPECT_TRUE(r3.m_intersections.size() == 2) << "Cylinder intersection bad";

		Ray r4{ PVpair{ Point4(0.0, 0.0, -2.0) , normalize(Vector4(0.0, 1.0, 2.0)) } };
		r4.intersect(&c1);
		EXPECT_TRUE(r4.m_intersections.size() == 2) << "Cylinder intersection bad";

		Ray r5{ PVpair{ Point4(0.0, 0.0, -2.0) , normalize(Vector4(0.0, 1.0, 1.0)) } };
		r5.intersect(&c1);
		EXPECT_TRUE(r5.m_intersections.size() == 2) << "Cylinder intersection bad";
	}

	TEST(CylinderTest, HandlesClosedCylinderNormals)
	{
		Cylinder c1;
		c1.m_minimum = 1.0;
		c1.m_maximum = 2.0;
		c1.m_closed = true;
		Point4 p1{ 0.0, 1.0, 0.0 };
		Vector4 n1 = c1.normal_at_local(p1);
		EXPECT_TRUE(n1 == Vector4(0.0, -1.0, 0.0)) << "Cylinder normal bad";

		Point4 p2{ 0.5, 1.0, 0.0 };
		Vector4 n2 = c1.normal_at_local(p2);
		EXPECT_TRUE(n2 == Vector4(0.0, -1.0, 0.0)) << "Cylinder normal bad";

		Point4 p3{ 0.0, 1.0, 0.5 };
		Vector4 n3 = c1.normal_at_local(p3);
		EXPECT_TRUE(n3 == Vector4(0.0, -1.0, 0.0)) << "Cylinder normal bad";

		Point4 p4{ 0.0, 2.0, 0.0 };
		Vector4 n4 = c1.normal_at_local(p4);
		EXPECT_TRUE(n4 == Vector4(0.0, 1.0, 0.0)) << "Cylinder normal bad";

		Point4 p5{ 0.5, 2.0, 0.0 };
		Vector4 n5 = c1.normal_at_local(p5);
		EXPECT_TRUE(n5 == Vector4(0.0, 1.0, 0.0)) << "Cylinder normal bad";

		Point4 p6{ 0.0, 2.0, 0.5 };
		Vector4 n6 = c1.normal_at_local(p6);
		EXPECT_TRUE(n6 == Vector4(0.0, 1.0, 0.0)) << "Cylinder normal bad";
	}
}

namespace Cones
{
	TEST(ConeTest, HandlesConeIntersection)
	{
		Cone c1;
		Ray r1{ PVpair{ Point4(0.0, 0.0, -5.0) , normalize(Vector4(0.0, 0.0, 1.0)) } };
		r1.intersect(&c1);
		EXPECT_TRUE(r1.m_intersections.size() == 2) << "Cone intersection bad";
		EXPECT_TRUE(is_equal(r1.m_intersections[0].m_time, 5.0)) << "Cone intersection bad";
		EXPECT_TRUE(is_equal(r1.m_intersections[1].m_time, 5.0)) << "Cone intersection bad";

		Cone c2;
		Ray r2{ PVpair{ Point4(0.0, 0.0, -5.0) , normalize(Vector4(1.0, 1.0, 1.0)) } };
		r2.intersect(&c2);
		EXPECT_TRUE(r2.m_intersections.size() == 2) << "Cone intersection bad";
		EXPECT_TRUE(is_equal(r2.m_intersections[0].m_time, 8.66025)) << "Cone intersection bad";
		EXPECT_TRUE(is_equal(r2.m_intersections[1].m_time, 8.66025)) << "Cone intersection bad";

		Cone c3;
		Ray r3{ PVpair{ Point4(1.0, 1.0, -5.0) , normalize(Vector4(-0.5, -1.0, 1.0)) } };
		r3.intersect(&c3);
		EXPECT_TRUE(r3.m_intersections.size() == 2) << "Cone intersection bad";
		EXPECT_TRUE(is_equal(r3.m_intersections[0].m_time, 4.55006)) << "Cone intersection bad";
		EXPECT_TRUE(is_equal(r3.m_intersections[1].m_time, 49.44994)) << "Cone intersection bad";
	
		Cone c4;
		Ray r4{ PVpair{ Point4(0.0, 0.0, -1.0) ,normalize(Vector4(0.0, 1.0, 1.0)) } };
		r4.intersect(&c4);
		EXPECT_TRUE(r4.m_intersections.size() == 1) << "Cone intersection bad";
		EXPECT_TRUE(is_equal(r4.m_intersections[0].m_time, 0.35355)) << "Cone intersection bad";
	}

	TEST(ConeTest, HandlesClosedCylinderCone)
	{
		Cone c1;
		c1.m_minimum = -0.5;
		c1.m_maximum = 0.5;
		c1.m_closed = true;
		Ray r1{ PVpair{ Point4(0.0, 0.0, -5.0) , normalize(Vector4(0.0, 1.0, 0.0)) } };
		r1.intersect(&c1);
		EXPECT_TRUE(r1.m_intersections.size() == 0) << "Cone intersection bad";

		Ray r2{ PVpair{ Point4(0.0, 0.0, -0.25) , normalize(Vector4(0.0, 1.0, 1.0)) } };
		r2.intersect(&c1);
		EXPECT_TRUE(r2.m_intersections.size() == 2) << "Cone intersection bad";

		Ray r3{ PVpair{ Point4(0.0, 0.0, -0.25) , normalize(Vector4(0.0, 1.0, 0.0)) } };
		r3.intersect(&c1);
		EXPECT_TRUE(r3.m_intersections.size() == 4) << "Cone intersection bad";
	}

	TEST(ConeTest, HandlesClosedCylinderNormals)
	{
		Cone c1;
		Point4 p1{ 0.0, 0.0, 0.0 };
		Vector4 n1 = c1.normal_at_local(p1);
		EXPECT_TRUE(n1 == Vector4(0.0, 0.0, 0.0)) << "Cone normal bad";

		Point4 p2{ 1.0, 1.0, 1.0 };
		Vector4 n2 = c1.normal_at_local(p2);
		EXPECT_TRUE(n2 == Vector4(1.0, -std::sqrt(2.0), 1.0)) << "Cone normal bad";

		Point4 p3{ -1.0, -1.0, 0.0 };
		Vector4 n3 = c1.normal_at_local(p3);
		EXPECT_TRUE(n3 == Vector4(-1.0, 1.0, 0.0)) << "Cone normal bad";
	}
}

namespace Groups
{
	TEST(GroupTest, HandlesDefaultGroup)
	{
		Group* g1 = new Group;

		EXPECT_TRUE(g1->m_transform == i4x4) << "Default Group bad";
		EXPECT_TRUE(g1->m_children.size() == 0) << "Default Group bad";

		delete g1;
	}

	TEST(GroupTest, HandlesShapeDefaultParent)
	{
		TestShape ts1;
		EXPECT_TRUE(ts1.m_parent == nullptr) << "Default shape parent bad";
	}

	TEST(GroupTest, HandlesAddChild)
	{
		Group g1;
		TestShape ts1;
		g1.add_child(ts1);

		EXPECT_TRUE(g1.m_children.size() == 1) << "Add child bad";

		Group::delete_track_nodes();
	}

	TEST(GroupTest, HandlesIntesrsectEmpty)
	{
		Group g1;
		Ray r1{ PVpair{ Point4(0.0, 0.0, 0.0), Vector4(0.0, 0.0, 1.0) } };
		r1.intersect(&g1);

		EXPECT_TRUE(r1.m_intersections.size() == 0) << "Group empty intersection bad";
	}

	TEST(GroupTest, HandlesIntesrsect)
	{
		World w1;
		Group g1;
		w1.add_object(g1);
		Group* p_g1 = dynamic_cast<Group*>(w1.m_shapes[0]);

		Sphere s1;
		Sphere s2;
		s2.m_transform = translation(0.0, 0.0, -3.0);
		Sphere s3;
		s3.m_transform = translation(5.0, 0.0, 0.0);
		p_g1->add_child(s1);
		p_g1->add_child(s2);
		p_g1->add_child(s3);

		Ray r1{ PVpair{ Point4(0.0, 0.0, -5.0), Vector4(0.0, 0.0, 1.0) } };
		intersect(w1, r1);

		EXPECT_TRUE(r1.m_intersections.size() == 4) << "Group intersection bad";
	
		Group::delete_track_nodes();
	}

	TEST(GroupTest, HandlesGroupTransform)
	{
		Group g1;
		g1.m_transform = scaling(2.0, 2.0, 2.0);
		Sphere s1;
		s1.m_transform = translation(5.0, 0.0, 0.0);

		g1.add_child(s1);

		Ray r1{ PVpair{ Point4(10.0, 0.0, -10.0), Vector4(0.0, 0.0, 1.0) } };
		r1.intersect(&g1);

		EXPECT_TRUE(r1.m_intersections.size() == 2) << "Group intersection bad";
	
		Group::delete_track_nodes();
	}

	TEST(GroupTest, HandlesGroupNormal)
	{
		World w;

		Group g1;
		g1.m_transform = rotation(0.0, DEG_90, 0.0);

		w.add_object(g1);
		Group* p_g1 = dynamic_cast<Group*>(w.m_shapes[0]);

		Group g2;
		g2.m_transform = scaling(1.0, 2.0, 3.0);

		p_g1->add_child(g2);
		Group* p_g2 = dynamic_cast<Group*>(p_g1->m_children[0]);

		Sphere s1;
		s1.m_transform = translation(5.0, 0.0, 0.0);

		p_g2->add_child(s1);

		Ray r1{ PVpair{ Point4(0.0 ,0.0 ,-10.0), Vector4(0.3543, 0.2362, 0.9048) } };

		intersect(w, r1);
		CompData cd = r1.get_comp_data();
		Vector4 n1{ r1.normal_at(cd) };

		EXPECT_TRUE(n1 == Vector4(0.28559, 0.42839, -0.85726)) << "Group intersection bad";

		Group::delete_track_nodes();
	}

}

namespace Triangles
{
	TEST(TriangleTest, HandlesAssignment)
	{
		Triangle tr1{ Point4(0.0, 1.0, 0.0), Point4(-1.0, 0.0, 0.0), Point4(1.0, 0.0, 0.0) };
		EXPECT_TRUE(tr1.m_pt1 == Point4(0.0, 1.0, 0.0)) << "Triangle assignment bad";
		EXPECT_TRUE(tr1.m_pt2 == Point4(-1.0, 0.0, 0.0)) << "Triangle assignment bad";
		EXPECT_TRUE(tr1.m_pt3 == Point4(1.0, 0.0, 0.0)) << "Triangle assignment bad";
		EXPECT_TRUE(tr1.m_e1 == Vector4(-1.0, -1.0, 0.0)) << "Triangle assignment bad";
		EXPECT_TRUE(tr1.m_e2 == Vector4(1.0, -1.0, 0.0)) << "Triangle assignment bad";
		EXPECT_TRUE(tr1.m_normal == Vector4(0.0, 0.0, -1.0)) << "Triangle assignment bad";
	}

	TEST(TriangleTest, HandlesNormal)
	{
		Triangle tr1{ Point4(0.0, 1.0, 0.0), Point4(-1.0, 0.0, 0.0), Point4(1.0, 0.0, 0.0) };
		EXPECT_TRUE(tr1.normal_at_local(Point4(0.0, 0.5, 0.0)) == tr1.m_normal) << "Triangle normal bad";
		EXPECT_TRUE(tr1.normal_at_local(Point4(-0.5, 0.75, 0.0)) == tr1.m_normal) << "Triangle normal bad";
		EXPECT_TRUE(tr1.normal_at_local(Point4(0.5, 0.25, 0.0)) == tr1.m_normal) << "Triangle normal bad";
	}

	TEST(TriangleTest, HandlesMissParallel)
	{
		Triangle tr1{ Point4(0.0, 1.0, 0.0), Point4(-1.0, 0.0, 0.0), Point4(1.0, 0.0, 0.0) };
		Ray r1{ PVpair{ Point4(0.0, -1.0, -2.0), Vector4(0.0, 1.0, 0.0) } };
		World w1;
		w1.add_object(tr1);
		intersect(w1, r1);
		EXPECT_TRUE(r1.m_intersections.size() == 0) << "Triangle intersection bad";
	}

	TEST(TriangleTest, HandlesMissEdge1)
	{
		Triangle tr1{ Point4(0.0, 1.0, 0.0), Point4(-1.0, 0.0, 0.0), Point4(1.0, 0.0, 0.0) };
		Ray r1{ PVpair{ Point4(1.0, 1.0, -2.0), Vector4(0.0, 0.0, 1.0) } };
		World w1;
		w1.add_object(tr1);
		intersect(w1, r1);
		EXPECT_TRUE(r1.m_intersections.size() == 0) << "Triangle intersection bad";
	}

	TEST(TriangleTest, HandlesMissEdge2)
	{
		Triangle tr1{ Point4(0.0, 1.0, 0.0), Point4(-1.0, 0.0, 0.0), Point4(1.0, 0.0, 0.0) };
		Ray r1{ PVpair{ Point4(-1.0, 1.0, -2.0), Vector4(0.0, 0.0, 1.0) } };
		World w1;
		w1.add_object(tr1);
		intersect(w1, r1);
		EXPECT_TRUE(r1.m_intersections.size() == 0) << "Triangle intersection bad";
	}

	TEST(TriangleTest, HandlesMissEdge3)
	{
		Triangle tr1{ Point4(0.0, 1.0, 0.0), Point4(-1.0, 0.0, 0.0), Point4(1.0, 0.0, 0.0) };
		Ray r1{ PVpair{ Point4(0.0, -1.0, -2.0), Vector4(0.0, 0.0, 1.0) } };
		World w1;
		w1.add_object(tr1);
		intersect(w1, r1);
		EXPECT_TRUE(r1.m_intersections.size() == 0) << "Triangle intersection bad";
	}

	TEST(TriangleTest, HandlesIntersection)
	{
		Triangle tr1{ Point4(0.0, 1.0, 0.0), Point4(-1.0, 0.0, 0.0), Point4(1.0, 0.0, 0.0) };
		Ray r1{ PVpair{ Point4(0.0, 0.5, -2.0), Vector4(0.0, 0.0, 1.0) } };
		World w1;
		w1.add_object(tr1);
		intersect(w1, r1);
		EXPECT_TRUE(r1.m_intersections.size() == 1) << "Triangle intersection bad";
		EXPECT_TRUE(r1.m_intersections[0].m_time == 2.0) << "Triangle intersection bad";
	}
}