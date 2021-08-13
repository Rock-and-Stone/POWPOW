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

	_bossDirection = leftIdle;

	_bossX = WINSIZEX- 300;
	_bossY = WINSIZEY/2;
	_bossRc = RectMakeCenter(_bossX, _bossY, 100, 100);

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
	_bossRc = RectMakeCenter(_bossX + 185, _bossY+ 200, 80, 130);
}

void boss::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _bossRc);
	}
	_bossImg->aniRender(getMemDC(), _bossX, _bossY, _bossAnim);
}
