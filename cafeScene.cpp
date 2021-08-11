#include "pch.h"
#include "cafeScene.h"

cafeScene::cafeScene()
{
}

cafeScene::~cafeScene()
{
}

HRESULT cafeScene::init()
{
	_x = 1200;
	_y = 0;
	
	_select = IMAGEMANAGER->findImage("shopsceneBox");
	_rc = RectMake(_x, _y, _select->getWidth(), _select->getHeight());

	return S_OK;
}

void cafeScene::release()
{
}

void cafeScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && _y < 200)
	{
		_y += 200;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && _y > 0)
	{
		_y -= 200;
	}
	Interaction();
}

void cafeScene::render()
{
	IMAGEMANAGER->findImage("SHOP_CAFE")->render(getMemDC(), 0, 0);
	_select->render(getMemDC(), _x, _y);
	
}

void cafeScene::Interaction()
{
	//아메리카노: 플레이어 HP모두 회복, COIN == 100원
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 0)
	{
		//coin - 100원
		//_player->setHP() -> 100;
	}
	//카페라떼: 플레이어 GP모두 회복, COIN == 100원
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 200)
	{
		//coin -100원
		//_player->getHP() -> 100;
	}
}
