#include "pch.h"

#include <cassert>
#include <iostream>

#include "include_all.h"

TEST(TupleTest, HandlesPointAssignment)
{
	tuple tp(4.3f, -4.2f, 3.1f, 1.0f);

	EXPECT_TRUE(is_equal(tp.x, 4.3f)) << "X member did not assign";
	EXPECT_TRUE(is_equal(tp.y,-4.2f)) << "Y member did not assign";
	EXPECT_TRUE(is_equal(tp.z, 3.1f)) << "Z member did not assign";
	EXPECT_TRUE(is_equal(tp.w, 1.0f)) << "W member did not assign";

	EXPECT_TRUE(point(4, -4, 3) == tuple(4, -4, 3, 1)) << "Point creation bad";
}

TEST(TupleTest, HandlesVectorAssignment)
{
	tuple tp(4.3f, -4.2f, 3.1f, 0.0f);

	EXPECT_TRUE(is_equal(tp.x, 4.3f)) << "X member did not assign";
	EXPECT_TRUE(is_equal(tp.y, -4.2f)) << "Y member did not assign";
	EXPECT_TRUE(is_equal(tp.z, 3.1f)) << "Z member did not assign";
	EXPECT_TRUE(is_equal(tp.w, 0.0f)) << "W member did not assign";

	EXPECT_TRUE(vector(4.0f, -4.0f, 3.0f) == tuple(4.0f, -4.0f, 3.0f, 0.0f)) << "Vector creation bad";
}

TEST(TupleTest, HandlesTupleAdd)
{
	tuple a(3.0f, -2.0f, 5.0f, 1.0f);
	tuple b(-2.0f, 3.0f, 1.0f, 0.0f);
	tuple c = a + b;

	EXPECT_TRUE(c == tuple(1.0f, 1.0f, 6.0f, 1.0f)) << "Tuple addition bad";
}

TEST(TupleTest, HandlesTupleSubPP)
{
	tuple p1 = point(3.0f, 2.0f, 1.0f);
	tuple p2 = point(5.0f, 6.0f, 7.0f);
	tuple v = p1 - p2;

	EXPECT_TRUE(v == vector(-2.0f, -4.0f, -6.0f)) << "Tuple point point subtraction bad";
}

TEST(TupleTest, HandlesTupleSubPV)
{
	tuple p1 = point(3.0f, 2.0f, 1.0f);
	tuple v1 = vector(5.0f, 6.0f, 7.0f);
	tuple p2 = p1 - v1;

	EXPECT_TRUE(p2 == point(-2.0f, -4.0f, -6.0f)) << "Tuple point vector subtraction bad";
}

TEST(TupleTest, HandlesTupleSubVV)
{
	tuple v1 = vector(3.0f, 2.0f, 1.0f);
	tuple v2 = vector(5.0f, 6.0f, 7.0f);
	tuple v = v1 - v2;

	EXPECT_TRUE(v == vector(-2.0f, -4.0f, -6.0f)) << "Tuple vector vector subtraction bad";
}

TEST(TupleTest, HandlesTupleNegation)
{
	tuple a(1.0f, -2.0f, 3.0f, -4.0f);
	a = -a;

	EXPECT_TRUE(a == tuple(-1.0f, 2.0f, -3.0f, 4.0f)) << "Tuple negation bad";
}

TEST(TupleTest, HandlesTupleScalarMult)
{
	tuple a(1.0f, -2.0f, 3.0f, -4.0f);

	EXPECT_TRUE(a * 3.5f == tuple(3.5f, -7.0f, 10.5f, -14.0f))<< "Tuple scalar multiplication bad";
	EXPECT_TRUE(a * 0.5f == tuple(0.5f, -1.0f, 1.5f, -2.0f))  << "Tuple scalar multiplication bad";
	EXPECT_TRUE(0.5f * a == tuple(0.5f, -1.0f, 1.5f, -2.0f))  << "scalar Tuple multiplication bad";
}

TEST(TupleTest, HandlesTupleScalarDiv)
{
	tuple a(1.0f, -2.0f, 3.0f, -4.0f);

	EXPECT_TRUE(a / 2.0f == tuple(0.5f, -1.0f, 1.5f, -2.0f)) << "scalar Tuple division bad";
}

TEST(TupleTest, HandlesTupleMagnitude)
{
	tuple v1{ vector(1.0f, 0.0f, 0.0f) };
	tuple v2{ vector(0.0f, 0.0f, 1.0f) };
	tuple v3{ vector(1.0f, 2.0f, 3.0f) };
	tuple v4{ vector(-1.0f, -2.0f, -3.0f) };

	EXPECT_TRUE(is_equal(magnitude(v1), 1.0f)) << "Tuple magnitude bad";
	EXPECT_TRUE(is_equal(magnitude(v2), 1.0f)) << "Tuple magnitude bad";
	EXPECT_TRUE(is_equal(magnitude(v3), sqrt(14.0f))) << "Tuple magnitude bad";
	EXPECT_TRUE(is_equal(magnitude(v4), sqrt(14.0f))) << "Tuple magnitude bad";
}

TEST(TupleTest, HandlesTupleNormalize)
{
	tuple v1{ vector(4.0f, 0.0f, 0.0f) };
	tuple v2{ vector(1.0f, 2.0f, 3.0f) };
	tuple v1_n = normalize(v1);
	tuple v2_n = normalize(v2);

	EXPECT_TRUE(is_equal(magnitude(v2_n), 1.0f)) << "Tuple normalize bad";
	EXPECT_TRUE(v2_n == vector(0.26726f, 0.53452f, 0.80178f)) << "Tuple normalize bad";
	EXPECT_TRUE(v1_n == vector(1.0f, 0.0f, 0.0f)) << "Tuple normalize bad";
}

