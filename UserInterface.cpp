#include "pch.h"
#include "UserInterface.h"

HRESULT UserInterface::init()
{

	
	IMAGEMANAGER->addFrameImage("hpNum", "source/hp_number.bmp", 140, 15, 10, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("gpNum", "source/gp_number.bmp", 140, 15, 10, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("coinNum", "source/coin_number.bmp", 140, 15, 10, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("player1UI", "source/player1.bmp", 150, 130, true, MAGENTA);
	IMAGEMANAGER->addImage("player2UI", "source/player2.bmp", 150, 130, true, MAGENTA);
	IMAGEMANAGER->addImage("ingameSetting", "source/ingamesetting.bmp", 400, 225, true, MAGENTA);
	IMAGEMANAGER->addImage("ingameSettingBox","source/ingamesettingSceneBox.bmp", 125, 25, true, MAGENTA);

	_hp100 = IMAGEMANAGER->findImage("hpNum");
	_hp10 = IMAGEMANAGER->findImage("hpNum");
	_hp1 = IMAGEMANAGER->findImage("hpNum");

	_gp100 = IMAGEMANAGER->findImage("gpNum");
	_gp10 = IMAGEMANAGER->findImage("gpNum");
	_gp1 = IMAGEMANAGER->findImage("gpNum");

	_coin100 = IMAGEMANAGER->findImage("coinNum");
	_coin10 = IMAGEMANAGER->findImage("coinNum");
	_coin1 = IMAGEMANAGER->findImage("coinNum");

	_option = IMAGEMANAGER->addImage("option", "source/pause.bmp", 236, 200, true, MAGENTA);
	_ingameSettingImg = IMAGEMANAGER->findImage("ingameSetting");
	_intgameSettingBox = IMAGEMANAGER->findImage("ingameSettingBox");

	_selectNum = 0;
	_volumeSelectNum = 0;
	_isPause = false;
	_ingameSetting = false;

	_selectRc = RectMake(WINSIZEX / 2, WINSIZEY / 2 + (_selectNum * 90) + 50, 200, 50);

	_BGMbar = new volumeProgressBar;
	_BGMbar->init(300, 400, 400, 100);
	_BGMbar->setGauge(getBGMVolume(), 1.0f);

	_SFXbar = new volumeProgressBar;
	_SFXbar->init(300, 600, 400, 100);
	_SFXbar->setGauge(getSFXVolume(), 1.0f);

	return S_OK;
}

void UserInterface::release()
{
}

void UserInterface::update()
{

	_BGMbar->setGauge(getBGMVolume(), 1.0f);
	_BGMbar->update();

	_SFXbar->setGauge(getSFXVolume(), 1.0f);
	_SFXbar->update();


	SOUNDMANAGER->setVolume("menuBGM", getBGMVolume());


	if(_isPause&& !_ingameSetting) _selectRc = RectMake(WINSIZEX / 2, WINSIZEY / 2 + (_selectNum * 90) + 50, 200, 50);

	else if(_ingameSetting) _selectRc = RectMake(WINSIZEX / 2, WINSIZEY / 2 + (_volumeSelectNum * 90) + 50, 200, 50);

	if (KEYMANAGER->isOnceKeyDown('O') && !_ingameSetting)
	{
		if (!_isPause) _isPause = true;
		else  _isPause = false;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (_isPause && !_ingameSetting)
		{
			switch (_selectNum)
			{
			case 0:
				_isPause = false;
				break;

			case 1:
				_ingameSetting = true;
				break;

			case 2:
				PostQuitMessage(0);
				break;
			}
		}

		else if (_ingameSetting)
		{
			_ingameSetting = false;
		}
	}


	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_selectNum--;
		_volumeSelectNum--;
		if (_selectNum < 0)
		{
			_selectNum = 2;
		}
		if (_volumeSelectNum < 0)
		{
			_volumeSelectNum = 1;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_selectNum++;
		_volumeSelectNum++;

		if (_selectNum > 2)
		{
			_selectNum = 0;
		}
		if (_volumeSelectNum > 1)
		{
			_volumeSelectNum = 0;
		}
	}

	if (_ingameSetting )
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_volumeSelectNum == 0)
			{
				setBGMVolutme(getBGMVolume() - 0.1f);



				if (getBGMVolume() <= 0)
				{
					setBGMVolutme(0);
				}


			}
			else if (_volumeSelectNum == 1)
			{
				setSFXVolume(getSFXVolume() - 0.1f);

				if (getSFXVolume() <= 0)
				{
					setSFXVolume(0);
				}
			}


		}

		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{

			if (_volumeSelectNum == 0)
			{
				setBGMVolutme(getBGMVolume() + 0.1f);
				if (getBGMVolume() >= 1)
				{
					setBGMVolutme(1);
				}
			}
			else if (_volumeSelectNum == 1)
			{
				setSFXVolume(getSFXVolume() + 0.1f);
				if (getSFXVolume() > 1)
				{
					setSFXVolume(1);
				}
			}
		}
	}

}

void UserInterface::render()
{
	IMAGEMANAGER->findImage("player1UI")->render(getMemDC(), 20, 20);

	_hp100->frameRender(getMemDC(), 95, 63, getPlayerHP() / 100 , 0);
	_hp10->frameRender(getMemDC(), 110, 63, getPlayerHP() % 100 /10,0);
	_hp1->frameRender(getMemDC(), 125, 63, getPlayerHP() % 10,0);

	_gp100->frameRender(getMemDC(), 95, 84, getPlayerGP() / 100, 0);
	_gp10->frameRender(getMemDC(), 110, 84, getPlayerGP() % 100 / 10, 0);
	_gp1->frameRender(getMemDC(), 125, 84, getPlayerGP() % 10, 0);

	_coin100->frameRender(getMemDC(), 95, 104, getCoin() / 100, 0);
	_coin10->frameRender(getMemDC(), 110, 104, getCoin() % 100 / 10, 0);
	_coin1->frameRender(getMemDC(), 125, 104, getCoin() % 10, 0);

	if (_isPause && !_ingameSetting)
	{
		_option->render(getMemDC() , WINSIZEX /2 - _option->getWidth()/2 , WINSIZEY /2 - _option->getHeight()/2);

		_intgameSettingBox->render(getMemDC(), _selectRc.left, _selectRc.top);

	}

	else if (_ingameSetting)
	{
		_ingameSettingImg->render(getMemDC(), WINSIZEX / 2 - _ingameSettingImg->getWidth() / 2, WINSIZEY / 2 - _ingameSettingImg->getHeight() / 2);
		_intgameSettingBox->render(getMemDC(), _selectRc.left, _selectRc.top);

		_BGMbar->render();
		_SFXbar->render();
	}

}
