#include "pch.h"
#include "bossScene.h"

HRESULT bossScene::init()
{
	_bossBackground = IMAGEMANAGER->findImage("bossBackground");
	
#pragma region 인트로 동영상 이닛

	_bossIntro = MCIWndCreate(_hWnd, NULL, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, "source/Bossintro.wmv");
	MoveWindow(_bossIntro, 0, 0, WINSIZEX, WINSIZEY, NULL);
	MCIWndPlay(_bossIntro);
	SCENEMANAGER->SetVideoPlay(true);

#pragma endregion

	SOUNDMANAGER->play("보스방", getBGMVolume() / 10);
	_boss = new boss;
	_boss->init();

	_player = new Ramona;
	_player->init(WINSIZEX/2,WINSIZEY /2);
	_player->InitVariables();

	_ui = new UserInterface;
	_ui->init();

	_ui->setPlayerMemoryAddress(_player);

	RENDERMANAGER->release();

	RENDERMANAGER->addRender(_player);
	RENDERMANAGER->addRender(_boss);


	return S_OK;
}

void bossScene::update()
{

#pragma region 동영상 스킵 및 삭제
	if (MCIWndGetLength(_bossIntro) <= MCIWndGetPosition(_bossIntro))
	{
		MCIWndDestroy(_bossIntro);
		SCENEMANAGER->SetVideoPlay(false);
	}
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{

		if (SCENEMANAGER->GetVideoPlay())
		{
			MCIWndDestroy(_bossIntro);
			SCENEMANAGER->SetVideoPlay(false);
		}
	}
#pragma endregion

	if (!_ui->GetIsPause())
	{
		_boss->update();
		_player->setRendX(_player->getPosX());
		_player->setRendY(_player->getPosY());
		_player->update();
	}

	RENDERMANAGER->update();

	_ui->update();
}

void bossScene::release()
{
}

void bossScene::render()
{
	_bossBackground->render(getMemDC());

	RENDERMANAGER->render(getMemDC());

	_ui->render();
}