TEST(TupleTest, HandlesTupleDot)
{
	tuple a{ vector(1.0f, 2.0f, 3.0f) };
	tuple b{ vector(2.0f, 3.0f, 4.0f) };

	EXPECT_TRUE(is_equal(dot(a, b), 20.0f)) << "Tuple dot bad";
}

TEST(TupleTest, HandlesTupleCross)
{
	tuple a{ vector(1.0f, 2.0f, 3.0f) };
	tuple b{ vector(2.0f, 3.0f, 4.0f) };

	EXPECT_TRUE(cross(a, b) == vector(-1.0f, 2.0f, -1.0f)) << "Tuple cross bad";
	EXPECT_TRUE(cross(b, a) == vector(1.0f, -2.0f, 1.0f)) << "Tuple cross bad";
}

TEST(TupleTest, HandlesColorAsignment)
{
	tuple c{ color(-0.5f, 0.4f, 1.7f) };

	EXPECT_TRUE(is_equal(c.x, -0.5f)) << "X color asingment bad";
	EXPECT_TRUE(is_equal(c.y, 0.4f)) << "Y color asingment bad";
	EXPECT_TRUE(is_equal(c.z, 1.7f)) << "Z color asingment bad";
}

TEST(TupleTest, HandlesColorArithmetic)
{
	tuple c1{ color(0.9f, 0.6f, 0.75f) };
	tuple c2{ color(0.7f, 0.1f, 0.25f) };
	tuple c3{ color(0.2f, 0.3f, 0.4f) };

	tuple c4 = c1 + c2;
	tuple c5 = c1 - c2;
	tuple c6 = c3 * 2.0f;

	EXPECT_TRUE(c4 == color(1.6f, 0.7f, 1.0f)) << "color addition bad";
	EXPECT_TRUE(c5 == color(0.2f, 0.5f, 0.5f)) << "color subtraction bad";
	EXPECT_TRUE(c6 == color(0.4f, 0.6f, 0.8f)) << "color multiplication bad";
}

TEST(TupleTest, HandlesTupleHadamard)
{
	tuple a1{ color(1.0f, 0.2f, 0.4f) };
	tuple a2{ color(0.9f, 1.0f, 0.1f) };

	EXPECT_TRUE(hadamard(a1, a2) == color(0.9f, 0.2f, 0.04f)) << "Tuple hadamard bad";
}

TEST(CanvasTest, HandlesCanvas)
{
	ImgBuf img_buf_test(20, 10);

	EXPECT_TRUE(img_buf_test.m_width == 20) << "Canvas width bad";
	EXPECT_TRUE(img_buf_test.m_height == 10) << "Canvas height bad";

	img_buf_test.write_pixel(2, 5, color(1, 0, 0));

	EXPECT_TRUE(img_buf_test.pixel_at(2, 5) == color(1.0f, 0.0f, 0.0f)) << "Canvas pixel asignment bad";
}

TEST(MatrixTest, HandlesMatrixAsignment)
{
	mat4x4 a1{
		1.0f , 2.0f , 3.0f , 4.0f,
		5.5f , 6.5f , 7.5f , 8.5f,
		9.0f , 10.0f, 11.0f, 12.0f,
		13.5f, 14.5f, 15.5f, 16.5f };

	mat3x3 a2{
		-3.0f,  5.0f,  0.0f,
		 1.0f, -2.0f, -7.0f,
		 0.0f,  1.0f,  1.0f
	};

	mat2x2 a3{
		-3.0f,  5.0f,
		 1.0f, -2.0
	};

	EXPECT_TRUE(is_equal(1.0f, a1.m_data[0][0]))  << "Bad 4x4 asignment at 0,0";
	EXPECT_TRUE(is_equal(4.0f, a1.m_data[0][3]))  << "Bad 4x4 asignment at 0,3";
	EXPECT_TRUE(is_equal(5.5f, a1.m_data[1][0]))  << "Bad 4x4 asignment at 1,0";
	EXPECT_TRUE(is_equal(7.5f, a1.m_data[1][2]))  << "Bad 4x4 asignment at 1,2";
	EXPECT_TRUE(is_equal(11.0f, a1.m_data[2][2])) << "Bad 4x4 asignment at 2,2";
	EXPECT_TRUE(is_equal(13.5f, a1.m_data[3][0])) << "Bad 4x4 asignment at 3,0";
	EXPECT_TRUE(is_equal(15.5f, a1.m_data[3][2])) << "Bad 4x4 asignment at 3,2";

	EXPECT_TRUE(is_equal(-3.0f, a2.m_data[0][0])) << "Bad 3x3 asignment at 0,0";
	EXPECT_TRUE(is_equal(-2.0f, a2.m_data[1][1])) << "Bad 3x3 asignment at 1,1";
	EXPECT_TRUE(is_equal(1.0f, a2.m_data[2][2]))  << "Bad 3x3 asignment at 2,2";

	EXPECT_TRUE(is_equal(-3.0f, a3.m_data[0][0])) << "Bad 2x2 asignment at 0,0";
	EXPECT_TRUE(is_equal(5.0f, a3.m_data[0][1]))  << "Bad 2x2 asignment at 0,1";
	EXPECT_TRUE(is_equal(1.0f, a3.m_data[1][0]))  << "Bad 2x2 asignment at 1,0";
	EXPECT_TRUE(is_equal(-2.0f, a3.m_data[1][1])) << "Bad 2x2 asignment at 1,1";
}

