#include "position.h"



CPosition::CPosition()
{
}


CPosition::~CPosition()
{
}

void CPosition::setX(int xx)
{
	m_x = xx;
}

void CPosition::setY(int yy)
{
	m_y = yy;
}

int CPosition::getX()
{
	return m_x;
}

int CPosition::getY()
{
	return m_y;
}
