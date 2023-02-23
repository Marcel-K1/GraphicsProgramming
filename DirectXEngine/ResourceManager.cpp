/*********************************************************************************************
* Project: DirectXEngine
* File   : ResourceManager
* Date   : 11.02.2023
* Author : Marcel Klein
*
* Handling the resource management by using the component design pattern by dividing the base
* class Resource in more specialized classes like Texture and Mesh.
*
* * Reference to: https://www.youtube.com/watch?v=luuyjjOxnUI&list=PL7Ej6SUky135IAAR3PFCFyiVwanauRqj3
* https://www.youtube.com/watch?v=hRL56gXqj-4&list=PLU2nPsAdxKWQYxkmQ3TdbLsyc1l2j25XM
* https://www.youtube.com/watch?v=gQIG77PfLgo&list=PLcacUGyBsOIBlGyQQWzp6D1Xn6ZENx9Y2
*********************************************************************************************/

#include "ResourceManager.h"

#if __cplusplus <= 201402L 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#if __cplusplus >= 201703L
#include <filesystem>
#endif

#if __cplusplus >= 202203L
#include <filesystem>
#endif

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

ResourcePtr ResourceManager::CreateResourceFromFile(const wchar_t* file_path)
{

#if (_MSC_VER >= 1900 && _MSC_VER <= 1916)  || ( _MSC_VER >= 1920 && __cplusplus <= 201402L) 
	std::wstring full_path = std::experimental::filesystem::absolute(file_path);
#endif

#if _MSC_VER >= 1920 && __cplusplus > 201402L 
	std::wstring full_path = std::filesystem::absolute(file_path);
#endif

	auto it = m_map_resources.find(full_path);

	if (it != m_map_resources.end())
		return it->second;

	Resource* raw_res = this->CreateResourceFromFileConcrete(full_path.c_str());

	if (raw_res)
	{
		ResourcePtr res(raw_res);
		m_map_resources[full_path] = res;
		return res;
	}

	return nullptr;
}
