#pragma once
#include <map>
#include <string>
#include "stdafx.h"
#include "afxdialogex.h"

class Unit
{
public:
	Unit();
	virtual ~Unit();
	virtual void OnPaint(CDC* dc);
	virtual void ShowBitmap(UINT ID, CDC* dc, POINT locate, SIZE si);
	virtual void ShowImage(CImage cImg, CDC* dc, POINT locate, SIZE si, UINT rgb);

protected:
	std::map<std::string, CImage*> this_images;
	CImage* this_current_image;
	POINT this_locate;
	SIZE this_si;
};

