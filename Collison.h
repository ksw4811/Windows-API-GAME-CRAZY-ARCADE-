//충돌 처리
#include "stdafx.h"
#include "Define.h"
#include "Player.h"
#include "Statue.h"


class Collison
{
private:
public:
	void Initialize() {};
	void Progress();
	void Render() {};
	Direction SetNotInterSect(RECT& pRect, RECT pHold); // 사각형 끼리 교차되지 않게 셋팅
};