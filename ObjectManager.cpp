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
        bat->init("bat_left_neutral", "bat_left_neutral", PointMake(1000 * i + 900, 500));
        bat->SetPlayerLink(_player);
        _vObject.push_back(bat);
        RENDERMANAGER->addRender(bat);
    }
}

void ObjectManager::SetTrash()
{
    for (int i = 0; i < 10; i++)
    {
        Object* trash;
        trash = new Trash;
        trash->SetCamera(_cm);
        trash->init("trash_left_neutral", "trash_left_neutral", PointMake(1000 * i + 850, 600));
        trash->SetPlayerLink(_player);
        _vObject.push_back(trash);
        RENDERMANAGER->addRender(trash);
    }
}
