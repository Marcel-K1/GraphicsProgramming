#pragma once
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

