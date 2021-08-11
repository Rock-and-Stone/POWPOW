#include "pch.h"
#include "settingScene.h"

HRESULT settingScene::init()
{
	IMAGEMANAGER->addImage("settingSceneBox", "source/settingSceneBox.bmp", 250, 50, true, RGB(255, 0, 255));

	_selectNum = 0;

	_rc = RectMake(190, 163 + (_selectNum * 67), 250, 50);
	_BGMbar = new volumeProgressBar;
	_BGMbar->init(300, 400, 400, 100);
	_BGMbar->setGauge(_currentBGMVolume, 1.0f);

	_SFXbar = new volumeProgressBar;
	_SFXbar->init(300, 600, 400, 100);
	_SFXbar->setGauge(_currentSFXVolume, 1.0f);

	_currentBGMVolume = getBGMVolume() / 10;
	_currentSFXVolume = getSFXVolume() / 10;

	return S_OK;
}

void settingScene::release()
{
}

void settingScene::update()
{
	

	//background music - volume update
	SOUNDMANAGER->setVolume("menuBGM", _currentBGMVolume);

	_BGMbar->setGauge(_currentBGMVolume, 1.0f);
	_BGMbar->update();

	_SFXbar->setGauge(_currentSFXVolume, 1.0f);
	_SFXbar->update();

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) 
	{ 
		SCENEMANAGER->changeScene("selectScene");

		setBGMVolume(_currentBGMVolume * 10);
		setSFXVolume(_currentSFXVolume * 10);
	}



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
			_currentBGMVolume-=0.1f;


			if (_currentBGMVolume <= 0)
			{
				_currentBGMVolume = 0;
			}


		}
		else if (_selectNum == 1) 
		{
			_currentSFXVolume -= 0.1f;

			if (_currentSFXVolume <= 0)
			{
				_currentSFXVolume = 0;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_selectNum == 0) 
		{
			_currentBGMVolume += 0.1f;
			if (_currentBGMVolume >= 1)
			{
				_currentBGMVolume = 1;
			}
		}
		else if (_selectNum == 1) 
		{
			_currentSFXVolume += 0.1f;
			if (_currentSFXVolume > 1)
			{
				_currentSFXVolume = 1;
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
