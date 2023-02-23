/*********************************************************************************************
* Project: DirectXEngine
* File   : Resource
* Date   : 10.02.2023
* Author : Marcel Klein
*
* Base class for all resources to implement.
* 
*********************************************************************************************/

#include "Resource.h"

Resource::Resource(const wchar_t* full_path) : m_full_path(full_path)
{
}

Resource::~Resource()
{
}
