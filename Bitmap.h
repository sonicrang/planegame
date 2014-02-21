#ifndef BITMAP_H
#define BITMAP_H

class Bitmap
{
private:
	HBITMAP		hbmp, hmask;
	int			w, h;
	BOOL		bTransMode;
	COLORREF	TransColor;

	void	Load(char *fn);
	void	CreateMask();
public:
	Bitmap(char *fn, BOOL transmode, COLORREF transcolor);
	~Bitmap();

	HBITMAP	GetBitmap()	{return hbmp;};
	int		GetWidth()	{return w;};
	int		GetHeight()	{return h;};
	
	void	Draw(HDC ddc, int dx, int dy, int dw, int dh, int sx, int sy);
};

#endif