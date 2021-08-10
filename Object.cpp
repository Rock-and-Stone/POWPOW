#include "pch.h"
#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

HRESULT Object::init()
{
    return S_OK;
}

HRESULT Object::init(const char* imageName, const char* animationName, POINT position)
{
    _imageName = IMAGEMANAGER->findImage(imageName);

    _motionName = KEYANIMANAGER->findAnimation(animationName);
    _motionName->GetNowPlayIdx();

    _posX = position.x;
    _posY = position.y;

    _motionName->start();

    return S_OK;
}

void Object::release()
{
}

void Object::update()
{
   
}

void Object::render()
{
    Draw();
}

void Object::Draw()
{
    _rendX = _posX - _cm->getCamX();
    _rendY = _posY - _cm->getCamY();

    _rc = RectMakeCenter(_rendX, _rendY, _imageName->getFrameWidth(), _imageName->getFrameHeight());
    _collideRect = RectMakeCenter(_rendX, _rendY, 20, 20);

    _imageName->aniRender(getMemDC(), _rc.left, _rc.top, _motionName);
}
