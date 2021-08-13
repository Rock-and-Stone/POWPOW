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

	_player = new player;
	_player->init(-1000, -1000);

	_ui = new UserInterface;
	_ui->init();

	_ui->setPlayerMemoryAddress(_player);
	SOUNDMANAGER->play("상점", getBGMVolume() / 10);
	return S_OK;
}

void cafeScene::release()
{
}

void cafeScene::update()
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
			SaveData(_player->getCurrentHp(), 100, _player->getCoin());
			SOUNDMANAGER->stop("상점");
			SCENEMANAGER->changeScene("stage1");
		}
		
		Interaction();
	}
	_ui->update();
}

void cafeScene::render()
{
	IMAGEMANAGER->findImage("SHOP_CAFE")->render(getMemDC(), 0, 0);
	_select->render(getMemDC(), _x, _y);

	_ui->render();
	
}

void cafeScene::Interaction()
{
	if (!_player->getCoin() < 100)
	{
		//아메리카노: 플레이어 HP모두 회복, COIN == 100원
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 0)
		{
			_player->setCoin(_player->getCoin() - 100);
			_player->setPlayerHP(100);
			//coin - 100원
			//_player->setHP() -> 100;
		}
		//카페라떼: 플레이어 GP모두 회복, COIN == 100원
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _y == 200)
		{
			_player->setCoin(_player->getCoin() - 100);
			_player->setPlayerGP(100);
			//coin -100원
			//_player->getHP() -> 100;
		}
	}
}
