#include "pch.h"
#include "ingameProgress.h"



ingameProgress::ingameProgress()
{
}


ingameProgress::~ingameProgress()
{
}

HRESULT ingameProgress::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarTop = IMAGEMANAGER->addImage("involumeBackBar", "source/ingamevolumnBackBar.bmp", width, height, true, RGB(255, 0, 255));
	_progressBarBottom = IMAGEMANAGER->addImage("involumeFrontBar", "source/ingamevolumnFrontBar.bmp", width, height, true, RGB(255, 0, 255));


	_width = _progressBarTop->getWidth();

	return S_OK;
}

void ingameProgress::release()
{
}

void ingameProgress::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarTop->getWidth(), _progressBarTop->getHeight());
}

void ingameProgress::render()
{

	IMAGEMANAGER->render("involumeFrontBar", getMemDC(),
		_rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_width, _progressBarBottom->getHeight());

	IMAGEMANAGER->render("involumeBackBar", getMemDC(),
		_rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

}

//게이지 조절하는 함수
void ingameProgress::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
}
