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
	//����λͼ��Դ
	bitmap.LoadBitmap(ID);
	//��������ȡ�豸������
	CBrush brush(&bitmap);
	//����λͼ��ˢ����������
	dc->FillRect(CRect(locate, si), &brush);
}

void Unit::ShowImage(CImage cImg, CDC* dc, POINT locate, SIZE si, UINT rgb)
{
	
}
