#include "stdafx.h"
#include "SelfTank.h"


SelfTank::SelfTank()
{
	InsertImage("left",_T("res/tank_left.png"));
	InsertImage("right",_T("res/tank_right.png"));
	InsertImage("top",_T("res/tank_top.png"));
	InsertImage("bottom",_T("res/tank_bottom.png"));
	SetTankSize(SIZE{ 26, 26 });
	this_current_image = new CImage;
}

SelfTank::~SelfTank()
{
}

void SelfTank::SetDirect(std::string direct)
{
	if (direct == "left")
	{
		//ImageCopy(this_images["left"], this_current_image);
	} 
	else if (direct == "right")
	{
		ImageCopy(this_images["right"], this_current_image);

	}
	else if (direct == "top")
	{
		ImageCopy(this_images["top"], this_current_image);
	}
	else if (direct == "bottom")
	{
		ImageCopy(this_images["bottom"], this_current_image);
	}
	else
	{

	}
}

void SelfTank::OnPaint(CDC* dc)
{
	//this_current_image = this_images["left"];


	//this_images["left"]->Load(_T("res/tank_right.png"));
	ShowImage(this_current_image, dc, this_locate, this_si, RGB(0, 0, 0));

}

void SelfTank::ShowImage(CImage* fg, CDC* dc, POINT locate, SIZE si, UINT rgb)
{
	/*CBrush brush;
	CBitmap bitMap;
	CImage img;
	img.Load(_T("res/tank_bottom.png"));
	bitMap.Attach(img.Detach());

	CDC memdc;
	memdc.CreateCompatibleDC(NULL);
	memdc.SelectObject(&bitMap);

	dc->TransparentBlt(100, 100, si.cx, si.cy, dc, 0, 0, si.cx, si.cy, rgb);
	bitMap.DeleteObject();*/

	CBrush brush;
	CBitmap bitMap;
	bitMap.Attach(fg->Detach());

	CDC memdc;
	memdc.CreateCompatibleDC(NULL);
	memdc.SelectObject(&bitMap);

	dc->TransparentBlt(locate.x, locate.y, si.cx, si.cy, &memdc, 0, 0, si.cx, si.cy, rgb);
	bitMap.DeleteObject();
}

void SelfTank::InsertImage(std::string direct, LPCTSTR filepath)
{
	CImage* img = new CImage;
	img->Load(filepath);
	this_images.insert(std::make_pair(direct, img));
}

void SelfTank::SetTankSize(SIZE si)
{
	this_si = si;
}

void SelfTank::ImageCopy(CImage* pImgSrc, CImage* pImgDrt)
{
	CDC *pDCsrc, *pDCdrc;
	if (!pImgDrt->IsNull())
	{
		pImgDrt->Destroy();
	}
	pImgDrt->Create(pImgSrc->GetWidth(), pImgSrc->GetHeight(), pImgSrc->GetBPP(), 0);
	pDCsrc = CDC::FromHandle(pImgSrc->GetDC());
	pDCdrc = CDC::FromHandle(pImgDrt->GetDC());
	pDCdrc->BitBlt(0, 0, pImgSrc->GetWidth(), pImgSrc->GetHeight(), pDCsrc, 0, 0, SRCCOPY);
	pImgSrc->ReleaseDC();
	pImgDrt->ReleaseDC();
}