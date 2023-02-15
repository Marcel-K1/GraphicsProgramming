#pragma once
#include "Resource.h"
#include "VertexBuffer.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "IndexBuffer.h"

class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_path);

	~Mesh();

	const VertexBufferPtr& GetVertexBuffer();

	const IndexBufferPtr& GetIndexBuffer();

private:
	VertexBufferPtr m_vertex_buffer;

	IndexBufferPtr m_index_buffer;

private:
	void ComputeTangents(
		const Vector3D& v0, const Vector3D& v1, const Vector3D& v2,
		const Vector2D& t0, const Vector2D& t1, const Vector2D& t2,
		Vector3D& tangent, Vector3D& binormal);

private:
	friend class DeviceContext;
};

