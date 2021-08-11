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

	SOUNDMANAGER->addSound("����", "����.mp3", true, true);

	SOUNDMANAGER->play("����", getBGMVolume());

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
	//����ʹ�: �÷��̾� WP 10 �������� , COIN == 300��
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 0)
	{
		//coin - 300��
		//_player->setWP +10;
	}
	//�����ʹ�: �÷��̾� SPD 10 ��������, COIN == 300��
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 200)
	{
		//coin -300��
		//_player->setSPD +10;
	}
	//��ȸ�ʹ�: �÷��̾��� DEF 10 ��������, COIN == 300��
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 400)
	{
		//coin -300��
		//_player->setDEF() +10;
	}
	//�ܹ���: �÷��̾��� STR 10 ��������, COIN == 300��
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 600)
	{
		//coin -300��
		//_player->setSTR() +10;
	}
}
