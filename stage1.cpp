#include "pch.h"
#include "stage1.h"

HRESULT stage1::init()
{
	RENDERMANAGER->release();
	SOUNDMANAGER->play("�ΰ���", getBGMVolume() / 10);
	_player = new Ramona;
	_player->init(getPlayerPosX(),getPlayerPosY());
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

#pragma region ����
//�ȼ��ݸ��� ����
// ���� �ε����� �� RGB (50,50,50) -> ȸ��
// ���� �ε����� �� RGB(255, 255, 0)->�뷩��
// �����ʿ� �ε����� �� RGB(139, 0, 255)->������
// �Ʒ� �ε����� �� RGB(80, 188, 223)->�ϴû�
// Cafe->RGB(255, 0, 0)->������
// Restaurant->RGB(0, 255, 0)->�ʷ���
// Convenient->RGB(0, 0, 255)->�ķ���
// Sushi->RGB(0, 255, 255)->�ָ��ѻ�
// bossRoom->RGB(0, 170, 255)
// ������ �ұ�����->RGB(1, 1, 1)->������ + 1
//========================
//������ SETPOSY�� �о��ִ°� ���� ������ �� �ȵ�
//�ȼ� ������ �� �Ǵµ� ���̷����� �̽��׸�
#pragma endregion
void stage1::pixelCollision()
{
	//�ȼ� �ݸ���
	_probePlayerX = _player->getPosX();				//�÷��̾� �߾� �κ�
	_probePlayerY = _player->getPosY();
	_probePlayerRX = _player->getPosX() + 40;		//�÷��̾� �����ʺκ�
	_probePlayerLX = _player->getPosX() - 40;		//�÷��̾� ���ʺκ�
	_probePlayerBY = _player->getPosY() + 90;		//�÷��̾� �� �κ�
	
	
	//���� �̵� �� ������ �̵�
	for (int i = _probePlayerBY - 1; i < _probePlayerBY; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), _player->getPosX(), i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			SaveData();
			setPlayerPosX(_player->getPosX());
			setPlayerPosY(_player->getPosY() + 50 );
			SOUNDMANAGER->stop("�ΰ���");
			SCENEMANAGER->changeScene("cafeScene");
		}

		if ((r == 0 && g == 255 && b == 0))
		{
			SaveData();
			setPlayerPosX(_player->getPosX());
			setPlayerPosY(_player->getPosY() + 50);
			SOUNDMANAGER->stop("�ΰ���");
			SCENEMANAGER->changeScene("restaurantScene");
		}

		if ((r == 0 && g == 0 && b == 255))
		{
			SaveData();
			setPlayerPosX(_player->getPosX());
			setPlayerPosY(_player->getPosY() + 50);
			SOUNDMANAGER->stop("�ΰ���");
			SCENEMANAGER->changeScene("convenientScene");
		}

		if ((r == 0 && g == 255 && b == 255))
		{
			SaveData();
			setPlayerPosX(_player->getPosX());
			setPlayerPosY(_player->getPosY() + 50);
			SOUNDMANAGER->stop("�ΰ���");
			SCENEMANAGER->changeScene("sushiScene");
		}

		if ((r == 0 && g == 170 && b == 255))
		{
			SOUNDMANAGER->stop("�ΰ���");
			SCENEMANAGER->changeScene("bossScene");
		}
	}

	//�ȼ� �� �浹
	for (int i = _probePlayerBY; i < _probePlayerBY +1 ; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), _player->getPosX(), i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 255 && b == 0))
		{
			_player->setSpeedY(-2);
		}
	}
	//�ȼ� �Ʒ� �浹
	for (int i = _probePlayerBY; i < _probePlayerBY + 1; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), _player->getPosX(), i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 80 && g == 188 && b == 223))
		{
			_player->setSpeedY(-2);
		}
	}

	//�ȼ� ������ �浹
	for (int i = _probePlayerRX; i < _probePlayerRX + 1; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), i, _player->getPosY());

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 139 && g == 0 && b == 255))
		{
			_player->setSpeedX(0);
		}
	}

	//�ȼ� ������ �浹
	for (int i = _probePlayerLX - 1; i < _probePlayerLX; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), i, _player->getPosY());

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 50 && g == 50 && b == 50))
		{
			_player->setSpeedX(0);
		}
	}

}
