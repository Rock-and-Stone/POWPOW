#include "pch.h"
#include "stage1.h"

HRESULT stage1::init()
{

	_player = new Ramona;
	_player->init();
	_player->InitVariables();

	_maxY = 1000;

	_cm = new CameraManager;
	_cm->init(31812, _maxY);

	_em = new EnemyManager;
	_em->init();
	_em->SetPlayerLink(_player);
	_em->SetCamera(_cm);
	_em->SetLuke();
	_em->SetMike();
	_em->SetMalcolm();

	_om = new ObjectManager;
	_om->init();
	_om->SetPlayerLink(_player);
	_om->SetCamera(_cm);
	_om->SetBat();

	_ui = new UserInterface;
	_ui->init();
	


	return S_OK;
}

void stage1::update()
{
	if (!_ui->GetIsPause())
	{
		_player->update();

		_cm->update(_player->getPosX(), _player->getPosY());

		_em->update();

		_om->update();
#pragma region ¾ð´öÄ«¸Þ¶ó¹«ºê

		if (_player->getPosX() >= 24765)
		{
			if (_maxY <= 1000) _maxY = 1000 + 0.6 * (_player->getPosX() - 24765);
		}

		if (_maxY >= 1000)
		{
			_maxY = 1000;
		}

		_cm->init(31812, _maxY);	
#pragma endregion

	}

	_ui->update();
	EFFECTMANAGER->update();
	RENDERMANAGER->update();
}

void stage1::release()
{
}

void stage1::render()
{
	IMAGEMANAGER->findImage("background")->render(getMemDC(), 0, 0, _cm->getCamX(), _cm->getCamY(), WINSIZEX, WINSIZEY);
	
	_player->setRendX(_cm->getRenderPosX());
	_player->setRendY(_cm->getRenderPosY());

	_em->render();
	_om->render();
	EFFECTMANAGER->render();
	RENDERMANAGER->render(getMemDC());

	//_player->render(_cm->getRenderPosX(), _cm->getRenderPosY());

	_ui->render();

#pragma region µð¹ö±ë

	char str[256];
	HFONT oldFont, font1;

	sprintf_s(str, "char X : %f", _player->getPosX());
	TextOut(getMemDC(), 100, 90, str, strlen(str));

	sprintf_s(str, "render X : %d", _cm->getRenderPosX());
	TextOut(getMemDC(), 100, 110, str, strlen(str));


	sprintf_s(str, "char Y : %f", _player->getPosY());
	TextOut(getMemDC(), 100, 130, str, strlen(str));

	sprintf_s(str, "render Y : %d", _cm->getRenderPosY());
	TextOut(getMemDC(), 100, 150, str, strlen(str));

	//RENDERMANAGER->render(getMemDC());
	TIMEMANAGER->render(getMemDC());

#pragma endregion

}
