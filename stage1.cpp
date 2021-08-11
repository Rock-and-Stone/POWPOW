#include "pch.h"
#include "stage1.h"

HRESULT stage1::init()
{
	RENDERMANAGER->release();
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
#pragma region 언덕카메라무브
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

<<<<<<< HEAD

=======
	pixelCollision();

	EFFECTMANAGER->update();
	RENDERMANAGER->update();
>>>>>>> fb8fc07c68e78ed6d4a78ec61ad43617b651a177
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

#pragma region 디버깅

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

//========================
//원래는 SETPOSY로 밀어주는게 제일 좋은데 잘 안됨
//픽셀 검출은 잘 되는데 왜이러는지 미스테리

void stage1::pixelCollision()
{
	//픽셀 콜리전
	_probePlayerX = _player->getPosX();				//플레이어 중앙 부분
	_probePlayerY = _player->getPosY();
	_probePlayerRX = _player->getPosX() + 40;		//플레이어 오른쪽부분
	_probePlayerLX = _player->getPosX() - 40;		//플레이어 왼쪽부분
	_probePlayerBY = _player->getPosY() + 90;		//플레이어 발 부분
	
	
	//플레이어 렉트 아랫부분에 충돌했을 때 (마젠타가 플레이어 발보다 위에 있을 때 )
	for (int i = _probePlayerBY - 1; i < _probePlayerBY; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), _player->getPosX(), i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			SCENEMANAGER->changeScene("cafeScene");
		}

		if ((r == 0 && g == 255 && b == 0))
		{
			SCENEMANAGER->changeScene("restaurantScene");
		}

		if ((r == 0 && g == 0 && b == 255))
		{
			SCENEMANAGER->changeScene("convenientScene");
		}

		if ((r == 0 && g == 255 && b == 255))
		{
			SCENEMANAGER->changeScene("sushiScene");
		}

		if ((r == 0 && g == 0 && b == 0))
		{
			SCENEMANAGER->changeScene("bossScene");
		}

		//마젠타가 위에 있을 때
		if ((r == 255 && g == 0 && b == 255))
		{
			_player->setSpeedY(-2);
		}
	}

	//픽셀 우 충돌 
	for (int i = _probePlayerRX; i < _probePlayerRX + 1; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), i, _player->getPosY());

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 255))
		{
			_player->setSpeedX(-2);
		}
	}
	//픽셀 좌 충돌
	for (int i = _probePlayerLX - 1; i < _probePlayerLX; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), i, _player->getPosY());

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 255))
		{
			_player->setSpeedX(-2);
		}
	}

	//픽셀 하 충돌
	for (int i = _probePlayerBY; i < _probePlayerBY + 1; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), _player->getPosX(), i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 255))
		{
			_player->setSpeedY(-2);
		}
	}

}
