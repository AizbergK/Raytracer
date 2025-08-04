#include "Matrix.hpp"

// === 2x2 MATRICES ===
bool mat2x2::operator==(const mat2x2& other) const
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (!is_equal(this->m_data[i][j], other.m_data[i][j])) return false;

    return true;
}

bool mat2x2::operator!=(const mat2x2& other) const
{
    return !(*this == other);
}

float mat2x2::determinant() const
{
    return m_data[0][0] * m_data[1][1] - m_data[0][1] * m_data[1][0];
}

// === 3x3 MATRICES ===
bool mat3x3::operator==(const mat3x3& other) const
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (!is_equal(this->m_data[i][j], other.m_data[i][j])) return false;

    return true;
}

bool mat3x3::operator!=(const mat3x3& other) const
{
    return !(*this == other);
}

mat2x2 mat3x3::submatrix(int row, int col) const
{
    mat2x2 result;
    int past_row = 0;

    for (int i = 0; i < 3; i++)
    {
        if (i == row)
        {
            past_row = 1;
            continue;
        }
        int past_col = 0;
        for (int j = 0; j < 3; j++)
        {
            if (j == col)
            {
                past_col = 1;
                continue;
            }
            result.m_data[i - past_row][j - past_col] = this->m_data[i][j];
        }
    }

    return result;
}

float mat3x3::minor(int row, int col) const
{
    mat2x2 temp = this->submatrix(row, col);
    return temp.determinant();
}

float mat3x3::cofactor(int row, int col) const
{
    float det = this->minor(row, col);
    if ((row + col) % 2 == 0)
        return det;
    else
        return -det;
}

float mat3x3::determinant() const
{
    float result = 0.0f;
    for (int i = 0; i < 3; i++)
    {
        result += this->m_data[0][i] * this->cofactor(0, i);
    }

    return result;
}

// === 4x4 MATRICES ===
bool mat4x4::operator==(const mat4x4& other) const
{
    for (int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if (!is_equal(this->m_data[i][j], other.m_data[i][j])) return false;

    return true;
}

bool mat4x4::operator!=(const mat4x4& other) const
{
    return !(*this == other);
}

mat4x4 mat4x4::operator*(const mat4x4& other) const
{
    mat4x4 result;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                result.m_data[i][j] += this->m_data[i][k] * other.m_data[k][j];
                
    return result;
}

tuple mat4x4::operator*(const tuple& other) const
{
    tuple result;

    result.x += this->m_data[0][0] * other.x;
    result.x += this->m_data[0][1] * other.y;
    result.x += this->m_data[0][2] * other.z;
    result.x += this->m_data[0][3] * other.w;

    result.y += this->m_data[1][0] * other.x;
    result.y += this->m_data[1][1] * other.y;
    result.y += this->m_data[1][2] * other.z;
    result.y += this->m_data[1][3] * other.w;

    result.z += this->m_data[2][0] * other.x;
    result.z += this->m_data[2][1] * other.y;
    result.z += this->m_data[2][2] * other.z;
    result.z += this->m_data[2][3] * other.w;

    result.w += this->m_data[3][0] * other.x;
    result.w += this->m_data[3][1] * other.y;
    result.w += this->m_data[3][2] * other.z;
    result.w += this->m_data[3][3] * other.w;

    return result;
}

mat4x4 mat4x4::transpose() const
{
    mat4x4 result;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result.m_data[i][j] = this->m_data[j][i];

    return result;
}

mat3x3 mat4x4::submatrix(int row, int col) const
{
    mat3x3 result;
    int past_row = 0;

    for(int i = 0; i < 4; i++)
    {
        if (i == row)
        {
            past_row = 1;
            continue;
        }
        int past_col = 0;
        for (int j = 0; j < 4; j++)
        {
            if (j == col)
            {
                past_col = 1;
                continue;
            }
            result.m_data[i - past_row][j - past_col] = this->m_data[i][j];
        }
    }

    return result;
}

float mat4x4::minor(int row, int col) const
{
    mat3x3 temp = this->submatrix(row, col);
    return temp.determinant();
}

float mat4x4::cofactor(int row, int col) const
{
    float det = this->minor(row, col);
    if ((row + col) % 2 == 0)
        return det;
    else
        return -det;
}

float mat4x4::determinant() const
{
    float result = 0.0f;
    for (int i = 0; i < 4; i++)
    {
        result += this->m_data[0][i] * this->cofactor(0, i);
    }

    return result;
}

mat4x4 mat4x4::inverse() const
{
    mat4x4 result;

    float det = this->determinant();
    if (is_equal(det, 0.0f)) throw;

    for(int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.m_data[j][i] = this->cofactor(i, j) / det;
        }
    }

    return result;
}

mat4x4 translation(float x, float y , float z)
{
    mat4x4 result = i4x4;
    result.m_data[0][3] = x;
    result.m_data[1][3] = y;
    result.m_data[2][3] = z;

    return result;
}

mat4x4 scaling(float x, float y, float z)
{
    mat4x4 result = i4x4;
    result.m_data[0][0] = x;
    result.m_data[1][1] = y;
    result.m_data[2][2] = z;

    return result;
}

mat4x4 rotation(float x, float y, float z)
{
    mat4x4 rotx = i4x4;
    mat4x4 roty = i4x4;
    mat4x4 rotz = i4x4;
    mat4x4 result = i4x4;

    rotx.m_data[1][1] =  cos(x);
    rotx.m_data[1][2] = -sin(x);
    rotx.m_data[2][1] =  sin(x);
    rotx.m_data[2][2] =  cos(x);

    roty.m_data[0][0] =  cos(y);
    roty.m_data[0][2] =  sin(y);
    roty.m_data[2][0] = -sin(y);
    roty.m_data[2][2] =  cos(y);

    rotz.m_data[0][0] =  cos(z);
    rotz.m_data[0][1] = -sin(z);
    rotz.m_data[1][0] =  sin(z);
    rotz.m_data[1][1] =  cos(z);

    result = rotz * roty * rotx;

    return result;
}

mat4x4 shearing(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy)
{
    mat4x4 result = i4x4;
    result.m_data[0][1] = Xy;
    result.m_data[0][2] = Xz;

    result.m_data[1][0] = Yx;
    result.m_data[1][2] = Yz;

    result.m_data[2][0] = Zx;
    result.m_data[2][1] = Zy;

    return result;
}

mat4x4 view_transform(tuple from, tuple to, tuple up)
{
    mat4x4 result = i4x4;

    tuple forward = normalize(to - from);
    tuple left = cross(forward, normalize(up));
    tuple true_up = cross(left, forward);

    result.m_data[0][0] = left.x;
    result.m_data[0][1] = left.y;
    result.m_data[0][2] = left.z;

    result.m_data[1][0] = true_up.x;
    result.m_data[1][1] = true_up.y;
    result.m_data[1][2] = true_up.z;

    result.m_data[2][0] = -forward.x;
    result.m_data[2][1] = -forward.y;
    result.m_data[2][2] = -forward.z;

    result = result * translation(-from.x, -from.y, -from.z);

    return result;
}