#pragma once

class DOT//µã
{
public:
	DOT();
	DOT(int x, int y);

	~DOT();

	int X();

	int Y();

	DOT& operator = (DOT &a);

	DOT& operator + (const DOT &a);

	void operator () (const int &x, const int& y);

	bool operator == ( DOT &a);

protected:
	int m_x;
	int m_y;
};

