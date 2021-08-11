#include "pch.h"
#include "ObjectManager.h"

HRESULT ObjectManager::init()
{

	return S_OK;
}

void ObjectManager::release()
{
}

void ObjectManager::update()
{
    for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
    {
        (*_viObject)->update();

    }
}

void ObjectManager::render()
{
    for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
    {
        RECT temp = (*_viObject)->GetRect();
        (*_viObject)->render();

    }
}

void ObjectManager::SetBat()
{
    for (int i = 0; i < 10; i++)
    {
        Object* bat;
        bat = new Bat;
        bat->SetCamera(_cm);
        bat->init("bat_left_atk", "bat_left_atk", PointMake(1000 * i + 900, 500));
        bat->SetPlayerLink(_player);
        _vObject.push_back(bat);
        RENDERMANAGER->addRender(bat);
    }
}
