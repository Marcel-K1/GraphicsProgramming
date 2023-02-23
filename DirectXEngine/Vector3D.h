/*********************************************************************************************
* Project: DirectXEngine
* File   : Vector3D
* Date   : 05.01.2023
* Author : Marcel Klein
*
* Data structure to be able to set up custom mathfunctions for vector calculations.
*
* Reference to: https://stackoverflow.com/
*********************************************************************************************/

#pragma once

class Vector3D
{
public:
	Vector3D() :m_x(0), m_y(0), m_z(0)
	{
	}
	Vector3D(float x, float y, float z) :m_x(x), m_y(y), m_z(z)
	{
	}
	Vector3D(const Vector3D& vector) :m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z)
	{
	}

	static Vector3D Lerp(const Vector3D& start, const Vector3D& end, float delta)
	{
		Vector3D v;
		v.m_x = start.m_x * (1.0f - delta) + end.m_x * (delta);
		v.m_y = start.m_y * (1.0f - delta) + end.m_y * (delta);
		v.m_z = start.m_z * (1.0f - delta) + end.m_z * (delta);
		return v;
	}

	Vector3D operator *(float num) const
	{
		return Vector3D(m_x * num, m_y * num, m_z * num);
	}

	Vector3D operator +(const Vector3D& vec) const
	{
		return Vector3D(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
	}

	Vector3D operator -(const Vector3D& vec) const
	{
		return Vector3D(m_x - vec.m_x, m_y - vec.m_y, m_z - vec.m_z);
	}

	static Vector3D Normalize(const Vector3D& vec)
	{
		Vector3D res;
		float len = (float)sqrt((vec.m_x * vec.m_x) + (vec.m_y * vec.m_y) + (vec.m_z * vec.m_z));
		if (!len)
			return Vector3D();

		res.m_x = vec.m_x / len;
		res.m_y = vec.m_y / len;
		res.m_z = vec.m_z / len;

		return res;
	}

	static Vector3D Cross(const Vector3D& v1, const Vector3D& v2)
	{
		Vector3D res;
		res.m_x = (v1.m_y * v2.m_z) - (v1.m_z * v2.m_y);
		res.m_y = (v1.m_z * v2.m_x) - (v1.m_x * v2.m_z);
		res.m_z = (v1.m_x * v2.m_y) - (v1.m_y * v2.m_x);
		return res;
	}

	~Vector3D()
	{
	}

public:
	float m_x, m_y, m_z;
};

