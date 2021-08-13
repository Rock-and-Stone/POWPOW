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

	_player = new player;
	_ui = new UserInterface;
	_ui->init();

	_ui->setPlayerMemoryAddress(_player);

	SOUNDMANAGER->play("����", getBGMVolume()/10);
	return S_OK;
}

void convenientScene::release()
{
}

void convenientScene::update()
{
	if (!_ui->GetIsPause())
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
			SOUNDMANAGER->stop("����");
			SCENEMANAGER->changeScene("stage1");
		}
		Interaction();
	}
	

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
	//ǳ����: �÷��̾� STR&&DEF 10 ���� , COIN == 200��
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 0)
	{
		//coin - 200��
		//_player->setSTR || setDEF() +10;
	}
	//ī���: �÷��̾� SPD&GP 10 ����, COIN == 200��
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 200)
	{
		//coin -200��
		//_player->setSPD || setDEF() +10;
	}
}
