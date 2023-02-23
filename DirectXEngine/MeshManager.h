/*********************************************************************************************
* Project: DirectXEngine
* File   : MeshManager
* Date   : 05.02.2023
* Author : Marcel Klein
*
* Class for managing file import for prebuild meshes.
*
*********************************************************************************************/

#pragma once
#include "Prerequisites.h"
#include "ResourceManager.h"

class MeshManager : public ResourceManager
{
public:
	MeshManager();

	~MeshManager();

	MeshPtr CreateMeshFromFile(const wchar_t* file_path);

protected:
	virtual Resource* CreateResourceFromFileConcrete(const wchar_t* file_path);

};

