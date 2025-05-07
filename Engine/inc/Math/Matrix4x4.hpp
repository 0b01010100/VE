#pragma once
#include <memory>
#include "Vector3D.hpp"
#include "Vector4D.hpp"
#include <cstring>
#include <cmath>

class Matrix4x4
{
public:
    // Constructor - initializes identity matrix
    Matrix4x4()
    {
        setIdentity();
    }

    // Set matrix to identity
    void setIdentity()
    {
        std::memset(m_mat, 0, sizeof(float) * 16);
        m_mat[0] = 1.0f;  // [0][0]
        m_mat[5] = 1.0f;  // [1][1]
        m_mat[10] = 1.0f; // [2][2]
        m_mat[15] = 1.0f; // [3][3]
    }

    // Set translation component
    void setTranslation(const Vector3D& translation)
    {
        m_mat[12] = translation.x; // [3][0]
        m_mat[13] = translation.y; // [3][1]
        m_mat[14] = translation.z; // [3][2]
    }

    // Set scale component
    void setScale(const Vector3D& scale)
    {
        m_mat[0] = scale.x;  // [0][0]
        m_mat[5] = scale.y;  // [1][1]
        m_mat[10] = scale.z; // [2][2]
    }

    // Set rotation around X axis
    void setRotationX(float x)
    {
        m_mat[5] = std::cos(x);   // [1][1]
        m_mat[6] = std::sin(x);   // [1][2]
        m_mat[9] = -std::sin(x);  // [2][1]
        m_mat[10] = std::cos(x);  // [2][2]
    }

    // Set rotation around Y axis
    void setRotationY(float y)
    {
        m_mat[0] = std::cos(y);   // [0][0]
        m_mat[2] = -std::sin(y);  // [0][2]
        m_mat[8] = std::sin(y);   // [2][0]
        m_mat[10] = std::cos(y);  // [2][2]
    }

    // Set rotation around Z axis
    void setRotationZ(float z)
    {
        m_mat[0] = std::cos(z);   // [0][0]
        m_mat[1] = std::sin(z);   // [0][1]
        m_mat[4] = -std::sin(z);  // [1][0]
        m_mat[5] = std::cos(z);   // [1][1]
    }

    // Get determinant of the matrix
    float getDeterminant()
    {
        Vector4D minor, v1, v2, v3;

        v1 = Vector4D(m_mat[0], m_mat[4], m_mat[8], m_mat[12]);   // First column
        v2 = Vector4D(m_mat[1], m_mat[5], m_mat[9], m_mat[13]);   // Second column
        v3 = Vector4D(m_mat[2], m_mat[6], m_mat[10], m_mat[14]);  // Third column

        minor.cross(v1, v2, v3);
        float det = -(m_mat[3] * minor.x + m_mat[7] * minor.y + 
                     m_mat[11] * minor.z + m_mat[15] * minor.w);
        return det;
    }

    // Inverse the matrix
    void inverse()
    {
        int a, i, j;
        Matrix4x4 out;
        Vector4D v, vec[3];
        float det = 0.0f;

        det = this->getDeterminant();
        if (!det) return; // If zero or less than zero this matrix is not invertible
        
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                if (j != i)
                {
                    a = j;
                    if (j > i) a = a - 1;
                    vec[a].x = (get(j, 0));
                    vec[a].y = (get(j, 1));
                    vec[a].z = (get(j, 2));
                    vec[a].w = (get(j, 3));
                }
            }
            v.cross(vec[0], vec[1], vec[2]);

            out.set(0, i, pow(-1.0f, i) * v.x / det);
            out.set(1, i, pow(-1.0f, i) * v.y / det);
            out.set(2, i, pow(-1.0f, i) * v.z / det);
            out.set(3, i, pow(-1.0f, i) * v.w / det);
        }

        this->setMatrix(out);
    }

    // Matrix multiplication
    void operator *=(const Matrix4x4& matrix)
    {
        Matrix4x4 out;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                float value = 
                    get(i, 0) * matrix.get(0, j) +
                    get(i, 1) * matrix.get(1, j) +
                    get(i, 2) * matrix.get(2, j) +
                    get(i, 3) * matrix.get(3, j);
                out.set(i, j, value);
            }
        }
        setMatrix(out);
    }

    // Copy contents from another matrix
    void setMatrix(const Matrix4x4& matrix)
    {
        std::memcpy(m_mat, matrix.m_mat, sizeof(float) * 16);
    }

    // Get Z direction vector
    Vector3D getZDirection() const
    {
        return Vector3D(m_mat[8], m_mat[9], m_mat[10]); // [2][0], [2][1], [2][2]
    }

    // Get Y direction vector
    Vector3D getYDirection() const
    {
        return Vector3D(m_mat[4], m_mat[5], m_mat[6]); // [1][0], [1][1], [1][2]
    }

    // Get X direction vector
    Vector3D getXDirection() const
    {
        return Vector3D(m_mat[0], m_mat[1], m_mat[2]); // [0][0], [0][1], [0][2]
    }

    // Get translation vector
    Vector3D getTranslation() const
    {
        return Vector3D(m_mat[12], m_mat[13], m_mat[14]); // [3][0], [3][1], [3][2]
    }

    // Set perspective projection matrix
    void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
    {
        setIdentity();
        float yscale = 1.0f / std::tan(fov / 2.0f);
        float xscale = yscale / aspect;

        m_mat[0] = xscale;   // [0][0]
        m_mat[5] = yscale;   // [1][1]
        m_mat[10] = zfar / (zfar - znear);  // [2][2]
        m_mat[11] = 1.0f;    // [2][3]
        m_mat[14] = (-znear * zfar) / (zfar - znear);  // [3][2]
        m_mat[15] = 0.0f;    // [3][3]
    }

    // Set orthographic projection matrix
    void setOrthoLH(float width, float height, float near_plane, float far_plane)
    {
        setIdentity();
        m_mat[0] = 2.0f / width;  // [0][0]
        m_mat[5] = 2.0f / height; // [1][1]
        m_mat[10] = 1.0f / (far_plane - near_plane);  // [2][2]
        m_mat[14] = -(near_plane / (far_plane - near_plane)); // [3][2]
    }

    // Helper method to get element at row i, column j
    float get(int i, int j) const
    {
        return m_mat[i * 4 + j];
    }

    // Helper method to set element at row i, column j
    void set(int i, int j, float value)
    {
        m_mat[i * 4 + j] = value;
    }

    ~Matrix4x4()
    {
    }

public:
    // Matrix stored in row-major order as a flat array
    // m_mat[i * 4 + j] is equivalent to original m_mat[i][j]
    float m_mat[16] = {};
};