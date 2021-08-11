#include "pch.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ���⿡�� �ض�!!!
HRESULT playGround::init()
{
	gameNode::init(true);

	SCENEMANAGER->addScene("stage1", new stage1);
	SCENEMANAGER->addScene("titleScene", new titleScene);
	SCENEMANAGER->addScene("selectScene", new SelectScene);
	SCENEMANAGER->addScene("loadingScene", new loadingScene);
	SCENEMANAGER->addScene("settingScene", new settingScene);
	SCENEMANAGER->addScene("bossScene", new bossScene);
	SCENEMANAGER->addScene("cafeScene", new cafeScene);
	SCENEMANAGER->addScene("convenientScene", new convenientScene);
	SCENEMANAGER->addScene("restaurantScene", new restaurantScene);
	SCENEMANAGER->addScene("sushiScene", new sushiScene);

	SCENEMANAGER->changeScene("titleScene");


	return S_OK;
}

//�޸� ������ ����� �ض�!!!!
void playGround::release()
{
	gameNode::release();
}

//����ó���� ����ٰ�!
void playGround::update()
{
	gameNode::update();
	SCENEMANAGER->update();
	EFFECTMANAGER->update();
	KEYANIMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("cafeScene");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("convenientScene");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("restaurantScene");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->changeScene("sushiScene");
	}
}

//����� �׷����!!!
void playGround::render()
{
	if (!SCENEMANAGER->GetVideoPlay())
	{
		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		//==============������ ���� �ǵ帮�� ���� ============

		SCENEMANAGER->render();
		EFFECTMANAGER->render();

		//=============== �ؿ��� �ǵ������� ================
		_backBuffer->render(getHDC(), 0, 0);
	}

}



