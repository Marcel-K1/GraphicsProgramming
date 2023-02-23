/*********************************************************************************************
* Project: DirectXEngine
* File   : MeshManager
* Date   : 05.02.2023
* Author : Marcel Klein
*
* Class for managing file import for prebuild meshes.
*
*********************************************************************************************/

#include "MeshManager.h"
#include "Mesh.h"

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
}

MeshPtr MeshManager::CreateMeshFromFile(const wchar_t* file_path)
{
	return std::static_pointer_cast<Mesh>(CreateResourceFromFile(file_path));
}

Resource* MeshManager::CreateResourceFromFileConcrete(const wchar_t* file_path)
{
	Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(file_path);
	}
	catch (...) {}

	return mesh;
}
