#include "pch.h"
#include "lCoin.h"

HRESULT lCoin::init()
{
    _value = 100;
    return S_OK;
}

void lCoin::release()
{
}

void lCoin::update()
{
    Object::update();
}

void lCoin::SwitchImage()
{
}
