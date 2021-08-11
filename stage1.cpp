#include "pch.h"
#include "stage1.h"

HRESULT stage1::init()
{

	_player = new Ramona;
	_player->init(600,600);
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
	_om->SetTrash();

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
#pragma region ���ī�޶󹫺�
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


		if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("bossScene");


		EFFECTMANAGER->update();

		RENDERMANAGER->update();

	}

	_ui->update();


	pixelCollision();

	EFFECTMANAGER->update();
	RENDERMANAGER->update();
}

void stage1::release()
{
}

void stage1::render()
{
	IMAGEMANAGER->findImage("background")->render(getMemDC(), 0, 0, _cm->getCamX(), _cm->getCamY(), WINSIZEX, WINSIZEY);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->findImage("col")->render(getMemDC(), 0, 0, _cm->getCamX(), _cm->getCamY(), WINSIZEX, WINSIZEY);
	}
	

	_player->setRendX(_cm->getRenderPosX());
	_player->setRendY(_cm->getRenderPosY());

	_em->render();
	_om->render();



	EFFECTMANAGER->render();
	RENDERMANAGER->render(getMemDC());

	//_player->render(_cm->getRenderPosX(), _cm->getRenderPosY());

	_ui->render();

#pragma region �����

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

void stage1::pixelCollision()
{
	//�ȼ� �ݸ���
	_probePlayerX = _player->getPosX();
	_probePlayerY = _player->getPosY() + 91;

	for (int i = _probePlayerY; i < _probePlayerY + 1; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), _player->getPosX(), i);

		_r = GetRValue(color);
		_g = GetGValue(color);
		_b = GetBValue(color);

		if ((_r == 255 && _g == 0 && _b == 0))
		{
			SCENEMANAGER->changeScene("cafeScene");
		}

		if ((_r == 0 && _g == 255 && _b == 0))
		{
			SCENEMANAGER->changeScene("restaurantScene");
		}

		if ((_r == 0 && _g == 0 && _b == 255))
		{
			SCENEMANAGER->changeScene("convenientScene");
		}

		if ((_r == 0 && _g == 255 && _b == 255))
		{
			SCENEMANAGER->changeScene("sushiScene");
		}

		if ((_r == 0 && _g == 0 && _b == 0))
		{
			SCENEMANAGER->changeScene("bossScene");
		}

		if ((_r == 255 && _g == 0 && _b == 255))
		{
			_player->setSpeedY(0);
		}
	}
}
