#pragma once
#include "DOT.h"
//����
class AXES
{
public:
	AXES();
	AXES(DOT l, DOT r, int md, int b);
	void SetValue(DOT l, DOT r, int md, int b);
public:
	void OnPaint( CClientDC* dc);
protected:
	DOT min;//һ�����������С����
	DOT max;//һ�����������󲿷�
	int mid;//һ��������ļ����С
	int mbe;//�����min��X����Y��
	//(x-min.X())/(max.X()-min.X()) = (y-min.Y())/(max.Y()-min.Y())

	double length;
	double k;//�Ƕ�
protected:
	//���е�����ת��Ϊ��������
	DOT GetXY(DOT d2);
};

