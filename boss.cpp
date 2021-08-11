#include "pch.h"
#include "boss.h"

boss::boss()
{
	
}

boss::~boss()
{
}

HRESULT boss::init()
{
	_bossState = new bossState;

	_bossDirection = BOSSDIRECTION::leftIdle;

	_bossX = WINSIZEX- 300;
	_bossY = WINSIZEY/2;
	_bossRc = RectMakeCenter(_bossX, _bossY, 500, 500);

	_bossImg = IMAGEMANAGER->findImage("BOSS IDLE");
	_bossAnim = KEYANIMANAGER->findAnimation("bossLeftIdle");

	_bossAnim->start();

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	_bossRc = RectMakeCenter(_bossX, _bossY, 500, 500);
}

void boss::render()
{
	_bossImg->aniRender(getMemDC(), _bossRc.left, _bossRc.top, _bossAnim);

	//Rectangle(getMemDC(), _bossRc);
}