TEST(MatrixTest, HandlesMatrixComparison)
{
	mat4x4 a1{
		1.0f , 2.0f , 3.0f , 4.0f,
		5.0f , 6.0f , 7.0f , 8.0f,
		9.0f , 10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f, 16.0f 
	};

	mat4x4 a2{
		1.0f , 2.0f , 3.0f , 4.0f,
		5.0f , 6.0f , 7.0f , 8.0f,
		9.0f , 10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f, 16.0f 
	};

	mat4x4 a3{
		2.0f ,3.0f, 4.0f ,5.0f,
		6.0f ,7.0f, 8.0f ,9.0f,
		8.0f ,7.0f, 6.0f, 5.0f,
		4.0f, 3.0f, 2.0f, 1.0f 
	};


	EXPECT_TRUE(a1 == a2) << "matrix equality bad";
	EXPECT_TRUE(a1 != a3) << "matrix inequality bad";
}

TEST(MatrixTest, HandlesMatrixMult)
{
	mat4x4 m1{
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f,
		9.0f, 8.0f, 7.0f, 6.0f,
		5.0f, 4.0f, 3.0f, 2.0f 
	};

	mat4x4 m2{
		-2.0f, 1.0f, 2.0f, 3.0f,
		 3.0f, 2.0f, 1.0f,-1.0f,
		 4.0f, 3.0f, 6.0f, 5.0f,
		 1.0f, 2.0f, 7.0f, 8.0f 
	};

	mat4x4 m3 = m1 * m2;

	mat4x4 m4{
		20.0f, 22.0f, 50.0f,  48.0f,
		44.0f, 54.0f, 114.0f, 108.0f,
		40.0f, 58.0f, 110.0f, 102.0f,
		16.0f, 26.0f, 46.0f,  42.0f 
	};

	mat4x4 m5{
		1.0f, 2.0f, 3.0f, 4.0f,
		2.0f, 4.0f, 4.0f, 2.0f,
		8.0f, 6.0f, 4.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	tuple t1{ 1.0f, 2.0f, 3.0f, 1.0f };
	tuple t2 = m5 * t1;
	tuple t3{ 18.0f, 24.0f, 33.0f, 1.0f };

	EXPECT_TRUE(m3 == m4) << "matrix matrix multiplication bad";
	EXPECT_TRUE(t2 == t3) << "matrix tuple multiplication bad";
}

TEST(MatrixTest, HandlesMatrixIdentity)
{
	mat4x4 a1{
		1.0f , 2.0f , 3.0f , 4.0f,
		5.0f , 6.0f , 7.0f , 8.0f,
		9.0f , 10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f, 16.0f 
	};

	mat4x4 a2 = a1 * i4x4;

	EXPECT_TRUE(a1 == a2) << "Identity matrix bad";
}

TEST(MatrixTest, HandlesMatrixTranspose)
{
	mat4x4 a1{
		0.0f, 9.0f, 3.0f, 0.0f,
		9.0f, 8.0f, 0.0f, 8.0f,
		1.0f, 8.0f, 5.0f, 3.0f,
		0.0f, 0.0f, 5.0f, 8.0f
	};

	mat4x4 a2 = a1.transpose();

	mat4x4 a3{
		0.0f, 9.0f, 1.0f, 0.0f,
		9.0f, 8.0f, 8.0f, 0.0f,
		3.0f, 0.0f, 5.0f, 5.0f,
		0.0f, 8.0f, 3.0f, 8.0f
	};

	EXPECT_TRUE(a2 == a3) << "matrix transpose bad";
}

TEST(MatrixTest, HandlesMatrixDeterminants)
{
	mat2x2 a1{
	 1.0f, 5.0f,
	-3.0f, 2.0f
	};

	float a2 = a1.determinant();

	EXPECT_TRUE(is_equal(a2, 17.0f)) << "matrix 2x2 determinant bad";
}

TEST(MatrixTest, HandlesMatrixSubmatrix)
{
	mat3x3 a1{
		 1.0f, 5.0f,  0.0f,
		-3.0f, 2.0f,  7.0f,
		 0.0f, 6.0f, -3.0f
	};

	mat2x2 a2 = a1.submatrix(0, 2);

	mat2x2 a3{
		-3.0f, 2.0f,
		 0.0f, 6.0f
	};

	mat4x4 a4{
		-6.0f, 1.0f,  1.0f, 6.0f,
		-8.0f, 5.0f,  8.0f, 6.0f,
		-1.0f, 0.0f,  8.0f, 2.0f,
		-7.0f, 1.0f, -1.0f, 1.0f
	};

	mat3x3 a5 = a4.submatrix(2, 1);

	mat3x3 a6{
		-6.0f,  1.0f, 6.0f,
		-8.0f,  8.0f, 6.0f,
		-7.0f, -1.0f, 1.0f
	};

	EXPECT_TRUE(a3 == a2) << "matrix 3x3 submatrix bad";
	EXPECT_TRUE(a6 == a5) << "matrix 4x4 submatrix bad";
}

TEST(MatrixTest, HandlesMatrixMinors)
{
	mat3x3 a1{
		3.0f, 5.0f, 0.0f,
		2.0f,-1.0f,-7.0f,
		6.0f,-1.0f, 5.0f
	};

	float a2 = a1.minor(1.0f, 0.0f);

	EXPECT_TRUE(is_equal(a2, 25.0f)) << "matrix 4x4 submatrix bad";
}

TEST(MatrixTest, HandlesMatrixCofactor)
{
	mat3x3 a1{
		3.0f, 5.0f, 0.0f,
		2.0f,-1.0f,-7.0f,
		6.0f,-1.0f, 5.0f
	};

	float a2 = a1.cofactor(0, 0);
	float a3 = a1.cofactor(1, 0);

	EXPECT_TRUE(is_equal(a2, -12.0f)) << "matrix 4x4 submatrix bad";
	EXPECT_TRUE(is_equal(a3, -25.0f)) << "matrix 4x4 submatrix bad";
}

TEST(MatrixTest, Handles4x4Matrix)
{
	mat3x3 a1{
		 1.0f, 2.0f,  6.0f,
		-5.0f, 8.0f, -4.0f,
		 2.0f, 6.0f,  4.0f
	};

	mat4x4 a2{
		-2.0f, -8.0f,  3.0f,  5.0f,
		-3.0f,  1.0f,  7.0f,  3.0f,
		 1.0f,  2.0f, -9.0f,  6.0f,
		-6.0f,  7.0f,  7.0f, -9.0f
	};

	float a3 = a1.cofactor(0, 0);
	float a4 = a1.cofactor(0, 1);
	float a5 = a1.cofactor(0, 2);
	float a6 = a1.determinant();

	float a7 =  a2.cofactor(0, 0);
	float a8 =  a2.cofactor(0, 1);
	float a9 =  a2.cofactor(0, 2);
	float a10 = a2.cofactor(0, 3);
	float a11 = a2.determinant();

	EXPECT_TRUE(is_equal(a3, 56.0f)) << "matrix 3x3 cofactor bad";
	EXPECT_TRUE(is_equal(a4, 12.0f)) << "matrix 3x3 cofactor bad";
	EXPECT_TRUE(is_equal(a5, -46.0f)) << "matrix 3x3 cofactor bad";
	EXPECT_TRUE(is_equal(a6, -196.0f)) << "matrix 3x3 determinant bad";

	EXPECT_TRUE(is_equal(a7, 690.0f)) << "matrix 4x4 cofactor bad";
	EXPECT_TRUE(is_equal(a8, 447.0f)) << "matrix 4x4 cofactor bad";
	EXPECT_TRUE(is_equal(a9, 210.0f)) << "matrix 4x4 cofactor bad";
	EXPECT_TRUE(is_equal(a10, 51.0f)) << "matrix 4x4 cofactor bad";
	EXPECT_TRUE(is_equal(a11, -4071.0f)) << "matrix 4x4 determinant bad";
}

TEST(MatrixTest, HandlesMatrixInverse)
{
	mat4x4 a1{
		-5.0f,  2.0f,  6.0f, -8.0f,
		 1.0f, -5.0f,  1.0f,  8.0f,
		 7.0f,  7.0f, -6.0f, -7.0f,
		 1.0f, -3.0f,  7.0f,  4.0f
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
		 3.0f, -9.0f,  7.0f,  3.0f,
		 3.0f, -8.0f,  2.0f, -9.0f,
		-4.0f,  4.0f,  4.0f,  1.0f,
		-6.0f,  5.0f, -1.0f,  1.0f
	};
	mat4x4 a5{
		8.0f,  2.0f, 2.0f, 2.0f,
		3.0f, -1.0f, 7.0f, 0.0f,
		7.0f,  0.0f, 5.0f, 4.0f,
		6.0f, -2.0f, 0.0f, 5.0f
	};
	mat4x4 a6 = a4 * a5;


	EXPECT_TRUE(a6 * a5.inverse() == a4) << "matrix 4x4 inverse bad";
}

TEST(TransformationTest, HandlesTranslation)
{
	mat4x4 a1 = translation(5.0f, -3.0f, 2.0f);
	tuple a2 = point(-3.0f, 4.0f, 5.0f);
	tuple a3 = a1 * a2;

	tuple a4 = vector(-3.0f, 4.0f, 5.0f);
	tuple a5 = a1 * a4;

	EXPECT_TRUE(a3 == point(2.0f, 1.0f, 7.0f)) << "translation bad";
	EXPECT_TRUE(a4 == a5) << "translation bad";
}

TEST(TransformationTest, HandlesScaling)
{
	mat4x4 a1 = scaling(2.0f, 3.0f, 4.0f);
	tuple a2 = point(-4.0f, 6.0f, 8.0f);
	tuple a3 = a1 * a2;

	tuple a4 = vector(-4.0f, 6.0f, 8.0f);
	tuple a5 = a1 * a4;

	EXPECT_TRUE(a3 == point(-8.0f, 18.0f, 32.0f)) << "scaling bad";
	EXPECT_TRUE(a5 == vector(-8.0f, 18.0f, 32.0f)) << "scaling bad";
}

TEST(TransformationTest, HandlesRotation)
{
	float deg90 = PI / 2.0f;
	float deg45 = PI / 4.0f;

	mat4x4 a1 = rotation(deg90, 0.0f, 0.0f);
	tuple a2 = point(0.0f, 1.0f, 0.0f);

	mat4x4 a3 = rotation(0.0f, deg90, 0.0f);
	tuple a4 = point(0.0f, 0.0f, 1.0f);

	mat4x4 a5 = rotation(0.0f, 0.0f, deg90);
	tuple a6 = point(0.0f, 1.0f, 0.0f);

	tuple a7 = a1 * a2;
	tuple a8 = a3 * a4;
	tuple a9 = a5 * a6;

	EXPECT_TRUE(a7 == point(0.0f, 0.0f, 1.0f)) << "rotation bad";
	EXPECT_TRUE(a8 == point(1.0f, 0.0f, 0.0f)) << "rotation bad";
	EXPECT_TRUE(a9 == point(-1.0f, 0.0f, 0.0f)) << "rotation bad";

	mat4x4 a10 = rotation(deg45, 0.0f, deg45);
	tuple a11 = point(0.0f, 1.0f, 0.0f);

	tuple a12 = a10 * a11;

	EXPECT_TRUE(a12 == point(-0.5f, 0.5f, 0.7071f)) << "rotation bad";
}

TEST(TransformationTest, HandlesShearing)
{
	tuple a1 = point(2.0f, 3.0f, 4.0f);

	mat4x4 a2 = shearing(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	mat4x4 a3 = shearing(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	mat4x4 a4 = shearing(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	mat4x4 a5 = shearing(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	mat4x4 a6 = shearing(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	mat4x4 a7 = shearing(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	EXPECT_TRUE(a2 * a1 == point(5.0f, 3.0f, 4.0f)) << "shearing bad";
	EXPECT_TRUE(a3 * a1 == point(6.0f, 3.0f, 4.0f)) << "shearing bad";
	EXPECT_TRUE(a4 * a1 == point(2.0f, 5.0f, 4.0f)) << "shearing bad";
	EXPECT_TRUE(a5 * a1 == point(2.0f, 7.0f, 4.0f)) << "shearing bad";
	EXPECT_TRUE(a6 * a1 == point(2.0f, 3.0f, 6.0f)) << "shearing bad";
	EXPECT_TRUE(a7 * a1 == point(2.0f, 3.0f, 7.0f)) << "shearing bad";
}

TEST(TransformationTest, HandlesMultipleTransform)
{
	tuple a1 = point(1.0f, 0.0f, 1.0f);

	mat4x4 a2 = rotation(PI / 2.0f, 0.0f, 0.0f);
	mat4x4 a3 = scaling(5.0f, 5.0f, 5.0f);
	mat4x4 a4 = translation(10.0f, 5.0f, 7.0f);

	tuple a5 = (a4 * a3 * a2) * a1;

	EXPECT_TRUE(a5 == point(15.0f, 0.0f, 7.0f)) << "shearing bad";
}

TEST(RayTest, HandlesRayCreation)
{
	tuple a1{ point(1.0f, 2.0f, 3.0f) };
	tuple a2{ vector(4.0f, 5.0f, 6.0f) };
	ray a3{ a1, a2 };
	ray a4{ point(2.0f, 3.0f, 4.0f), vector(1.0f, 0.0f, 0.0f) };

	EXPECT_TRUE(a3.m_origin == a1) << "ray origin bad";
	EXPECT_TRUE(a3.m_direction == a2) << "ray direction bad";
	EXPECT_TRUE(a4.position(0.0f) == point(2.0f, 3.0f, 4.0f)) << "ray position bad";
	EXPECT_TRUE(a4.position(1.0f) == point(3.0f, 3.0f, 4.0f)) << "ray position bad";
	EXPECT_TRUE(a4.position(-1.0f) == point(1.0f, 3.0f, 4.0f)) << "ray position bad";
	EXPECT_TRUE(a4.position(2.5f) == point(4.5f, 3.0f, 4.0f)) << "ray position bad";
}

TEST(RayTest, HandlesRaySphereIntersection)
{
	ray a1{ point(0.0f, 0.0f, -5.0f), vector(0.0f, 0.0f, 1.0f) };
	sphere a2;
	a1.intersect(a2);

	EXPECT_TRUE(a1.m_intersections.size() == 2) << "ray sphere intersection bad";
	EXPECT_TRUE(is_equal(a1.m_intersections[0].m_time, 4.0f)) << "ray sphere intersection bad";
	EXPECT_TRUE(is_equal(a1.m_intersections[1].m_time, 6.0f)) << "ray sphere intersection bad";

	ray a3{ point(0.0f, 1.0f, -5.0f), vector(0.0f, 0.0f, 1.0f) };
	sphere a4;
	a3.intersect(a4);

	EXPECT_TRUE(a3.m_intersections.size() == 2) << "ray sphere intersection bad";
	EXPECT_TRUE(is_equal(a3.m_intersections[0].m_time, 5.0f)) << "ray sphere intersection bad";
	EXPECT_TRUE(is_equal(a3.m_intersections[1].m_time, 5.0f)) << "ray sphere intersection bad";

	ray a5{ point(0.0f, 2.0f, -5.0f), vector(0.0f, 0.0f, 1.0f) };
	sphere a6;
	a5.intersect(a6);

	EXPECT_TRUE(a5.m_intersections.size() == 0) << "ray sphere intersection bad";

	ray a7{ point(0.0f, 0.0f, 0.0f), vector(0.0f, 0.0f, 1.0f) };
	sphere a8;
	a7.intersect(a8);

	EXPECT_TRUE(is_equal(a7.m_intersections[0].m_time, -1.0f)) << "ray sphere intersection bad";
	EXPECT_TRUE(is_equal(a7.m_intersections[1].m_time, 1.0f)) << "ray sphere intersection bad";

	ray a9{ point(0.0f, 0.0f, 5.0f), vector(0.0f, 0.0f, 1.0f) };
	sphere a10;
	a9.intersect(a10);

	EXPECT_TRUE(is_equal(a9.m_intersections[0].m_time, -6.0f)) << "ray sphere intersection bad";
	EXPECT_TRUE(is_equal(a9.m_intersections[1].m_time, -4.0f)) << "ray sphere intersection bad";
}

TEST(RayTest, HandlesRayIntersection)
{
	sphere a1;
	intersection a2{ 0.0f, a1 };

	EXPECT_TRUE(is_equal(a2.m_time, 0.0f)) << "ray sphere intersection bad";
	EXPECT_TRUE(a2.m_obj == &a1) << "ray sphere intersection bad";
}

TEST(RayTest, HandlesRayHits)
{
	sphere a1;
	ray a2;
	intersection a3{ -2.0f, a1 };
	intersection a4{ -1.0f, a1 };
	a2.add_intersection(a4);
	a2.add_intersection(a3);
	intersection a5 = a2.hit();

	EXPECT_TRUE(a5.m_time == INFINITY) << "ray hits bad";

	intersection a6{ 5.0f, a1 };
	intersection a7{ 7.0f, a1 };
	intersection a8{ -3.0f, a1 };
	intersection a9{ 2.0f, a1 };
	ray a10;
	a10.add_intersection(a6);
	a10.add_intersection(a7);
	a10.add_intersection(a8);
	a10.add_intersection(a9);
	intersection a11 = a10.hit();

	EXPECT_TRUE(a11.m_time == a9.m_time) << "ray hits bad";
	EXPECT_TRUE(a11.m_obj == a9.m_obj) << "ray hits bad";
}

TEST(RayTest, HandlesRayScale)
{
	ray a1{ point(1.0f, 2.0f, 3.0f), vector(0.0f, 1.0f, 0.0f) };
	mat4x4 a2{ translation(3.0f, 4.0f, 5.0f) };
	auto a3 = a1.transform(a2);

	EXPECT_TRUE(a3.first == point(4.0f, 6.0f, 8.0f)) << "ray hits bad";
	EXPECT_TRUE(a3.second == vector(0.0f, 1.0f, 0.0f)) << "ray hits bad";

	ray a4{ point(1.0f, 2.0f, 3.0f), vector(0.0f, 1.0f, 0.0f) };
	mat4x4 a5{ scaling(2.0f, 3.0f, 4.0f) };
	auto a6 = a4.transform(a5);

	EXPECT_TRUE(a6.first == point(2.0f, 6.0f, 12.0f)) << "ray hits bad";
	EXPECT_TRUE(a6.second == vector(0.0f, 3.0f, 0.0f)) << "ray hits bad";

	ray a7{ point(0.0f, 0.0f, -5.0f), vector(0.0f, 0.0f, 1.0f) };
	sphere a8{ scaling(2.0f, 2.0f, 2.0f) };
	a7.intersect(a8);

	EXPECT_TRUE(is_equal(a7.m_intersections[0].m_time, 3.0f)) << "ray hits bad";
	EXPECT_TRUE(is_equal(a7.m_intersections[1].m_time, 7.0f)) << "ray hits bad";
}

TEST(LightingTest, HandlesNormals)
{
	sphere a1;

	EXPECT_TRUE(a1.normal_at(point(1.0f, 0.0f, 0.0f)) == vector(1.0f, 0.0f, 0.0f)) << "normal bad";
	EXPECT_TRUE(a1.normal_at(point(0.0f, 1.0f, 0.0f)) == vector(0.0f, 1.0f, 0.0f)) << "normal bad";
	EXPECT_TRUE(a1.normal_at(point(0.0f, 0.0f, 1.0f)) == vector(0.0f, 0.0f, 1.0f)) << "normal bad";
	EXPECT_TRUE(a1.normal_at(point(sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f)) == vector(sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f)) << "normal bad";

	sphere a2{ translation(0.0f, 1.0f, 0.0f) };
	tuple a3 = a2.normal_at(point(0, 1.70711f, -0.70711f));

	EXPECT_TRUE(a3 == vector(0, 0.70711f, -0.70711f)) << "normal bad";

	sphere a4{ scaling(1.0f, 0.5f, 1.0f) * rotation(0.0f, 0.0f, PI / 5.0f) };
	tuple a5 = a4.normal_at(point(0.0f, sqrt(2.0f) / 2.0f, -sqrt(2.0f) / 2.0f));

	EXPECT_TRUE(a5 == vector(0.0f, 0.97014f, -0.24254f)) << "normal bad";
}

TEST(LightingTest, HandlesReflections)
{
	tuple a1{ vector(1.0f, -1.0f, 0.0f) };
	tuple a2{ vector(0.0f, 1.0f, 0.0f) };
	tuple a3 = reflect(a1, a2);

	EXPECT_TRUE(a3 == vector(1.0f, 1.0f, 0.0f)) << "reflection bad";

	tuple a4{ vector(0.0f, -1.0f, 0.0f) };
	tuple a5{ vector(sqrt(2.0f) / 2.0f, sqrt(2.0f) / 2.0f, 0.0f) };
	tuple a6 = reflect(a4, a5);

	EXPECT_TRUE(a6 == vector(1.0f, 0.0f, 0.0f)) << "reflection bad";
}

TEST(LightingTest, HandlesPointLight)
{
	pt_lght a1{ point(0.0f, 0.0f, 0.0f), color(1.0f, 1.0f, 1.0f) };

	EXPECT_TRUE(a1.m_pos == point(0.0f, 0.0f, 0.0f)) << "point light position bad";
	EXPECT_TRUE(a1.m_intensity == color(1.0f, 1.0f, 1.0f)) << "point light intensity bad";
}

TEST(LightingTest, HandlesMaterials)
{
	sphere a1;
	material a2;

	EXPECT_TRUE(a1.m_material.m_albedo == a2.m_albedo) << "material albedo bad";
	EXPECT_TRUE(a1.m_material.m_ambient == a2.m_ambient) << "material ambient bad";
	EXPECT_TRUE(a1.m_material.m_diffuse == a2.m_diffuse) << "material diffuse bad";
	EXPECT_TRUE(a1.m_material.m_shininess == a2.m_shininess) << "material shininess bad";
	EXPECT_TRUE(a1.m_material.m_specular == a2.m_specular) << "material specular bad";
}

TEST(LightingTest, HandlesLightCalculation)
{
	material m1;
	tuple a0{ point(0.0f, 0.0f, 0.0f) };
	tuple a1{ vector(0.0f, 0.0f, -1.0f) };
	tuple a2{ vector(0.0f, 0.0f, -1.0f) };
	pt_lght a3{ point(0.0f, 0.0f, -10.0f), color(1.0f, 1.0f, 1.0f) };
	tuple a4{ lighting(m1, a3, a0, a1, a2) };

	EXPECT_TRUE(a4 == color(1.9f, 1.9f, 1.9f)) << "material albedo bad";

	tuple a5{ vector(0.0f, sqrt(2.0f) / 2.0f, sqrt(2.0f) / 2.0f) };
	tuple a6{ vector(0.0f, 0.0f, -1.0f) };
	pt_lght a7{ point(0.0f, 0.0f, -10.0f), color(1.0f, 1.0f, 1.0f) };
	tuple a8{ lighting(m1, a7, a0, a5, a6) };

	EXPECT_TRUE(a8 == color(1.0f, 1.0f, 1.0f)) << "material albedo bad";

	tuple a9{ vector(0.0f, 0.0f, -1.0f) };
	tuple a10{ vector(0.0f, 0.0f, -1.0f) };
	pt_lght a11{ point(0.0f, 10.0f, -10.0f), color(1.0f, 1.0f, 1.0f) };
	tuple a12{ lighting(m1, a11, a0, a9, a10) };

	EXPECT_TRUE(a12 == color(0.7364f, 0.7364f, 0.7364f)) << "material albedo bad";

	tuple a13{ vector(0.0f, -sqrt(2.0f) / 2.0f, -sqrt(2.0f) / 2.0f) };
	tuple a14{ vector(0.0f, 0.0f, -1.0f) };
	pt_lght a15{ point(0.0f, 10.0f, -10.0f), color(1.0f, 1.0f, 1.0f) };
	tuple a16{ lighting(m1, a15, a0, a13, a14) };

	EXPECT_TRUE(a16 == color(1.6364f, 1.6364f, 1.6364f)) << "material albedo bad";

	tuple a17{ vector(0.0f, 0.0f, 1.0f) };
	tuple a18{ vector(0.0f, 0.0f, -1.0f) };
	pt_lght a19{ point(0.0f, 0.0f, 10.0f), color(1.0f, 1.0f, 1.0f) };
	tuple a20{ lighting(m1, a19, a0, a17, a18) };

	EXPECT_TRUE(a20 == color(0.1f, 0.1f, 0.1f)) << "material albedo bad";
}

TEST(WorldTest, HandlesWorldIntersection)
{
	world w1;
	w1.add_light(pt_lght{ point(-10.0f, 10.0f, -10.0f), color(1.0f, 1.0f, 1.0f) });
	w1.add_object(sphere{ material{ color(0.8f, 1.0f, 0.6f) } });
	w1.m_spheres[0].m_material.m_diffuse = 0.7f;
	w1.m_spheres[0].m_material.m_specular = 0.2f;
	w1.add_object(sphere{ scaling(0.5f, 0.5f, 0.5f) });

	ray r1{ point(0.0f, 0.0f, -5.0f), vector(0.0f, 0.0f, 1.0f) };
	r1.intersect(w1);
	EXPECT_TRUE(r1.m_intersections.size() == 4) << "world intersect bad";
	EXPECT_TRUE(is_equal(r1.m_intersections[0].m_time, 4.0f)) << "world intersect bad";
	EXPECT_TRUE(is_equal(r1.m_intersections[2].m_time, 4.5f)) << "world intersect bad";
	EXPECT_TRUE(is_equal(r1.m_intersections[3].m_time, 5.5f)) << "world intersect bad";
	EXPECT_TRUE(is_equal(r1.m_intersections[1].m_time, 6.0f)) << "world intersect bad";
}

TEST(WorldTest, HandlesCompData)
{
	ray r1{ point(0.0f, 0.0f, -5.0f), vector(0.0f, 0.0f, 1.0f) };
	sphere s1;
	intersection i1{ 1.0f, s1 };
	r1.add_intersection(i1);
	comp_data c1 = r1.get_comp_data();

	EXPECT_TRUE(c1.is_inside == false);

	ray r2{ point(0.0f, 0.0f, 0.0f), vector(0.0f, 0.0f, 1.0f) };
	sphere s2;
	intersection i2{ 1.0f, s2 };
	r2.add_intersection(i2);
	comp_data c2 = r2.get_comp_data();

	EXPECT_TRUE(c2.is_inside == true);
	EXPECT_TRUE(c2.pt == point(0.0f, 0.0f, 1.0f));
	EXPECT_TRUE(c2.eyev == vector(0.0f, 0.0f, -1.0f)); 
	EXPECT_TRUE(c2.normalv == vector(0.0f, 0.0f, -1.0f));
}

TEST(WorldTest, HandlesWorldShading)
{
	world w1;
	w1.add_light(pt_lght{ point(-10.0f, 10.0f, -10.0f), color(1.0f, 1.0f, 1.0f) });
	w1.add_object(sphere{ material{ color(0.8f, 1.0f, 0.6f) } });
	w1.m_spheres[0].m_material.m_diffuse = 0.7f;
	w1.m_spheres[0].m_material.m_specular = 0.2f;
	w1.add_object(sphere{ scaling(0.5f, 0.5f, 0.5f) });

	ray r1{ point(0.0f, 0.0f, -5.0f), vector(0.0f, 0.0f, 1.0f) };
	intersection i1{ 4.0f, w1.m_spheres[0] };
	r1.add_intersection(i1);
	comp_data cd1 = r1.get_comp_data();
	tuple c1 = w1.shade_hit(cd1);
	EXPECT_TRUE(c1 == color(0.38066f, 0.47583f, 0.2855f));

	w1.m_point_lights[0] = pt_lght{ point(0.0f, 0.25f, 0.0f), color(1.0f, 1.0f, 1.0f) };
	ray r2{ point(0.0f, 0.0f, 0.0f), vector(0.0f, 0.0f, 1.0f) };
	intersection i2{ 0.5f, w1.m_spheres[1] };
	r2.add_intersection(i2);
	comp_data cd2 = r2.get_comp_data();
	tuple c2 = w1.shade_hit(cd2);
	EXPECT_TRUE(c2 == color(0.90498f, 0.90498f, 0.90498f));

	w1.m_point_lights[0] = pt_lght{ point(-10.0f, 10.0f, -10.0f), color(1.0f, 1.0f, 1.0f) };
	ray r3 = ray(point(0.0f, 0.0f, -5.0f), vector(0.0f, 0.0f, 1.0f));
	tuple c3 = color_at(w1, r3);
	EXPECT_TRUE(c3 == color(0.38066f, 0.47583f, 0.2855f));

	ray r4 = ray(point(0.0f, 0.0f, 0.75f), vector(0.0f, 0.0f, -1.0f));
	w1.m_spheres[0].m_material.m_ambient = 1.0f;
	w1.m_spheres[1].m_material.m_ambient = 1.0f;
	tuple c4 = color_at(w1, r4);
	EXPECT_TRUE(c4 == w1.m_spheres[1].m_material.m_albedo);
}

TEST(WorldTest, HandlesViewTransform)
{
	tuple fr1 =  point(0.0f, 0.0f, 0.0f);
	tuple to1 = point(0.0f, 0.0f, -1.0f);
	tuple up1 = vector(0.0f, 1.0f, 0.0f);
	mat4x4 t1 = view_transform(fr1, to1, up1);
	EXPECT_TRUE(t1 == i4x4);

	tuple fr2 = point(0.0f, 0.0f, 0.0f);
	tuple to2 = point(0.0f, 0.0f, 1.0f);
	tuple up2 = vector(0.0f, 1.0f, 0.0f);
	mat4x4 t2 = view_transform(fr2, to2, up2);
	EXPECT_TRUE(t2 == scaling(-1.0f, 1.0f, -1.0f));

	tuple fr3 = point(0.0f, 0.0f, 8.0f);
	tuple to3 = point(0.0f, 0.0f, 0.0f);
	tuple up3 = vector(0.0f, 1.0f, 0.0f);
	mat4x4 t3 = view_transform(fr3, to3, up3);
	EXPECT_TRUE(t3 == translation(0.0f, 0.0f, -8.0f));

	tuple fr4 = point(1.0f, 3.0f, 2.0f);
	tuple to4 = point(4.0f, -2.0f, 8.0f);
	tuple up4 = vector(1.0f, 1.0f, 0.0f);
	mat4x4 t4 = view_transform(fr4, to4, up4);
	mat4x4 t4res{
		-0.50709f, 0.50709f,  0.67612f, -2.36643f,
		 0.76772f, 0.60609f,  0.12122f, -2.82843f,
		-0.35857f, 0.59761f, -0.71714f,  0.00000f,
		 0.00000f, 0.00000f,  0.00000f,  1.00000f
	};
	EXPECT_TRUE(t4 == t4res);
}

TEST(CameraTest, HandlesCameraCreation)
{
	Camera c{ 160, 120, PI / 2.0f };

	EXPECT_TRUE(c.m_hsize == 160);
	EXPECT_TRUE(c.m_vsize == 120);
	EXPECT_TRUE(is_equal(c.m_fov, PI / 2.0f));
	EXPECT_TRUE(c.m_transform == i4x4);

	Camera c2{ 200, 125, PI / 2.0f };
	EXPECT_TRUE(is_equal(c2.m_pixel_size, 0.01f));

	Camera c3{ 125, 200, PI / 2.0f };
	EXPECT_TRUE(is_equal(c3.m_pixel_size, 0.01f));
}


TEST(CameraTest, HandlesRayPerPixel)
{
	Camera c1{ 201, 101, PI / 2.0f };
	ray r1 = c1.ray_for_pixel(100, 50);
	EXPECT_TRUE(r1.m_origin == point(0.0f, 0.0f, 0.0f));
	EXPECT_TRUE(r1.m_direction == vector(0.0f, 0.0f, -1.0f));

	Camera c2{ 201, 101, PI / 2.0f };
	ray r2 = c2.ray_for_pixel(0, 0);
	EXPECT_TRUE(r2.m_origin == point(0.0f, 0.0f, 0.0f));
	EXPECT_TRUE(r2.m_direction == vector(0.66519f, 0.33259f, -0.66851f));

	Camera c3{ 201, 101, PI / 2.0f };
	c3.m_transform = rotation(0.0f, PI / 4.0f, 0.0f) * translation(0.0f, -2.0f, 5.0f);
	ray r3 = c3.ray_for_pixel(100, 50);
	EXPECT_TRUE(r3.m_origin == point(0.0f, 2.0f, -5.0f));
	EXPECT_TRUE(r3.m_direction == vector(sqrt(2.0f) / 2.0f, 0.0f, -sqrt(2.0f) / 2.0f));
}

TEST(RenderTest, HandlesRendering)
{
	world w = default_world();
	Camera c{ 11, 11, PI / 2.0f };
	c.m_transform = view_transform(point(0.0f, 0.0f, -5.0f), point(0.0f, 0.0f, 0.0f), vector(0.0f, 1.0f, 0.0f));
	ImgBuf img{ render(c, w) };
	EXPECT_TRUE(img.pixel_at(5, 5) == color(0.38066f, 0.47583f, 0.2855f));
}