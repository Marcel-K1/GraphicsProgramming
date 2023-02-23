/*********************************************************************************************
* Project: DirectXEngine
* File   : Point
* Date   : 10.02.2023
* Author : Marcel Klein
*
* Data structure for handling the mouse position in the input system
*
*********************************************************************************************/

#pragma once

class Point
{
public:
	Point() :m_x(0), m_y(0)
	{
	}

	Point(int x, int y) :m_x(x), m_y(y)
	{
	}

	Point(const Point& point) :m_x(point.m_x), m_y(point.m_y)
	{
	}

	~Point()
	{
	}

public:
	int m_x = 0;
	int	m_y = 0;
};

