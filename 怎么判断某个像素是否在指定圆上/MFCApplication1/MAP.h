#pragma once

class MAP
{
public:
	MAP(int mix, int miy, int max, int may);

	~MAP();

	char& Node(int x, int y);

protected:
	int m_mix;
	int m_miy;
	int m_max;
	int m_may;
	int sizex;
	int sizey;
	char **m_map;
};

