#include "pch.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "Object.h"

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
    CoinCollision();
    
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
  
}

void ObjectManager::CoinCollision()
{
    RECT temp;
    for (int i = 0; i < _vCoin.size(); i++)
    {
        RECT temp2;
        RECT playerHitRC = _player->getHitRC();
        RECT coinRC = _vCoin[i]->GetRect();
        if (IntersectRect(&temp, &playerHitRC, &coinRC))
        {
            _player->coinGet(_vCoin[i]->GetCoin());
            SOUNDMANAGER->play("µ¿Àü¸Ô±â", getBGMVolume() / 10);
            _vCoin[i]->SetReleased(true);
            removeCoin(i);
        }
    }
}

void ObjectManager::addCoin(float x, float y)
{
    for (int i = 0; i < 5; i++)
    {
        Object* scoin;
        scoin = new sCoin;
        scoin->SetCamera(_cm);
        scoin->init("smallCoin", "smallCoin", PointMake(x + RND->getFromIntTo(-30, 30), y + RND->getFromIntTo(-30, 30)));
        scoin->init();
        scoin->SetPlayerLink(_player);
        RENDERMANAGER->addRender(scoin);
        _vCoin.push_back(scoin);
    }
   
    for (int i = 0; i < 3; i++)
    {
        Object* mcoin;
        mcoin = new mCoin;
        mcoin->SetCamera(_cm);
        mcoin->init("mediumCoin", "mediumCoin", PointMake(x + RND->getFromIntTo(-30, 30), y + RND->getFromIntTo(-30, 30)));
        mcoin->init();
        mcoin->SetPlayerLink(_player);
        RENDERMANAGER->addRender(mcoin);
        _vCoin.push_back(mcoin);
    }
    

    Object* lcoin;
    lcoin = new sCoin;
    lcoin->SetCamera(_cm);
    lcoin->init("largeCoin", "largeCoin", PointMake(x + RND->getFromIntTo(-30, 30), y + RND->getFromIntTo(-30, 30)));
    lcoin->init();
    lcoin->SetPlayerLink(_player);
    RENDERMANAGER->addRender(lcoin);
    _vCoin.push_back(lcoin);
}

void ObjectManager::removeCoin(int arrNum)
{
    _vCoin.erase(_vCoin.begin() + arrNum);
}
