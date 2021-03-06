#include "pch.h"
#include "stage1.h"

HRESULT stage1::init()
{
	RENDERMANAGER->release();
	SOUNDMANAGER->play("인게임", getBGMVolume() / 10);
	_player = new Ramona;
	_cm = new CameraManager;
	_em = new EnemyManager;
	_om = new ObjectManager;
	_ui = new UserInterface;
	_player->init(getPlayerPosX(),getPlayerPosY());
	_player->InitVariables();

	_isBattle = false;

	_minMapX = 0;
	_mapX = MAPSIZEX;
	_maxY = MAPSIZEY;

	_cm = new CameraManager;
	_cm->init(_minMapX, _mapX, _maxY);

	_em->init();
	_em->SetPlayerLink(_player);
	_em->SetCamera(_cm);
	_em->SetOMLink(_om);

	_om->init();
	_om->SetPlayerLink(_player);
	_om->SetEMLink(_em);
	_om->SetCamera(_cm);
	_om->SetBat();
	_om->SetTrash();

	_ui->init();

	_ui->setPlayerMemoryAddress(_player);

	return S_OK;
}

void stage1::update()
{
	if (_em->GetEnemyCount() == 0)
	{
		_isBattle = false;
		CameraLock();
	}

	if (_player->getPosX() > _stage * SPAWNRATE + 1000 && !_isBattle)
	{
		_isBattle = true;
		_em->SpawnEnemy(1, 1, 1, _stage);
		_stage++;
		CameraLock();
	}

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
		_cm->init(_minMapX,_mapX, _maxY);
#pragma endregion

		if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("bossScene");

		EFFECTMANAGER->update();

		RENDERMANAGER->update();

		pixelCollision();
	}

	_ui->update();

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
	_player->setShadowY(_cm->getRenderPosY());

	_em->render();
	_om->render();

	EFFECTMANAGER->render();
	RENDERMANAGER->render(getMemDC());

	_ui->render();

#pragma region 디버깅


	//TIMEMANAGER->render(getMemDC());

#pragma endregion

}

#pragma region 설명서
//픽셀콜리전 설명서
// 왼쪽 부딪혔을 때 RGB (50,50,50) -> 회색
// 위에 부딪혔을 때 RGB(255, 255, 0)->노랭이
// 오른쪽에 부딪혔을 때 RGB(139, 0, 255)->보랭이
// 아래 부딪혔을 때 RGB(80, 188, 223)->하늘색
// Cafe->RGB(255, 0, 0)->빨갱이
// Restaurant->RGB(0, 255, 0)->초록이
// Convenient->RGB(0, 0, 255)->파랭이
// Sushi->RGB(0, 255, 255)->애매한색
// bossRoom->RGB(0, 170, 255)
// 지옥의 불구덩이->RGB(1, 1, 1)->검정이 + 1
//========================
//원래는 SETPOSY로 밀어주는게 제일 좋은데 잘 안됨
//픽셀 검출은 잘 되는데 왜이러는지 미스테리
#pragma endregion

void stage1::pixelCollision()
{
	//픽셀 콜리전
	_probePlayerX = _player->getPosX();				//플레이어 중앙 부분
	_probePlayerY = _player->getPosY();
	_probePlayerRX = _player->getPosX() + 40;		//플레이어 오른쪽부분
	_probePlayerLX = _player->getPosX() - 40;		//플레이어 왼쪽부분
	_probePlayerBY = _player->getPosY() + 90;		//플레이어 발 부분

	
	//상점 이동 및 보스방 이동
	for (int i = _probePlayerBY - 1; i < _probePlayerBY; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), _player->getPosX(), i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{

			SaveData(_player->getCurrentHp(), 100, _player->getCoin());
			setPlayerPosX(_player->getPosX()); 
			setPlayerPosY(_player->getPosY() + 50 );
			SOUNDMANAGER->stop("인게임");
			SCENEMANAGER->changeScene("cafeScene");
		}

		if ((r == 0 && g == 255 && b == 0))
		{
			SaveData(_player->getCurrentHp(), 100, _player->getCoin());
			setPlayerPosX(_player->getPosX());
			setPlayerPosY(_player->getPosY() + 50);
			SOUNDMANAGER->stop("인게임");
			SCENEMANAGER->changeScene("restaurantScene");
		}

		if ((r == 0 && g == 0 && b == 255))
		{
			SaveData(_player->getCurrentHp(), 100, _player->getCoin());
			setPlayerPosX(_player->getPosX());
			setPlayerPosY(_player->getPosY() + 50);
			SOUNDMANAGER->stop("인게임");
			SCENEMANAGER->changeScene("convenientScene");
		}

		if ((r == 0 && g == 255 && b == 255))
		{
			SaveData(_player->getCurrentHp(), 100, _player->getCoin());
			setPlayerPosX(_player->getPosX());
			setPlayerPosY(_player->getPosY() + 50);
			SOUNDMANAGER->stop("인게임");
			SCENEMANAGER->changeScene("sushiScene");
		}

		if ((r == 0 && g == 170 && b == 255))
		{
			SaveData(_player->getCurrentHp(), 100, _player->getCoin());
			SOUNDMANAGER->stop("인게임");
			SCENEMANAGER->changeScene("bossScene");
		}
	}

	//픽셀 윗 충돌
	//플레이어
	for (int i = _probePlayerBY - 5; i < _probePlayerBY  ; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), _player->getPosX(), i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 255 && b == 0))
		{
			_player->setSpeedY(0);
			_player->setPosY(i - 84);
		}
	}
	


	//픽셀 아랫 충돌
	//플레이어
	for (int i = _probePlayerBY + 5; i > _probePlayerBY; --i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), _player->getPosX(), i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 255 && b == 0))
		{
			_player->setSpeedY(0);
			_player->setPosY(i - 95);
		}
	}
	

	//픽셀 오른쪽 충돌
	//플레이어
	for (int i = _probePlayerRX + 5; i > _probePlayerRX; --i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), i, _probePlayerBY);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 255 && b == 0))
		{
			_player->setSpeedX(0);
			_player->setPosX(i - 45);
		}
	}

	

	//픽셀 왼쪽 충돌
	//플레이어
	for (int i = _probePlayerLX - 5; i < _probePlayerLX; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), i, _probePlayerBY);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 255 && b == 0))
		{
			_player->setSpeedX(0);
			_player->setPosX(i + 45);
		}
	}
	
}

void stage1::CameraLock()
{
	if (!_isBattle)
	{
		_minMapX = 0;
		_mapX = MAPSIZEX;
	}
	else
	{
		_minMapX = _cm->getCamX();
		_mapX = _cm->getCamX() + WINSIZEX;
	}
}
