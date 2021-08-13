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



	_player = new player;
	_player->init(-1000, -1000);

	_ui = new UserInterface;
	_ui->init();

	_ui->setPlayerMemoryAddress(_player);

	SOUNDMANAGER->play("����", getBGMVolume()/10);

	return S_OK;

}

void sushiScene::release()
{
}

void sushiScene::update()
{
	if (!_ui->GetIsPause())
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
			SaveData(_player->getCurrentHp(), 100, _player->getCoin());

			SOUNDMANAGER->stop("����");
			SCENEMANAGER->changeScene("stage1");

		}
		Interaction();
	}
	

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
		_player->setCoin(_player->getCoin() - 300);
		//coin - 300��
		//_player->setWP +10;
	}
	//�����ʹ�: �÷��̾� SPD 10 ��������, COIN == 300��
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 200)
	{
		_player->setCoin(_player->getCoin() - 300);
		//coin -300��
		//_player->setSPD +10;
	}
	//��ȸ�ʹ�: �÷��̾��� DEF 10 ��������, COIN == 300��
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 400)
	{
		_player->setCoin(_player->getCoin() - 300);
		//coin -300��
		//_player->setDEF() +10;
	}
	//�ܹ���: �÷��̾��� STR 10 ��������, COIN == 300��
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 600)
	{
		_player->setCoin(_player->getCoin() - 300);
		//coin -300��
		//_player->setSTR() +10;
	}
}
