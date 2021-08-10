#include "pch.h"
#include "volumeProgressBar.h"


volumeProgressBar::volumeProgressBar()
{
}


volumeProgressBar::~volumeProgressBar()
{
}

HRESULT volumeProgressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarTop = IMAGEMANAGER->findImage("volumeBackBar");
	_progressBarBottom = IMAGEMANAGER->findImage("volumeFrontBar");

	_width = _progressBarTop->getWidth();


	return S_OK;
}

void volumeProgressBar::release()
{
}

void volumeProgressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarTop->getWidth(),
		_progressBarTop->getHeight());
}

void volumeProgressBar::render()
{

	IMAGEMANAGER->render("volumeFrontBar", getMemDC(),
		_rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_width, _progressBarBottom->getHeight());

	IMAGEMANAGER->render("volumeBackBar", getMemDC(),
		_rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

}

//게이지 조절하는 함수
void volumeProgressBar::setGauge(float currentGauge, float maxGauge)
{
		_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
}
