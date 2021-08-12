#include "pch.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기에다 해라!!!
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

//메모리 해제는 여기다 해라!!!!
void playGround::release()
{
	gameNode::release();
}

//연산처리는 여기다가!
void playGround::update()
{
	gameNode::update();
	SCENEMANAGER->update();
	EFFECTMANAGER->update();
	KEYANIMANAGER->update();

	
}

//여기다 그려줘라!!!
void playGround::render()
{
	if (!SCENEMANAGER->GetVideoPlay())
	{
		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		//==============위에는 제발 건드리지 마라 ============

		SCENEMANAGER->render();
		EFFECTMANAGER->render();

		//=============== 밑에도 건들지마라 ================
		_backBuffer->render(getHDC(), 0, 0);
	}

}



