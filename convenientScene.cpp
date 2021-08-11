#include "pch.h"
#include "convenientScene.h"

convenientScene::convenientScene()
{
}

convenientScene::~convenientScene()
{
}

HRESULT convenientScene::init()
{
	_x = 1200;
	_y = 0;

	_select = IMAGEMANAGER->findImage("shopsceneBox");
	_rc = RectMake(_x, _y, _select->getWidth(), _select->getHeight());

	_ui = new UserInterface;
	_ui->init();

	return S_OK;
}

void convenientScene::release()
{
}

void convenientScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && _y < 200)
	{
		_y += 200;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && _y > 0)
	{
		_y -= 200;
	}
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		SCENEMANAGER->changeScene("stage1");
	}
	Interaction();

	_ui->update();
}

void convenientScene::render()
{
	IMAGEMANAGER->findImage("SHOP_CONVENIENT")->render(getMemDC(), 0, 0);
	_select->render(getMemDC(), _x, _y);

	_ui->render();
}

void convenientScene::Interaction()
{
	//풍선껌: 플레이어 STR&&DEF 10 증가 , COIN == 200원
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 0)
	{
		//coin - 200원
		//_player->setSTR || setDEF() +10;
	}
	//카페라떼: 플레이어 SPD&GP 10 증가, COIN == 200원
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 200)
	{
		//coin -200원
		//_player->setSPD || setDEF() +10;
	}
}
