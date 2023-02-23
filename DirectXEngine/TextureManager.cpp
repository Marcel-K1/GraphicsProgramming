/*********************************************************************************************
* Project: DirectXEngine
* File   : TextureManager
* Date   : 05.02.2023
* Author : Marcel Klein
*
* Class for managing file import for textures using .jpg-format.
*
*********************************************************************************************/

#include "TextureManager.h"
#include "Texture.h"

TextureManager::TextureManager() : ResourceManager()
{
}


TextureManager::~TextureManager()
{
}

TexturePtr TextureManager::CreateTextureFromFile(const wchar_t* file_path)
{
	return std::static_pointer_cast<Texture>(CreateResourceFromFile(file_path));
}

Resource* TextureManager::CreateResourceFromFileConcrete(const wchar_t* file_path)
{
	Texture* tex = nullptr;
	try
	{
		tex = new Texture(file_path);
	}
	catch (...) {}

	return tex;
}
