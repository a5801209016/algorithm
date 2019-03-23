#include "stdafx.h"
#include "DOT.h"



DOT::DOT()
{
	m_x = 0;
	m_y = 0;
}

DOT::DOT(int x, int y)
{
	m_x = x;
	m_y = y;
}

DOT::~DOT()
{

}

int DOT::X()
{
	return m_x;
}

int DOT::Y()
{
	return m_y;
}

DOT& DOT::operator=(DOT &a)
{
	m_x = a.X();
	m_y = a.Y();
	return *this;
}

DOT& DOT::operator+(const DOT &a)
{
	DOT r(m_x + a.m_x, m_y + a.m_y);
	return r;
}

void DOT::operator()(const int &x, const int& y)
{
	m_x = x;
	m_y = y;
}

bool DOT::operator==(DOT &a)
{
	if (m_x == a.X() && m_y == a.Y())
	{
		return true;
	}
	else
	{
		return false;
	}
}
