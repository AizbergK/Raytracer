#ifndef _MATRIX_  
#define _MATRIX_  
#include "Tuples.hpp"

class mat2x2 {
public:
    double m_data[2][2] = {};

    constexpr mat2x2() = default;
    constexpr mat2x2(
        double m00, double m01,
        double m10, double m11)
        : m_data{
              {m00, m01},
              {m10, m11}
        } {};

    bool operator==(const mat2x2&) const;
    bool operator!=(const mat2x2&) const;

    double determinant() const;
};

constexpr mat2x2 i2x2{
   1.0, 0.0,
   0.0, 1.0
};

class mat3x3 {
public:
    double m_data[3][3] = {};

    constexpr mat3x3() = default;
    constexpr mat3x3(
        double m00, double m01, double m02,
        double m10, double m11, double m12,
        double m20, double m21, double m22)
        : m_data{
              {m00, m01, m02},
              {m10, m11, m12},
              {m20, m21, m22}
        } {};

    bool operator==(const mat3x3&) const;
    bool operator!=(const mat3x3&) const;

    mat2x2 submatrix(int, int) const;
    double minor(int, int) const;
    double cofactor(int, int) const;

    double determinant() const;
};

constexpr mat3x3 i3x3{
   1.0, 0.0, 0.0,
   0.0, 1.0, 0.0,
   0.0, 0.0, 1.0
};

class mat4x4 {  
public:  
    double m_data[4][4] = {};  

    constexpr mat4x4() = default;
    constexpr mat4x4(
        double m00, double m01, double m02, double m03,
        double m10, double m11, double m12, double m13,
        double m20, double m21, double m22, double m23,
        double m30, double m31, double m32, double m33)
        : m_data{
              {m00, m01, m02, m03},
              {m10, m11, m12, m13},
              {m20, m21, m22, m23},
              {m30, m31, m32, m33}
        } {};

    bool operator==(const mat4x4&) const;
    bool operator!=(const mat4x4&) const;
    mat4x4 operator*(const mat4x4&) const;

    template <typename Derived>
    Derived operator*(const Tuple4<Derived>& other) const
    {
        Derived result;

        result.x = this->m_data[0][0] * other.x;
        result.x += this->m_data[0][1] * other.y;
        result.x += this->m_data[0][2] * other.z;
        result.x += this->m_data[0][3] * other.w;

        result.y = this->m_data[1][0] * other.x;
        result.y += this->m_data[1][1] * other.y;
        result.y += this->m_data[1][2] * other.z;
        result.y += this->m_data[1][3] * other.w;

        result.z = this->m_data[2][0] * other.x;
        result.z += this->m_data[2][1] * other.y;
        result.z += this->m_data[2][2] * other.z;
        result.z += this->m_data[2][3] * other.w;

        result.w = this->m_data[3][0] * other.x;
        result.w += this->m_data[3][1] * other.y;
        result.w += this->m_data[3][2] * other.z;
        result.w += this->m_data[3][3] * other.w;

        return result;
    }

    mat4x4 transpose() const;

    mat3x3 submatrix(int, int) const;
    double minor(int, int) const;
    double cofactor(int, int) const;

    double determinant() const;
    mat4x4 inverse() const;

};

mat4x4 translation(double, double, double);
mat4x4 scaling(double, double, double);
mat4x4 rotation(double, double, double);
mat4x4 TRS(Point4 translate, Point4 rotate = Point4(0.0, 0.0, 0.0), Point4 scale = Point4(1.0, 1.0, 1.0));
mat4x4 shearing(double, double, double, double, double, double);

mat4x4 view_transform(Point4 from, Point4 to, Vector4 up);

 constexpr mat4x4 i4x4{
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
};

#endif
