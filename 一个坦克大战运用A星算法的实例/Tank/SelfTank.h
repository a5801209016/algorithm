#pragma once
#include "gdiplusenums.h"
#include "Unit.h"
class SelfTank :public Unit
{
	enum DIRECT
	{
		LEFT = 0,
		RIGHT,
		TOP,
		BOTTOM

	};
public:
	SelfTank();
	~SelfTank();
	void SetDirect(std::string direct);
public:
	virtual void OnPaint(CDC* dc);
	virtual void ShowImage(CImage* cImg, CDC* dc, POINT locate, SIZE si, UINT rgb);

protected:
	void InsertImage(std::string direct, LPCTSTR filepath);
	void SetTankSize(SIZE si);
	void ImageCopy(CImage* pImgSrc, CImage* pImgDrt);
};

