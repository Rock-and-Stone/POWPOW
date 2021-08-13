#include "pch.h"
#include "sCoin.h"

HRESULT sCoin::init()
{
    _value = 10;
    return S_OK;
}

void sCoin::release()
{
}

void sCoin::update()
{
    Object::update();
}

void sCoin::SwitchImage()
{
}
