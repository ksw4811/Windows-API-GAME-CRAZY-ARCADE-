#pragma once
#include "stdafx.h"
#include "Define.h"
#include "myJson.h"

extern HINSTANCE hInst;
extern HWND g_hWnd;
extern RECT crt;

class Wave
{
private:
	HWND myHWND;
	HDC myDC;
	string filename;
	int nWidth, nHeight;
	HBITMAP PopDownbit, PopUpbit, PopLeftbit, PopRightbit;
	HBITMAP PopDownold, PopUpold, PopLeftold, PopRightold;
	myJson parseJson;
	int PopFrameX = 0;
	bool myActivation = false;
	int nConnection = 0;
public:
	Wave();
	~Wave();
	void Initialize(HDC hdc);
	void Progress();
	void Render(HDC hdc, float fX, float fY, int m_FrameX); // ��ǳ�� ��ġ
	int getWidth(const char* chFileName);
	int getHeight(const char* chFileName);
	float getX();
	float getY();
	void CreateBomb(float m_fX, float m_fY);
	void DeleteBomb();
	bool ExistBomb();
};