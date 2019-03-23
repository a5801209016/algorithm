#include "stdafx.h"
#include "AXES.h"



AXES::AXES()
{
	min = DOT(0, 0);
	max = DOT(0, 0);
	mid = 0;
	length = 0.0;
	k = 0.0;
}

AXES::AXES(DOT l, DOT r, int md, int b)
{
	min = l;
	max = r;
	mid = md;
	mbe = b;
	length = pow(pow(max.X() - min.X(), 2) + pow(max.Y() - min.Y(), 2), 0.5);
	k = atan2((max.Y() - min.Y()), (max.X() - min.X()));
}

void AXES::SetValue(DOT l, DOT r, int md, int b)
{
	min = l;
	max = r;
	mid = md;
	mbe = b;
	length = pow(pow(max.X() - min.X(), 2) + pow(max.Y() - min.Y(), 2), 0.5);
	k = atan2((max.Y() - min.Y()), (max.X() - min.X()));
}

void AXES::OnPaint(CClientDC* dc)
{
	POINT p1;
	p1.x = GetXY(min).X();
	p1.y = GetXY(min).Y();

	POINT p2;
	p2.x = GetXY(max).X();
	p2.y = GetXY(max).Y();

	//坐标线
	CPen* newpen = new CPen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* oldpen = dc->GetCurrentPen();
	dc->SelectObject(newpen);
	dc->MoveTo(p1);
	dc->LineTo(p2);

	//坐标字
	CFont font;
	font.CreateFont(13,                                    //   字体的高度   
		0,                                          //   字体的宽度  
		0,                                          //  nEscapement 
		0,                                          //  nOrientation   
		FW_NORMAL,                                  //   nWeight   
		FALSE,                                      //   bItalic   
		FALSE,                                      //   bUnderline   
		0,                                                   //   cStrikeOut   
		ANSI_CHARSET,                             //   nCharSet   
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision   
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision   
		DEFAULT_QUALITY,                       //   nQuality   
		DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily     
		_T("宋体"));
	dc->SelectObject(&font);
	dc->SetBkMode(TRANSPARENT);
	dc->SetTextColor(RGB(255, 0, 0));
	for (int dis = 0; dis <= length; dis += mid)
	{
		//字
		char buff[128] = { 0 };
		sprintf(buff, "%d", mbe + dis);
		DOT point = DOT(min.X() + dis*cos(k), min.Y() + dis*sin(k));
		DOT windp = GetXY(point);
		//点
		RECT rt;
		rt.left = windp.X() - 2;
		rt.right = windp.X() + 2;
		rt.top = windp.Y() - 2;
		rt.bottom = windp.Y() + 2;
		CBrush* oldbrush = dc->GetCurrentBrush();
		CBrush newbrush(RGB(255, 0, 0));
		dc->SelectObject(&newbrush);
		dc->Ellipse(&rt);
		dc->SelectObject(&oldbrush);
		dc->TextOut(windp.X(), windp.Y(), CString(buff));
	}



	dc->SelectObject(oldpen);
	delete newpen;
	newpen = NULL;
}

DOT AXES::GetXY(DOT d2)
{
	DOT d(d2.X() + 500, 300 - d2.Y());
	return d;
}
