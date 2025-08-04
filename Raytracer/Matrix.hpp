#ifndef _MATRIX_  
#define _MATRIX_  

#include <cstring>  
#include <algorithm>

#include "Helpers.hpp" 
#include "Tuples.hpp"

class mat2x2 {
public:
    float m_data[2][2] = {};

    constexpr mat2x2() = default;
    constexpr mat2x2(
        float m00, float m01,
        float m10, float m11)
        : m_data{
              {m00, m01},
              {m10, m11}
        } {};

    bool operator==(const mat2x2&) const;
    bool operator!=(const mat2x2&) const;

    float determinant() const;
};

constexpr mat2x2 i2x2{
   1.0f, 0.0f,
   0.0f, 1.0f
};

class mat3x3 {
public:
    float m_data[3][3] = {};

    constexpr mat3x3() = default;
    constexpr mat3x3(
        float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22)
        : m_data{
              {m00, m01, m02},
              {m10, m11, m12},
              {m20, m21, m22}
        } {};

    bool operator==(const mat3x3&) const;
    bool operator!=(const mat3x3&) const;

    mat2x2 submatrix(int, int) const;
    float minor(int, int) const;
    float cofactor(int, int) const;

    float determinant() const;
};

constexpr mat3x3 i3x3{
   1.0f, 0.0f, 0.0f,
   0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 1.0f
};

class mat4x4 {  
public:  
    float m_data[4][4] = {};  

    constexpr mat4x4() = default;
    constexpr mat4x4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33)
        : m_data{
              {m00, m01, m02, m03},
              {m10, m11, m12, m13},
              {m20, m21, m22, m23},
              {m30, m31, m32, m33}
        } {};

    bool operator==(const mat4x4&) const;
    bool operator!=(const mat4x4&) const;
    mat4x4 operator*(const mat4x4&) const;
    tuple operator*(const tuple&) const;

    mat4x4 transpose() const;

    mat3x3 submatrix(int, int) const;
    float minor(int, int) const;
    float cofactor(int, int) const;

    float determinant() const;
    mat4x4 inverse() const;

};

mat4x4 translation(float, float, float);
mat4x4 scaling(float, float, float);
mat4x4 rotation(float, float, float);
mat4x4 shearing(float, float, float, float, float, float);

mat4x4 view_transform(tuple from, tuple to, tuple up);

 constexpr mat4x4 i4x4{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

#endif
