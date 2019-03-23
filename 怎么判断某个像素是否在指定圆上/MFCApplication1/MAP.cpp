#include "stdafx.h"
#include "MAP.h"



MAP::MAP(int mix, int miy, int max, int may)
{
	m_mix = mix;
	m_miy = miy;
	m_max = max;
	m_may = may;
	sizex = max - mix + 1;
	sizey = may - miy + 1;

	//二维数组的空间分配方式
	m_map = (char **)malloc(sizeof(char*)*sizey);       //arr在这里可以看出成数组，数组的每个成员都是指向int类型的指针，这样每个指针指向的代表一行，共row行   
	for (int i = 0; i < sizey; i++)            //为每行申请空间
	{
		m_map[i] = (char*)malloc(sizeof(char)*sizex);       //每一行有col列
	}
}

MAP::~MAP()
{
	//二维数组的空间释放方式
	for (int i = 0; i < sizey; i++)            //为每行申请空间
	{
		delete[] m_map[i];       //每一行有col列
		m_map[i] = NULL;
	}
	delete[] m_map;
	m_map = NULL;
}

char& MAP::Node(int x, int y)
{
	return m_map[x - m_mix][y - m_miy];
}