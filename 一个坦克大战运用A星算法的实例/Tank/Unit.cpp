#include "stdafx.h"
#include "Unit.h"


Unit::Unit()
{
}


Unit::~Unit()
{
}

void Unit::OnPaint(CDC* dc)
{
	return;
}

void Unit::ShowBitmap(UINT ID, CDC* dc, POINT locate, SIZE si)
{
	CBitmap bitmap;
	//加载位图资源
	bitmap.LoadBitmap(ID);
	//创建并获取设备描述表
	CBrush brush(&bitmap);
	//利用位图画刷填充矩形区域
	dc->FillRect(CRect(locate, si), &brush);
}

void Unit::ShowImage(CImage cImg, CDC* dc, POINT locate, SIZE si, UINT rgb)
{
	
}
