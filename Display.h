#ifndef DISPLAY_H
#define DISPLAY_H

class Display 
{
	HDC			DC, memDC, picDC;
	HBITMAP		memBmp, picBmp, maskBmp;
	class GameWorld *pGameWorld;
	class Bitmap *pBitmap;

	void SetClientSize(HWND, int, int);
public:
	HDC GetOffscreenDC();
	Display(GameWorld*);
	~Display();
	void Clear();
	void DrawToOffscreen(int x, int y, int w, int h, int sx, int sy, bool bTransparent);
	void DrawAllToScreen();
};

#endif