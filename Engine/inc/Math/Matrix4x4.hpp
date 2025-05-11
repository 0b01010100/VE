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

    // Set translation component (column-major for OpenGL)
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

    // Set rotation around X axis (right-handed)
    void setRotationX(float angle)
    {
        float c = std::cos(angle);
        float s = std::sin(angle);
        m_mat[5] = c;   // [1][1]
        m_mat[6] = s;   // [1][2]
        m_mat[9] = -s;  // [2][1]
        m_mat[10] = c;  // [2][2]
    }

    // Set rotation around Y axis (right-handed)
    void setRotationY(float angle)
    {
        float c = std::cos(angle);
        float s = std::sin(angle);
        m_mat[0] = c;   // [0][0]
        m_mat[2] = -s;  // [0][2]
        m_mat[8] = s;   // [2][0]
        m_mat[10] = c;  // [2][2]
    }

    // Set rotation around Z axis (right-handed)
    void setRotationZ(float angle)
    {
        float c = std::cos(angle);
        float s = std::sin(angle);
        m_mat[0] = c;   // [0][0]
        m_mat[1] = s;   // [0][1]
        m_mat[4] = -s;  // [1][0]
        m_mat[5] = c;   // [1][1]
    }

    // Get determinant of the matrix
    float getDeterminant() const
    {
        // For column-major 4x4 matrix
        return
            m_mat[0] * (
                m_mat[5] * (m_mat[10] * m_mat[15] - m_mat[11] * m_mat[14]) -
                m_mat[9] * (m_mat[6] * m_mat[15] - m_mat[7] * m_mat[14]) +
                m_mat[13] * (m_mat[6] * m_mat[11] - m_mat[7] * m_mat[10])
            ) -
            m_mat[4] * (
                m_mat[1] * (m_mat[10] * m_mat[15] - m_mat[11] * m_mat[14]) -
                m_mat[9] * (m_mat[2] * m_mat[15] - m_mat[3] * m_mat[14]) +
                m_mat[13] * (m_mat[2] * m_mat[11] - m_mat[3] * m_mat[10])
            ) +
            m_mat[8] * (
                m_mat[1] * (m_mat[6] * m_mat[15] - m_mat[7] * m_mat[14]) -
                m_mat[5] * (m_mat[2] * m_mat[15] - m_mat[3] * m_mat[14]) +
                m_mat[13] * (m_mat[2] * m_mat[7] - m_mat[3] * m_mat[6])
            ) -
            m_mat[12] * (
                m_mat[1] * (m_mat[6] * m_mat[11] - m_mat[7] * m_mat[10]) -
                m_mat[5] * (m_mat[2] * m_mat[11] - m_mat[3] * m_mat[10]) +
                m_mat[9] * (m_mat[2] * m_mat[7] - m_mat[3] * m_mat[6])
            );
    }

    // Inverse the matrix
    bool inverse()
    {
        float det = getDeterminant();
        if (std::abs(det) < 1e-6f) return false; // Matrix not invertible
        
        Matrix4x4 inv;
        
        inv.m_mat[0] = m_mat[5] * (m_mat[10] * m_mat[15] - m_mat[11] * m_mat[14]) -
                       m_mat[9] * (m_mat[6] * m_mat[15] - m_mat[7] * m_mat[14]) +
                       m_mat[13] * (m_mat[6] * m_mat[11] - m_mat[7] * m_mat[10]);
                       
        inv.m_mat[4] = -(m_mat[4] * (m_mat[10] * m_mat[15] - m_mat[11] * m_mat[14]) -
                         m_mat[8] * (m_mat[6] * m_mat[15] - m_mat[7] * m_mat[14]) +
                         m_mat[12] * (m_mat[6] * m_mat[11] - m_mat[7] * m_mat[10]));
                      
        inv.m_mat[8] = m_mat[4] * (m_mat[9] * m_mat[15] - m_mat[11] * m_mat[13]) -
                       m_mat[8] * (m_mat[5] * m_mat[15] - m_mat[7] * m_mat[13]) +
                       m_mat[12] * (m_mat[5] * m_mat[11] - m_mat[7] * m_mat[9]);
                     
        inv.m_mat[12] = -(m_mat[4] * (m_mat[9] * m_mat[14] - m_mat[10] * m_mat[13]) -
                          m_mat[8] * (m_mat[5] * m_mat[14] - m_mat[6] * m_mat[13]) +
                          m_mat[12] * (m_mat[5] * m_mat[10] - m_mat[6] * m_mat[9]));
                      
        inv.m_mat[1] = -(m_mat[1] * (m_mat[10] * m_mat[15] - m_mat[11] * m_mat[14]) -
                         m_mat[9] * (m_mat[2] * m_mat[15] - m_mat[3] * m_mat[14]) +
                         m_mat[13] * (m_mat[2] * m_mat[11] - m_mat[3] * m_mat[10]));
                      
        inv.m_mat[5] = m_mat[0] * (m_mat[10] * m_mat[15] - m_mat[11] * m_mat[14]) -
                       m_mat[8] * (m_mat[2] * m_mat[15] - m_mat[3] * m_mat[14]) +
                       m_mat[12] * (m_mat[2] * m_mat[11] - m_mat[3] * m_mat[10]);
                     
        inv.m_mat[9] = -(m_mat[0] * (m_mat[9] * m_mat[15] - m_mat[11] * m_mat[13]) -
                         m_mat[8] * (m_mat[1] * m_mat[15] - m_mat[3] * m_mat[13]) +
                         m_mat[12] * (m_mat[1] * m_mat[11] - m_mat[3] * m_mat[9]));
                      
        inv.m_mat[13] = m_mat[0] * (m_mat[9] * m_mat[14] - m_mat[10] * m_mat[13]) -
                        m_mat[8] * (m_mat[1] * m_mat[14] - m_mat[2] * m_mat[13]) +
                        m_mat[12] * (m_mat[1] * m_mat[10] - m_mat[2] * m_mat[9]);
                      
        inv.m_mat[2] = m_mat[1] * (m_mat[6] * m_mat[15] - m_mat[7] * m_mat[14]) -
                       m_mat[5] * (m_mat[2] * m_mat[15] - m_mat[3] * m_mat[14]) +
                       m_mat[13] * (m_mat[2] * m_mat[7] - m_mat[3] * m_mat[6]);
                     
        inv.m_mat[6] = -(m_mat[0] * (m_mat[6] * m_mat[15] - m_mat[7] * m_mat[14]) -
                         m_mat[4] * (m_mat[2] * m_mat[15] - m_mat[3] * m_mat[14]) +
                         m_mat[12] * (m_mat[2] * m_mat[7] - m_mat[3] * m_mat[6]));
                      
        inv.m_mat[10] = m_mat[0] * (m_mat[5] * m_mat[15] - m_mat[7] * m_mat[13]) -
                        m_mat[4] * (m_mat[1] * m_mat[15] - m_mat[3] * m_mat[13]) +
                        m_mat[12] * (m_mat[1] * m_mat[7] - m_mat[3] * m_mat[5]);
                      
        inv.m_mat[14] = -(m_mat[0] * (m_mat[5] * m_mat[14] - m_mat[6] * m_mat[13]) -
                          m_mat[4] * (m_mat[1] * m_mat[14] - m_mat[2] * m_mat[13]) +
                          m_mat[12] * (m_mat[1] * m_mat[6] - m_mat[2] * m_mat[5]));
                       
        inv.m_mat[3] = -(m_mat[1] * (m_mat[6] * m_mat[11] - m_mat[7] * m_mat[10]) -
                         m_mat[5] * (m_mat[2] * m_mat[11] - m_mat[3] * m_mat[10]) +
                         m_mat[9] * (m_mat[2] * m_mat[7] - m_mat[3] * m_mat[6]));
                      
        inv.m_mat[7] = m_mat[0] * (m_mat[6] * m_mat[11] - m_mat[7] * m_mat[10]) -
                       m_mat[4] * (m_mat[2] * m_mat[11] - m_mat[3] * m_mat[10]) +
                       m_mat[8] * (m_mat[2] * m_mat[7] - m_mat[3] * m_mat[6]);
                     
        inv.m_mat[11] = -(m_mat[0] * (m_mat[5] * m_mat[11] - m_mat[7] * m_mat[9]) -
                          m_mat[4] * (m_mat[1] * m_mat[11] - m_mat[3] * m_mat[9]) +
                          m_mat[8] * (m_mat[1] * m_mat[7] - m_mat[3] * m_mat[5]));
                       
        inv.m_mat[15] = m_mat[0] * (m_mat[5] * m_mat[10] - m_mat[6] * m_mat[9]) -
                        m_mat[4] * (m_mat[1] * m_mat[10] - m_mat[2] * m_mat[9]) +
                        m_mat[8] * (m_mat[1] * m_mat[6] - m_mat[2] * m_mat[5]);
        
        // Multiply by reciprocal of determinant
        float invDet = 1.0f / det;
        for (int i = 0; i < 16; i++) {
            inv.m_mat[i] *= invDet;
        }
        
        setMatrix(inv);
        return true;
    }

    // Matrix multiplication (column-major for OpenGL)
    Matrix4x4 operator *(const Matrix4x4& matrix) const
    {
        Matrix4x4 out;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                float value = 0.0f;
                for (int k = 0; k < 4; k++) {
                    value += m_mat[i + k*4] * matrix.m_mat[k + j*4];
                }
                out.m_mat[i + j*4] = value;
            }
        }
        return out;
    }

    // In-place multiplication
    void operator *=(const Matrix4x4& matrix)
    {
        *this = *this * matrix;
    }

    // Copy contents from another matrix
    void setMatrix(const Matrix4x4& matrix)
    {
        std::memcpy(m_mat, matrix.m_mat, sizeof(float) * 16);
    }

    // Get Z direction vector (column-major for OpenGL)
    Vector3D getZDirection() const
    {
        return Vector3D(m_mat[2], m_mat[6], m_mat[10]); // [0][2], [1][2], [2][2]
    }

    // Get Y direction vector (column-major for OpenGL)
    Vector3D getYDirection() const
    {
        return Vector3D(m_mat[1], m_mat[5], m_mat[9]); // [0][1], [1][1], [2][1]
    }

    // Get X direction vector (column-major for OpenGL)
    Vector3D getXDirection() const
    {
        return Vector3D(m_mat[0], m_mat[4], m_mat[8]); // [0][0], [1][0], [2][0]
    }

    // Get translation vector (column-major for OpenGL)
    Vector3D getTranslation() const
    {
        return Vector3D(m_mat[12], m_mat[13], m_mat[14]); // [3][0], [3][1], [3][2]
    }

    // Set perspective projection matrix (right-handed for OpenGL)
    void setPerspective(float fov, float aspect, float znear, float zfar)
    {
        setIdentity();
        float f = 1.0f / std::tan(fov / 2.0f);
        
        m_mat[0] = f / aspect;  // [0][0]
        m_mat[5] = f;           // [1][1]
        m_mat[10] = (zfar + znear) / (znear - zfar);  // [2][2]
        m_mat[11] = -1.0f;      // [2][3]
        m_mat[14] = (2.0f * zfar * znear) / (znear - zfar);  // [3][2]
        m_mat[15] = 0.0f;       // [3][3]
    }

    // Set orthographic projection matrix (right-handed for OpenGL)
    void setOrtho(float left, float right, float bottom, float top, float near_plane, float far_plane)
    {
        setIdentity();
        m_mat[0] = 2.0f / (right - left);
        m_mat[5] = 2.0f / (top - bottom);
        m_mat[10] = -2.0f / (far_plane - near_plane);
        m_mat[12] = -(right + left) / (right - left);
        m_mat[13] = -(top + bottom) / (top - bottom);
        m_mat[14] = -(far_plane + near_plane) / (far_plane - near_plane);
    }

    // Set look-at view matrix (right-handed for OpenGL)
    void setLookAt(const Vector3D& eye, const Vector3D& target, const Vector3D& up)
    {
        Vector3D zaxis = (eye - target).normalize();
        Vector3D xaxis = up.cross(zaxis).normalize();
        Vector3D yaxis = zaxis.cross(xaxis);

        m_mat[0] = xaxis.x;
        m_mat[1] = yaxis.x;
        m_mat[2] = zaxis.x;
        m_mat[3] = 0.0f;

        m_mat[4] = xaxis.y;
        m_mat[5] = yaxis.y;
        m_mat[6] = zaxis.y;
        m_mat[7] = 0.0f;

        m_mat[8] = xaxis.z;
        m_mat[9] = yaxis.z;
        m_mat[10] = zaxis.z;
        m_mat[11] = 0.0f;

        m_mat[12] = -xaxis.dot(eye);
        m_mat[13] = -yaxis.dot(eye);
        m_mat[14] = -zaxis.dot(eye);
        m_mat[15] = 1.0f;
    }

    // Helper methods to create transformation matrices
    static Matrix4x4 createTranslation(const Vector3D& translation)
    {
        Matrix4x4 result;
        result.m_mat[12] = translation.x;
        result.m_mat[13] = translation.y;
        result.m_mat[14] = translation.z;
        return result;
    }

    static Matrix4x4 createScale(const Vector3D& scale)
    {
        Matrix4x4 result;
        result.m_mat[0] = scale.x;
        result.m_mat[5] = scale.y;
        result.m_mat[10] = scale.z;
        return result;
    }

    static Matrix4x4 createRotationX(float angle)
    {
        Matrix4x4 result;
        float c = std::cos(angle);
        float s = std::sin(angle);
        result.m_mat[5] = c;
        result.m_mat[6] = s;
        result.m_mat[9] = -s;
        result.m_mat[10] = c;
        return result;
    }

    static Matrix4x4 createRotationY(float angle)
    {
        Matrix4x4 result;
        float c = std::cos(angle);
        float s = std::sin(angle);
        result.m_mat[0] = c;
        result.m_mat[2] = -s;
        result.m_mat[8] = s;
        result.m_mat[10] = c;
        return result;
    }

    static Matrix4x4 createRotationZ(float angle)
    {
        Matrix4x4 result;
        float c = std::cos(angle);
        float s = std::sin(angle);
        result.m_mat[0] = c;
        result.m_mat[1] = s;
        result.m_mat[4] = -s;
        result.m_mat[5] = c;
        return result;
    }

    // Helper method to get element at row i, column j (column-major order)
    float get(int row, int col) const
    {
        // For column-major: element[row + col*4]
        return m_mat[row + col*4];
    }

    // Helper method to set element at row i, column j (column-major order)
    void set(int row, int col, float value)
    {
        // For column-major: element[row + col*4]
        m_mat[row + col*4] = value;
    }

public:
    // Matrix stored in column-major order as a flat array for OpenGL
    // m_mat[row + col*4] is equivalent to original m_mat[row][col]
    float m_mat[16] = {};
};