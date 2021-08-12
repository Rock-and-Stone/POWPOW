#include "pch.h"
#include "ObjectManager.h"
#include "EnemyManager.h"

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

    for (_viCoin = _vCoin.begin(); _viCoin != _vCoin.end(); ++_viCoin)
    {
        (*_viCoin)->update();

    }
}

void ObjectManager::render()
{
    for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
    {
        RECT temp = (*_viObject)->GetRect();
        (*_viObject)->render();

    }
    for (_viCoin = _vCoin.begin(); _viCoin != _vCoin.end(); ++_viCoin)
    {
        RECT temp = (*_viCoin)->GetRect();
        (*_viCoin)->render();
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

void ObjectManager::SetsCoin()
{
    for (int j = 0; j < _em->GetVLuke().size(); ++j)
    {
        for (int i = 0; i < 5; i++)
        {
            Object* scoin;
            scoin = new sCoin;
            scoin->SetCamera(_cm);
            scoin->init("smallCoin", "smallCoin", PointMake(_em->GetVLuke()[j]->GetEnemyPosX() - 10 + i*5, _em->GetVLuke()[j]->GetEnemyPosY()));
            scoin->SetPlayerLink(_player);
            _vCoin.push_back(scoin);
            RENDERMANAGER->addRender(scoin);
        }
    }
}
