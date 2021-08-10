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
}
