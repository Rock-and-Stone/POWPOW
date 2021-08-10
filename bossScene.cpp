#include "pch.h"
#include "bossScene.h"

HRESULT bossScene::init()
{
	_bossBackground = IMAGEMANAGER->addImage("bossBackground","source/Level 1 - Boss Room.bmp", WINSIZEX, WINSIZEY,true, MAGENTA);

#pragma region 인트로 동영상 이닛
	_bossIntro = MCIWndCreate(_hWnd, NULL, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, "source/Bossintro.wmv");
	MoveWindow(_bossIntro, 0, 0, WINSIZEX, WINSIZEY, NULL);
	MCIWndPlay(_bossIntro);
	SCENEMANAGER->SetVideoPlay(true);
#pragma endregion


	return S_OK;
}

void bossScene::update()
{

#pragma region 동영상 스킵 및 삭제
	if (MCIWndGetLength(_bossIntro) <= MCIWndGetPosition(_bossIntro))
	{
		MCIWndDestroy(_bossIntro);
		SCENEMANAGER->SetVideoPlay(false);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{

		if (SCENEMANAGER->GetVideoPlay())
		{
			MCIWndDestroy(_bossIntro);
			SCENEMANAGER->SetVideoPlay(false);
		}
	}
#pragma endregion

}

void bossScene::release()
{
}

void bossScene::render()
{
	_bossBackground->render(getMemDC());
}
