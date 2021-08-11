#include "pch.h"
#include "restaurantScene.h"

restaurantScene::restaurantScene()
{
}

restaurantScene::~restaurantScene()
{
}

HRESULT restaurantScene::init()
{
	_x = 1200;
	_y = 0;

	_select = IMAGEMANAGER->findImage("shopsceneBox");
	_rc = RectMake(_x, _y, _select->getWidth(), _select->getHeight());

	SOUNDMANAGER->addSound("상점", "상점.mp3", true, true);

	SOUNDMANAGER->play("상점", getBGMVolume());

	return S_OK;
}

void restaurantScene::release()
{
}

void restaurantScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && _y < 600)
	{
		_y += 200;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && _y > 0)
	{
		_y -= 200;
	}
	Interaction();
}

void restaurantScene::render()
{
	IMAGEMANAGER->findImage("SHOP_RESTAURANT")->render(getMemDC(), 0, 0);
	_select->render(getMemDC(), _x, _y);
}

void restaurantScene::Interaction()
{
	//스테이크: 플레이어 STR 10 영구증가 , COIN == 300원
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 0)
	{
		//coin - 300원
		//_player->setSTR +10;
	}
	//치킨: 플레이어 SPD 10 영구증가, COIN == 300원
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 200)
	{
		//coin -300원
		//_player->setSPD +10;
	}
	//피자: 플레이어의 DEF 10 영구증가, COIN == 300원
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 400)
	{
		//coin -300원
		//_player->setDEF() +10;
	}
	//햄버거: 플레이어의 WP 10 영구증가, COIN == 300원
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 600)
	{
		//coin -300원
		//_player->setWP() +10;
	}
}
