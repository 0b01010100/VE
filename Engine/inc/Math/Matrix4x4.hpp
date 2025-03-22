#pragma once
#include <memory>
#include <Math/Vector3D.hpp>
#include <Math/Vector4D.hpp>
class Matrix4x4
{
public:
	Matrix4x4()
	{
		m_mat[0][0] = 1;
		m_mat[1] [1] = 1;
		m_mat[2][2] = 1;
		m_mat[3][3] = 1;
	}

	void setIdentity()
	{
        *this = Matrix4x4();
		m_mat[0][0] = 1;
		m_mat[1][1] = 1;
		m_mat[2][2] = 1;
		m_mat[3][3] = 1;
	}

	void setTranslation(const Vector3D& translation)
	{
		m_mat[3][0] = translation.x;
		m_mat[3][1] = translation.y;
		m_mat[3][2] = translation.z;
	}

	void setScale(const Vector3D& scale)
	{
		m_mat[0][0] = scale.x;
		m_mat[1][1] = scale.y;
		m_mat[2][2] = scale.z;
	}

	void setRotationX(float x)
	{
		m_mat[1][1] = cos(x);
		m_mat[1][2] = sin(x);
		m_mat[2][1] = -sin(x);
		m_mat[2][2] = cos(x);
	}

	void setRotationY(float y)
	{
		m_mat[0][0] = cos(y);
		m_mat[0][2] = -sin(y);
		m_mat[2][0] = sin(y);
		m_mat[2][2] = cos(y);
	}

	void setRotationZ(float z)
	{
		m_mat[0][0] = cos(z);
		m_mat[0][1] = sin(z);
		m_mat[1][0] = -sin(z);
		m_mat[1][1] = cos(z);
	}

	float getDeterminant()
	{
		Vector4D minor, v1, v2, v3;
		float det;

		v1 = Vector4D(this->m_mat[0][0], this->m_mat[1][0], this->m_mat[2][0], this->m_mat[3][0]);
		v2 = Vector4D(this->m_mat[0][1], this->m_mat[1][1], this->m_mat[2][1], this->m_mat[3][1]);
		v3 = Vector4D(this->m_mat[0][2], this->m_mat[1][2], this->m_mat[2][2], this->m_mat[3][2]);


		minor.cross(v1, v2, v3);
		det = -(this->m_mat[0][3] * minor.x + this->m_mat[1][3] * minor.y + this->m_mat[2][3] * minor.z +
			this->m_mat[3][3] * minor.w);
		return det;
	}

	void inverse()
	{
		int a, i, j;
		Matrix4x4 out;
		Vector4D v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;//If zero of less than Zero this matrix is not invertable
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].x = (this->m_mat[j][0]);
					vec[a].y = (this->m_mat[j][1]);
					vec[a].z = (this->m_mat[j][2]);
					vec[a].w = (this->m_mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.m_mat[0][i] = pow(-1.0f, i) * v.x / det;
			out.m_mat[1][i] = pow(-1.0f, i) * v.y / det;
			out.m_mat[2][i] = pow(-1.0f, i) * v.z / det;
			out.m_mat[3][i] = pow(-1.0f, i) * v.w / det;
		}

		this->setMatrix(out);
	}

	void operator*=(const Matrix4x4& matrix)
	{
		Matrix4x4 out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.m_mat[i][j] =
					m_mat[i][0] * matrix.m_mat[0][j] +
					m_mat[i][1] * matrix.m_mat[1][j] +
					m_mat[i][2] * matrix.m_mat[2][j] +
					m_mat[i][3] * matrix.m_mat[3][j];
			}
		}
		setMatrix(out);
	}
	// copy the contents of a 4x4 matrix matrix into this 4x4 matrix 
	void setMatrix(const Matrix4x4& matrix)
	{
		::memcpy(m_mat, matrix.m_mat, sizeof(float) * 16);
	}
	//Returns the Z-axis that is available in the third row of the matrix
	//Useful when we want to get the relative Z of an object 
	Vector3D getZDirection()
	{
		return Vector3D(m_mat[2][0], m_mat[2][1], m_mat[2][2]);
	}
	//Useful when we want to get the relative Y of an object 
	Vector3D getYDirection() 
	{
		return Vector3D(m_mat[1][0], m_mat[1][1], m_mat[1][2]);
	}
	//Return the x axis that is available in the first row of the matrix
	//Useful when we want to get the relative X of an object 
	Vector3D getXDirection()
	{
		return Vector3D(m_mat[0][0], m_mat[0][1], m_mat[0][2]);
	}
	//Returns the last row where the tranlation of the matrix ios placed
	Vector3D getTranslation()
	{
		return Vector3D(m_mat[3][0], m_mat[3][1], m_mat[3][2]);
	}
	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
	{
		float yscale = 1.0f / tan(fov / 2.0f);
		float xscale = yscale / aspect;

		m_mat[0][0] = xscale;
		m_mat[1][1] = yscale;
		m_mat[2][2]= zfar / (zfar - znear);
		m_mat[2][3] = 1.0f;
		m_mat[3][2] = (-znear * zfar) / (zfar - znear);
		m_mat[3][3] = 0.0f;
		//m_mat[0][0] = aspect * (1 / tan(fov / 2));
		//m_mat[1][1] = 1 / tan(fov / 2);
		//m_mat[2][2] = zfar / (zfar - znear);
		//m_mat[2][3] = (-zfar * znear) / (zfar - znear);
		//m_mat[3][2] = 1.0f;
	}

	void setOrthoLH(float width, float height, float near_plane, float far_plane)
	{
		setIdentity();
		m_mat[0][0] = 2.0f / width;
		m_mat[1][1] = 2.0f / height;
		m_mat[2][2] = 1.0f / (far_plane - near_plane);
		m_mat[3][2] = -(near_plane / (far_plane - near_plane));
	}

	~Matrix4x4()
	{
	}

public:
	float m_mat[4][4] = {};
};