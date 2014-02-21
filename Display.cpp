#include "stdafx.h"
// 构造函数
Display::Display(GameWorld *pgw)
:pGameWorld(pgw)
{
	// SetClientSize(pGameWorld->GameWindow, pGameWorld->Width, pGameWorld->Height);
	SetClientSize(pGameWorld->GameWindow, pGameWorld->Width+6, pGameWorld->Height+25);

	pBitmap=new Bitmap("picture.bmp", true, RGB(255, 0, 255));
	// 初始化图形环境

	DC=GetDC(pGameWorld->GameWindow);
	memDC=CreateCompatibleDC(DC);
	memBmp=CreateCompatibleBitmap(DC, pGameWorld->Width, pGameWorld->Height);
	SelectObject(memDC, memBmp);
}

// 释构函数
Display::~Display()
{
	// 释放GDI资源
	ReleaseDC(pGameWorld->GameWindow,DC);
	DeleteDC(memDC);
	DeleteObject(memBmp);
}

// 把图形绘制到离屏表面中
void Display::DrawToOffscreen(int x, int y, int w, int h, int sx, int sy, bool bTransparent)
{
	pBitmap->Draw(memDC, x, y, w, h, sx, sy);
}

// 把画面输出到屏幕
void Display::DrawAllToScreen()
{
	// BitBlt(memDC, 0, 0, 100, 100, picDC, 0, 0, SRCCOPY);
	BitBlt(DC, 0, 0, pGameWorld->Width, pGameWorld->Height, memDC, 0, 0, SRCCOPY);
}

// 设置窗口客户区大小
void Display::SetClientSize(HWND hwnd, int Width, int Height) 
{
	RECT	w_rect, c_rect;
	int		dw, dh;

	// ?得到的结果总为0
	GetWindowRect(hwnd, &w_rect);
	GetClientRect(hwnd, &c_rect);
	dw=w_rect.right-w_rect.left-(c_rect.right-c_rect.left);
	dh=w_rect.bottom-w_rect.top-(c_rect.bottom-c_rect.top);

	SetWindowPos(hwnd, 0, 0, 0, Width+dw, Height+dh, SWP_NOMOVE | SWP_NOZORDER);
}

// 清除画面
void Display::Clear()
{
	SelectObject(memDC, GetStockObject(BLACK_BRUSH));
	Rectangle(memDC, 0, 0, pGameWorld->Width, pGameWorld->Height);
}

HDC Display::GetOffscreenDC()
{
	return memDC;
}
