/*********************************************************************************************
* Project: DirectXEngine
* File   : ResourceManager
* Date   : 11.02.2023
* Author : Marcel Klein
*
* Handling the resource management by using the component design pattern by dividing the base
* class Resource in more specialized classes like Texture and Mesh.
*
*********************************************************************************************/

#pragma once
#include "Prerequisites.h"
#include "Resource.h"

#include <unordered_map>
#include <string>

class ResourceManager
{
public:
	ResourceManager();

	virtual ~ResourceManager();

	ResourcePtr CreateResourceFromFile(const wchar_t* file_path);

protected:
	virtual Resource* CreateResourceFromFileConcrete(const wchar_t* file_path) = 0;

private:
	std::unordered_map<std::wstring, ResourcePtr> m_map_resources;

};


