#include "pch.h"
#include "EnemyDown.h"
#include "Enemy.h"

HRESULT EnemyDown::init()
{
	return S_OK;
}

void EnemyDown::release()
{
}

void EnemyDown::update()
{
	//만약 아직 HP가 0이 아니면 -> UP
	//만약 뒤지면 -> 알파블렌드로 처리한다음에-> DEAD // findIMAGE-> 마젠타
}