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

	//��ά����Ŀռ���䷽ʽ
	m_map = (char **)malloc(sizeof(char*)*sizey);       //arr��������Կ��������飬�����ÿ����Ա����ָ��int���͵�ָ�룬����ÿ��ָ��ָ��Ĵ���һ�У���row��   
	for (int i = 0; i < sizey; i++)            //Ϊÿ������ռ�
	{
		m_map[i] = (char*)malloc(sizeof(char)*sizex);       //ÿһ����col��
	}
}

MAP::~MAP()
{
	//��ά����Ŀռ��ͷŷ�ʽ
	for (int i = 0; i < sizey; i++)            //Ϊÿ������ռ�
	{
		delete[] m_map[i];       //ÿһ����col��
		m_map[i] = NULL;
	}
	delete[] m_map;
	m_map = NULL;
}

char& MAP::Node(int x, int y)
{
	return m_map[x - m_mix][y - m_miy];
}