/*********************************************************************************************
* Project: DirectXEngine
* File   : Resource
* Date   : 10.02.2023
* Author : Marcel Klein
*
* Base class for all resources to implement.
*
*********************************************************************************************/

#pragma once
#include "Prerequisites.h"

#include <string>

class Resource
{
public:
	Resource(const wchar_t* full_path);

	virtual ~Resource();

protected:
	std::wstring m_full_path;

};

