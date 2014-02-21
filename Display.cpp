#include "stdafx.h"
// ���캯��
Display::Display(GameWorld *pgw)
:pGameWorld(pgw)
{
	// SetClientSize(pGameWorld->GameWindow, pGameWorld->Width, pGameWorld->Height);
	SetClientSize(pGameWorld->GameWindow, pGameWorld->Width+6, pGameWorld->Height+25);

	pBitmap=new Bitmap("picture.bmp", true, RGB(255, 0, 255));
	// ��ʼ��ͼ�λ���

	DC=GetDC(pGameWorld->GameWindow);
	memDC=CreateCompatibleDC(DC);
	memBmp=CreateCompatibleBitmap(DC, pGameWorld->Width, pGameWorld->Height);
	SelectObject(memDC, memBmp);
}

// �͹�����
Display::~Display()
{
	// �ͷ�GDI��Դ
	ReleaseDC(pGameWorld->GameWindow,DC);
	DeleteDC(memDC);
	DeleteObject(memBmp);
}

// ��ͼ�λ��Ƶ�����������
void Display::DrawToOffscreen(int x, int y, int w, int h, int sx, int sy, bool bTransparent)
{
	pBitmap->Draw(memDC, x, y, w, h, sx, sy);
}

// �ѻ����������Ļ
void Display::DrawAllToScreen()
{
	// BitBlt(memDC, 0, 0, 100, 100, picDC, 0, 0, SRCCOPY);
	BitBlt(DC, 0, 0, pGameWorld->Width, pGameWorld->Height, memDC, 0, 0, SRCCOPY);
}

// ���ô��ڿͻ�����С
void Display::SetClientSize(HWND hwnd, int Width, int Height) 
{
	RECT	w_rect, c_rect;
	int		dw, dh;

	// ?�õ��Ľ����Ϊ0
	GetWindowRect(hwnd, &w_rect);
	GetClientRect(hwnd, &c_rect);
	dw=w_rect.right-w_rect.left-(c_rect.right-c_rect.left);
	dh=w_rect.bottom-w_rect.top-(c_rect.bottom-c_rect.top);

	SetWindowPos(hwnd, 0, 0, 0, Width+dw, Height+dh, SWP_NOMOVE | SWP_NOZORDER);
}

// �������
void Display::Clear()
{
	SelectObject(memDC, GetStockObject(BLACK_BRUSH));
	Rectangle(memDC, 0, 0, pGameWorld->Width, pGameWorld->Height);
}

HDC Display::GetOffscreenDC()
{
	return memDC;
}
