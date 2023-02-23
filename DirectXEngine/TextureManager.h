/*********************************************************************************************
* Project: DirectXEngine
* File   : TextureManager
* Date   : 05.02.2023
* Author : Marcel Klein
*
* Class for managing file import for textures using .jpg-format.
*
*********************************************************************************************/

#pragma once
#include "Prerequisites.h"
#include "ResourceManager.h"

class TextureManager : public ResourceManager
{
public:
	TextureManager();

	~TextureManager();

	TexturePtr CreateTextureFromFile(const wchar_t* file_path);

protected:
	virtual Resource* CreateResourceFromFileConcrete(const wchar_t* file_path);

};

