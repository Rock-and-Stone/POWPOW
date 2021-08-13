#include "pch.h"
#include "mCoin.h"

HRESULT mCoin::init()
{
    _value = 50;
    return S_OK;
}

void mCoin::release()
{
}

void mCoin::update()
{
    Object::update();
}

void mCoin::SwitchImage()
{
}
