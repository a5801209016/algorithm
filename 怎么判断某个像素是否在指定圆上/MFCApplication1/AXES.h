#pragma once
#include "DOT.h"
//坐标
class AXES
{
public:
	AXES();
	AXES(DOT l, DOT r, int md, int b);
	void SetValue(DOT l, DOT r, int md, int b);
public:
	void OnPaint( CClientDC* dc);
protected:
	DOT min;//一根坐标轴的最小部分
	DOT max;//一根坐标轴的最大部分
	int mid;//一根坐标轴的间隔大小
	int mbe;//起点是min的X还是Y轴
	//(x-min.X())/(max.X()-min.X()) = (y-min.Y())/(max.Y()-min.Y())

	double length;
	double k;//角度
protected:
	//把中点坐标转换为窗口坐标
	DOT GetXY(DOT d2);
};

