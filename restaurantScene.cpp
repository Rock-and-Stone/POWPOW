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

	SOUNDMANAGER->addSound("����", "����.mp3", true, true);

	SOUNDMANAGER->play("����", getBGMVolume());

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
	//������ũ: �÷��̾� STR 10 �������� , COIN == 300��
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 0)
	{
		//coin - 300��
		//_player->setSTR +10;
	}
	//ġŲ: �÷��̾� SPD 10 ��������, COIN == 300��
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 200)
	{
		//coin -300��
		//_player->setSPD +10;
	}
	//����: �÷��̾��� DEF 10 ��������, COIN == 300��
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 400)
	{
		//coin -300��
		//_player->setDEF() +10;
	}
	//�ܹ���: �÷��̾��� WP 10 ��������, COIN == 300��
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 600)
	{
		//coin -300��
		//_player->setWP() +10;
	}
}
