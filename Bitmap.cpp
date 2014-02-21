#include "stdafx.h"
#include "Bitmap.h"

//--------------------------------------------
//  构造函数
//--------------------------------------------
Bitmap::Bitmap(char *fn, BOOL transmode=false, COLORREF transcolor=RGB(255, 0, 255)):
	hbmp(NULL),
	hmask(NULL),
	w(0),
	h(0),
	bTransMode(transmode),
	TransColor(transcolor)
{
	Load(fn);
	if(bTransMode)
		CreateMask();
}

//--------------------------------------------
//  释构函数
//--------------------------------------------
Bitmap::~Bitmap()
{
	DeleteObject(hbmp);
}

//--------------------------------------------
//  Load()
//  载入图像文件
//--------------------------------------------
void Bitmap::Load(char *fn)
{
	DeleteObject(hbmp);
	hbmp=(HBITMAP)LoadImage(
		NULL,
		fn,
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION
		);
	DIBSECTION		ds;
	GetObject(hbmp, sizeof(ds), &ds);
	w=ds.dsBmih.biWidth;
	h=ds.dsBmih.biHeight;
}

//--------------------------------------------
//  CreateMask()
//  载入图像文件
//--------------------------------------------
void Bitmap::CreateMask()
{
	hmask=CreateBitmap(w, h, 1, 1, NULL);
	HDC bmpDC=CreateCompatibleDC(0);
	HDC maskDC=CreateCompatibleDC(0);
	SelectObject(bmpDC, hbmp);
	SelectObject(maskDC, hmask);

	SetBkColor(bmpDC, TransColor);
	BitBlt(maskDC, 0, 0, w, h, bmpDC, 0, 0, SRCCOPY);
	SetBkColor(bmpDC, RGB(0, 0, 0));
	SetTextColor(bmpDC, RGB(255, 255, 255));
	BitBlt(bmpDC, 0, 0, w, h, maskDC, 0, 0, SRCAND);

	DeleteDC(bmpDC);
	DeleteDC(maskDC);
}

//--------------------------------------------
//  Draw()
//  输出到设备场景上
//--------------------------------------------
void Bitmap::Draw(HDC ddc, int dx=0, int dy=0, int dw=0, int dh=0, int sx=0, int sy=0)
{
	if(!dw) dw=w;
	if(!dh) dh=h;

	HDC bmpDC=CreateCompatibleDC(ddc);
	SelectObject(bmpDC, hbmp);

	if(bTransMode)
	{
		HDC maskDC=CreateCompatibleDC(ddc);
		SelectObject(maskDC, hmask);

		BitBlt(ddc, dx, dy, dw, dh, maskDC, sx, sy, SRCAND);
		BitBlt(ddc, dx, dy, dw, dh, bmpDC, sx, sy, SRCPAINT);

		DeleteDC(maskDC);
	}
	else
		BitBlt(ddc, dx, dy, dw, dh, bmpDC, sx, sy, SRCCOPY);

	DeleteDC(bmpDC);
}
