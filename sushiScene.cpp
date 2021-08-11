#include "pch.h"
#include "sushiScene.h"

sushiScene::sushiScene()
{
}

sushiScene::~sushiScene()
{
}

HRESULT sushiScene::init()
{
	_x = 1200;
	_y = 0;

	_select = IMAGEMANAGER->findImage("shopsceneBox");
	_rc = RectMake(_x, _y, _select->getWidth(), _select->getHeight());

	SOUNDMANAGER->addSound("상점", "상점.mp3", true, true);

	SOUNDMANAGER->play("상점", getBGMVolume());

	_ui = new UserInterface;
	_ui->init();


	return S_OK;

}

void sushiScene::release()
{
}

void sushiScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && _y < 600)
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

void sushiScene::render()
{
	IMAGEMANAGER->findImage("SHOP_SUSHI")->render(getMemDC(), 0, 0);
	_select->render(getMemDC(), _x, _y);

	_ui->render();
}

void sushiScene::Interaction()
{
	//계란초밥: 플레이어 WP 10 영구증가 , COIN == 300원
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 0)
	{
		//coin - 300원
		//_player->setWP +10;
	}
	//연어초밥: 플레이어 SPD 10 영구증가, COIN == 300원
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 200)
	{
		//coin -300원
		//_player->setSPD +10;
	}
	//육회초밥: 플레이어의 DEF 10 영구증가, COIN == 300원
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 400)
	{
		//coin -300원
		//_player->setDEF() +10;
	}
	//햄버거: 플레이어의 STR 10 영구증가, COIN == 300원
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 600)
	{
		//coin -300원
		//_player->setSTR() +10;
	}
}
