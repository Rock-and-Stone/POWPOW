#include "pch.h"
#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::init()
{
   
	return S_OK;
}

void EnemyManager::release()
{

}

void EnemyManager::update()
{
    //·çÅ© º¤ÅÍ ¾÷µ«
    for (_viLuke = _vLuke.begin(); _viLuke != _vLuke.end(); ++_viLuke)
    {
        (*_viLuke)->update();
    }

    Collision();
}

void EnemyManager::render()
{
    for (_viLuke = _vLuke.begin(); _viLuke != _vLuke.end(); ++_viLuke)
    {
        RECT temp = (*_viLuke)->GetRect();
        (*_viLuke)->render();
    }
}

void EnemyManager::EnemyImageStorage()
{

}

void EnemyManager::SetLuke()
{
    for (int i = 0; i < 5; i++)
    {
        Enemy* luke;
        luke = new Luke;
        luke->SetCamera(_cm);
        luke->init("LUKE_IDLE", "LUKEleftIdle" , PointMake(800 * i + 800, 700));
        luke->init();
        luke->SetPlayerLink(_player);
        _vLuke.push_back(luke);
        RENDERMANAGER->addRender(luke);
    }
}

void EnemyManager::SetMike()
{
    for (int i = 0; i < 10; i++)
    {
        Enemy* mike;
        mike = new Mike;
        mike->SetCamera(_cm);
        mike->init("MIKE_IDLE", "MIKEleftIdle", PointMake(800 * i + 1000, 500));
        mike->init();
        mike->SetPlayerLink(_player);
        _vLuke.push_back(mike);
        RENDERMANAGER->addRender(mike);
    }
}

void EnemyManager::SetMalcolm()
{
    for (int i = 0; i < 10; i++)
    {
        Enemy* malcolm;
        malcolm = new Malcolm;
        malcolm->SetCamera(_cm);
        malcolm->init("MALCOLM_IDLE", "MALCOLMleftIdle", PointMake(800 * i + 1200, 800));
        malcolm->init();
        malcolm->SetPlayerLink(_player);
        _vLuke.push_back(malcolm);
        RENDERMANAGER->addRender(malcolm);
    }
}

void EnemyManager::Collision()
{
    for (int i = 0; i < _vLuke.size(); i++)
    {
        RECT temp;
        RECT playerRC = _player->getAttackRC();
        RECT enemyRC = _vLuke[i]->GetRect();

        if (IntersectRect(&temp, &playerRC, &enemyRC))
        {
            if (_player->getPosY() + 20 > _vLuke[i]->GetEnemyPosY() && _player->getPosY() -20 < _vLuke[i]->GetEnemyPosY())
            _vLuke[i]->HitDamage(10);
        }

        RECT temp2;
        RECT playerHitRC = _player->getHitRC();
        RECT enemyHitRC = _vLuke[i]->GetAttackRect();

        if (IntersectRect(&temp2, &playerHitRC, &enemyHitRC))
        {
            if (_player->getPosY() > _vLuke[i]->GetEnemyPosY() - 20 && _player->getPosY() < _vLuke[i]->GetEnemyPosY() + 20)
            _player->hitDamage(5);
        }

        if(_vLuke[i]->getReleased())
            _vLuke.erase(_vLuke.begin() + i);
    }


}



