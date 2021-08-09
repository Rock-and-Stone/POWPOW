#include "pch.h"
#include "settingScene.h"

HRESULT settingScene::init()
{


	IMAGEMANAGER->addImage("settingSceneBox", "source/settingSceneBox.bmp", 250, 50, true, RGB(255, 0, 255));

	_selectNum = 0;
	_rc = RectMake(190, 163 + (_selectNum * 67), 250, 50);

	_BGMbar = new volumeProgressBar;
	_BGMbar->init(300, 400, 400, 100);
	_BGMbar->setGauge(getBGMVolume(), 1.0f);

	_SFXbar = new volumeProgressBar;
	_SFXbar->init(300, 600, 400, 100);
	_SFXbar->setGauge(getSFXVolume(), 1.0f);

	return S_OK;
}

void settingScene::release()
{
}

void settingScene::update()
{
	_BGMbar->setGauge(getBGMVolume(), 1.0f);
	_BGMbar->update();

	_SFXbar->setGauge(getSFXVolume(), 1.0f);
	_SFXbar->update();

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) 
	{ 
		SCENEMANAGER->changeScene("selectScene");
	}


	//background music - volume update
	SOUNDMANAGER->setVolume("menuBGM", getBGMVolume());
	

	if (KEYMANAGER->isOnceKeyDown(VK_UP)) 
	{
		_selectNum--;
		if (_selectNum < 0)
		{
			_selectNum = 1;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) 
	{
		_selectNum++;
		if (_selectNum > 1)
		{
			_selectNum = 0;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_selectNum == 0) 
		{
			setBGMVolutme(getBGMVolume()-0.1f);

	

			if (getBGMVolume() <= 0) 
			{
				setBGMVolutme(0);
			}


		}
		else if (_selectNum == 1) 
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
		if (_selectNum == 0) 
		{
			setBGMVolutme(getBGMVolume() + 0.1f);
			if (getBGMVolume() >= 1)
			{
				setBGMVolutme(1);
			}
		}
		else if (_selectNum == 1) 
		{
			setSFXVolume(getSFXVolume() + 0.1f);
			if (getSFXVolume() > 1)
			{
				setSFXVolume(1);
			}
		}
	}
	_rc = RectMake(190, 163 + (_selectNum * 67), 250, 50);
}

void settingScene::render()
{
	
	IMAGEMANAGER->findImage("settingBackGround")->render(getMemDC());

	IMAGEMANAGER->findImage("settingSceneBox")->render(getMemDC(),  _rc.left, _rc.top);

	_BGMbar->render();
	_SFXbar->render();
}
