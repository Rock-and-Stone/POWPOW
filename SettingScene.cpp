#include "pch.h"
#include "settingScene.h"

HRESULT settingScene::init()
{
	_backgroundVolume = IMAGEMANAGER->findImage("volumnFrontBar");
	_SFXvolume = IMAGEMANAGER->findImage("volumnFrontBar");

	IMAGEMANAGER->addImage("settingSceneBox", "source/settingSceneBox.bmp", 250, 50, true, RGB(255, 0, 255));


	_selectNum = 0;
	_rc = RectMake(190, 163 + (_selectNum * 67), 250, 50);
	return S_OK;
}

void settingScene::release()
{
}

void settingScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) SCENEMANAGER->changeScene("selectScene");

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
			setSFXVolume(getSFXVolume() + 1);
			if (getSFXVolume() > 100)
			{
				setSFXVolume(100);
			}
		}
	}
	_rc = RectMake(190, 163 + (_selectNum * 67), 250, 50);
}

void settingScene::render()
{
	IMAGEMANAGER->findImage("settingBackGround")->render(getMemDC());


	IMAGEMANAGER->findImage("settingSceneBox")->render(getMemDC(),  _rc.left, _rc.top);
	//volume »ö
	_backgroundVolume->render(getMemDC(), 499, 164, 0, 0, (int)(160.0f * (getBGMVolume() / 100.0f)), 40);
	_SFXvolume->render(getMemDC(), 499, 238, 0, 0, (int)(160.0f * (getBGMVolume() / 100.0f)), 40);
	//volume Bar
	IMAGEMANAGER->findImage("volumnBackBar")->render(getMemDC(), 489, 159);
	IMAGEMANAGER->findImage("volumnBackBar")->render(getMemDC(), 489, 233);

}
