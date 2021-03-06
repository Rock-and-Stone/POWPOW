#include "pch.h"
#include "SelectScene.h"

HRESULT SelectScene::init()
{
	_selectNum = 0;

	_selectRc = RectMake(WINSIZEX / 2, WINSIZEY / 2 + (_selectNum * 90) + 30, 200, 50);

	return S_OK;
}

void SelectScene::update()
{
	_selectRc = RectMake(WINSIZEX / 2, WINSIZEY / 2 + (_selectNum * 90) + 30, 200, 50);

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_selectNum--;
		if (_selectNum < 0)
		{
			_selectNum = 2;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
		_selectNum++;
		if (_selectNum > 2) 
		{
			_selectNum = 0;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
	
			switch (_selectNum)
			{
			case 0:

				SaveData(100, 100, 0);
				SCENEMANAGER->changeScene("stage1");
				SOUNDMANAGER->stop("menuBGM");
			

				break;


			case 1:
				SCENEMANAGER->changeScene("settingScene");
				break;

			case 2:
				PostQuitMessage(0);
				break;
			}
	}
}

void SelectScene::release()
{
}

void SelectScene::render()
{
		IMAGEMANAGER->findImage("mainMenu")->render(getMemDC());
		IMAGEMANAGER->findImage("mainMenubox")->render(getMemDC(), _selectRc.left, _selectRc.top);
}
