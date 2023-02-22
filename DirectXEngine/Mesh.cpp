#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <locale>
#include <codecvt>
#include <filesystem>

#include "GraphicsEngine.h"
#include "VertexMesh.h"

Mesh::Mesh(const wchar_t* full_path) : Resource(full_path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	auto inputfile = std::filesystem::path(full_path).string();

	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty()) throw std::exception("Mesh not created successfully");

	if (!res) throw std::exception("Mesh not created successfully");

	if (shapes.size() > 1) throw std::exception("Mesh not created successfully");

	//Setting up the vertices and indices for the mesh
	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;

	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;
		list_vertices.reserve(shapes[s].mesh.indices.size());
		list_indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			Vector3D vertices_face[3];
			Vector2D texcoords_face[3];

			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = 0;
				tinyobj::real_t ty = 0;
				if (attribs.texcoords.size())
				{
					tx = attribs.texcoords[index.texcoord_index * 2 + 0];
					ty = attribs.texcoords[index.texcoord_index * 2 + 1];
				}
				vertices_face[v] = Vector3D(vx, vy, vz);
				texcoords_face[v] = Vector2D(tx, ty);
			}

			Vector3D tangent, binormal;

			ComputeTangents(
				vertices_face[0], vertices_face[1], vertices_face[2],
				texcoords_face[0], texcoords_face[1], texcoords_face[2],
				tangent, binormal);


			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = 0;
				tinyobj::real_t ty = 0;

				if (attribs.texcoords.size())
				{
					tx = attribs.texcoords[index.texcoord_index * 2 + 0];
					ty = attribs.texcoords[index.texcoord_index * 2 + 1];
				}

				tinyobj::real_t nx = 0;
				tinyobj::real_t ny = 0;
				tinyobj::real_t nz = 0;

				if (attribs.normals.size())
				{
					nx = attribs.normals[index.normal_index * 3 + 0];
					ny = attribs.normals[index.normal_index * 3 + 1];
					nz = attribs.normals[index.normal_index * 3 + 2];
				}

				Vector3D v_tangent, v_binormal;
				v_binormal = Vector3D::Cross(Vector3D(nx, ny, nz), tangent);
				v_tangent = Vector3D::Cross(v_binormal, Vector3D(nx, ny, nz));

				//Populating the VertexMesh with the computed data for all parts of the vertex
				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty), Vector3D(nx, ny, nz), v_tangent, v_binormal);

				list_vertices.push_back(vertex);
				list_indices.push_back((unsigned int)index_offset + v);
			}

			index_offset += num_face_verts;
		}
	}

	//Setting up the right size for the different buffers, depending on which mesh is to be loaded, by using the VertexMeshLayoutShader.
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::Get()->GetVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);
	m_vertex_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateVertexBuffer(&list_vertices[0], sizeof(VertexMesh),
		(UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader);
	m_index_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateIndexBuffer(&list_indices[0], (UINT)list_indices.size());

}

Mesh::~Mesh()
{
}

const VertexBufferPtr& Mesh::GetVertexBuffer()
{
	return m_vertex_buffer;
}

const IndexBufferPtr& Mesh::GetIndexBuffer()
{
	return m_index_buffer;
}

void Mesh::ComputeTangents(const Vector3D& v0,
	const Vector3D& v1,
	const Vector3D& v2,
	const Vector2D& t0,
	const Vector2D& t1,
	const Vector2D& t2,
	Vector3D& tangent, Vector3D& binormal)
{
	Vector3D deltaPos1 = v1 - v0;
	Vector3D deltaPos2 = v2 - v0;

	Vector2D deltaUV1 = t1 - t0;
	Vector2D deltaUV2 = t2 - t0;


	float r = 1.0f / (deltaUV1.m_x * deltaUV2.m_y - deltaUV1.m_y * deltaUV2.m_x);
	tangent = (deltaPos1 * deltaUV2.m_y - deltaPos2 * deltaUV1.m_y);
	tangent = Vector3D::Normalize(tangent);
	binormal = (deltaPos2 * deltaUV1.m_x - deltaPos1 * deltaUV2.m_x);
	binormal = Vector3D::Normalize(binormal);
}
