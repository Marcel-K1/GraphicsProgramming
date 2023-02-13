#pragma once
#include "Vector3D.h"
#include "Vector2D.h"

class VertexMesh
{
public:
	//With Lighting:
	VertexMesh() :m_position(), m_texcoord(), m_normal()
	{
	}

	VertexMesh(Vector3D position, Vector2D texcoord, Vector3D normal) :
		m_position(position),
		m_texcoord(texcoord),
		m_normal(normal)
	{
	}

	VertexMesh(const VertexMesh& vertex) :
		m_position(vertex.m_position),
		m_texcoord(vertex.m_texcoord),
		m_normal(vertex.m_normal)
	{
	}

	//Without Lighting:
	//VertexMesh(Vector3D position, Vector2D texcoord) :m_position(position), m_texcoord(texcoord)
	//{
	//}

	//VertexMesh(const VertexMesh& vertex) :m_position(vertex.m_position), m_texcoord(vertex.m_texcoord)
	//{
	//}

	~VertexMesh()
	{
	}

public:
	Vector3D m_position;
	Vector2D m_texcoord;
	Vector3D m_normal;
};

