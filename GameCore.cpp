// 01. GameCore
#include "GameCore.h"


GameCore::GameCore()
{
}

GameCore::~GameCore()
{
	Release();
}

void GameCore::Initialize()
{
	nCurrent = 0; // 0 = main, 1 = GameStart, 2 = GameMenu, 3 = GameOver
	myHDC = GetDC(g_hWnd);
	myLogin.Initialize(myHDC);
	myLobby.Initialize(myHDC);
	myBackGround.Initialize(myHDC);
	myPlayer.Initialize(myHDC);
	myShadow.Initialize(myHDC);
	myBlock.Initialize(myHDC);
	myDbBuf.Initialize();
}

void GameCore::Progress()
{
	if (nCurrent == 0)
	{
		nInitNum = myLogin.Progress(nCurrent);
		if (nInitNum == 1)
		{
			myDbBuf.DeleteScreen();
		}
	}
	if (nCurrent == 1)
	{
		nInitNum = myLobby.Progress(nCurrent);
		if (nInitNum == 1)
		{
			myDbBuf.DeleteScreen();
		}
	}

	else if (nCurrent == 2)
	{
		if (nFrame == 10)
		{
			// 블록들과 캐릭터의 충돌
			for (int nIndex = 0; nIndex < 12; nIndex++)
			{
				for (int nJndex = 0; nJndex < 27; nJndex++)
				{
					myPlayer.pushbackPlayer(myCollison.SetNotInterSect(myPlayer.getPlayerRECT(myXY.myX, myXY.myY), myBlock.getBlockRect(nIndex, nJndex)));
				}
			}
			nFrame = 0;
		}

		nFrame++;
	}
}

void GameCore::Render()
{
	if (nCurrent == 0)
	{
		myLogin.Render(myDbBuf.ReturnBackDC());
		//myImageManager.Render("BazziDown1", myDbBuf.ReturnBackDC());
	}

	else if (nCurrent == 1)
	{
		myLobby.Render(myDbBuf.ReturnBackDC());
		myShadow.Render(myDbBuf.ReturnBackDC(), 1);
		myPlayer.Render(myDbBuf.ReturnBackDC(), 1);
	}

	else if (nCurrent == 2)
	{
		myBackGround.Render(myDbBuf.ReturnBackDC());
		myShadow.Render(myDbBuf.ReturnBackDC());
		myBlock.Render(myDbBuf.ReturnBackDC());
		myPlayer.Render(myDbBuf.ReturnBackDC());
	}
	myDbBuf.Render();
}

void GameCore::Release()
{
	ReleaseDC(g_hWnd, myHDC);
}