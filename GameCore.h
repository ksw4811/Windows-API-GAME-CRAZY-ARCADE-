#pragma once
#include "stdafx.h"
#include "Define.h"
#include "DbBuf.h"
#include "background.h"
#include "Player.h"
#include "Shadow.h"
#include "Mark.h"
#include "Login.h"
#include "Lobby.h"
#include "ImageManager.h"

//나머지 게임에 관련된 클래스가 있는 헤더를 추가한다.
extern HINSTANCE hInst;                                // 현재 인스턴스입니다.
extern HWND g_hWnd;
extern RECT crt;

class GameCore
{
private:
	//관련된 클래스들 추가
	HDC myHDC = GetDC(g_hWnd);
	ImageManager myImageManager;
	DbBuf myDbBuf;
	BackGround myBackGround;
	Player myPlayer;
	Shadow myShadow;
	Mark myMark;
	Login myLogin;
	Lobby myLobby;
	int nCurrent = 0;
	int nInitNum = 0;

public:
	GameCore();
	~GameCore();

	void Initialize(); // 초기화
	void Progress(); // 처리
	void Render(); // 그리기
	void Release();

};