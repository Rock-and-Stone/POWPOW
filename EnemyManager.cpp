#include "pch.h"
#include "EnemyManager.h"
#include "ObjectManager.h"
#include "Enemy.h"

HRESULT EnemyManager::init()
{
    _enemyCount = 0;
	return S_OK;
}

void EnemyManager::release()
{

}

void EnemyManager::update()
{
    //·çÅ© º¤ÅÍ ¾÷µ«
    for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
    {
        (*_viEnemy)->update();
    }

    Collision();
}

void EnemyManager::render()
{
    int i = 0;
    char str[256];

    for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
    {
        i++;
        (*_viEnemy)->render();
    }
    _enemyCount = i;
}


void EnemyManager::SetLuke(POINT pos)
{
        Enemy* luke;
        luke = new Luke;
        luke->SetCamera(_cm);
        luke->init("LUKE_IDLE", "LUKEleftIdle" , pos);
        luke->init();
        luke->SetPlayerLink(_player);
        _vEnemy.push_back(luke);
        RENDERMANAGER->addRender(luke);
}

void EnemyManager::SetMike(POINT pos)
{
        Enemy* mike;
        mike = new Mike;
        mike->SetCamera(_cm);
        mike->init("MIKE_IDLE", "MIKEleftIdle", pos);
        mike->init();
        mike->SetPlayerLink(_player);
        _vEnemy.push_back(mike);
        RENDERMANAGER->addRender(mike);
}

void EnemyManager::SetMalcolm(POINT pos)
{
        Enemy* malcolm;
        malcolm = new Malcolm;
        malcolm->SetCamera(_cm);
        malcolm->init("MALCOLM_IDLE", "MALCOLMleftIdle", pos);
        malcolm->init();
        malcolm->SetPlayerLink(_player);
        _vEnemy.push_back(malcolm);
        RENDERMANAGER->addRender(malcolm);
}

void EnemyManager::SpawnEnemy(int lukeNum, int mikeNum, int malcolmNum, int currentstage)
{
    int rnd;
    POINT position;
    position.y = RND->getFromIntTo(500, 700);

    for (int i = 0; i < lukeNum; i++)
    {
        rnd = RND->getInt(2);
        position.x = currentstage * 3000 + 100 + rnd * 1800;
        SetLuke(position);
    }

    for (int j = 0; j < mikeNum; j++)
    {
        rnd = RND->getInt(2);
        position.x = currentstage * 3000 + 100 + rnd * 1800;
        SetMike(position);
    }

    for (int k = 0; k < malcolmNum; k++)
    {
        rnd = RND->getInt(2);
        position.x = currentstage * 3000 + 100 + rnd * 1800;
        SetMalcolm(position);
    }
}

void EnemyManager::Collision()
{
    for (int i = 0; i < _vEnemy.size(); i++)
    {
        RECT temp;
        RECT playerRC = _player->getAttackRC();
        RECT enemyRC = _vEnemy[i]->GetRect();

        if (IntersectRect(&temp, &playerRC, &enemyRC))
        {
            if (_player->getPosY() + 20 > _vEnemy[i]->GetEnemyPosY() && _player->getPosY() -20 < _vEnemy[i]->GetEnemyPosY())
            _vEnemy[i]->HitDamage(10);
        }

        RECT temp2;
        RECT playerHitRC = _player->getHitRC();
        RECT enemyHitRC = _vEnemy[i]->GetAttackRect();

        if (IntersectRect(&temp2, &playerHitRC, &enemyHitRC))
        {
            if (_player->getPosY() > _vEnemy[i]->GetEnemyPosY() - 20 && _player->getPosY() < _vEnemy[i]->GetEnemyPosY() + 20)
            _player->hitDamage(5);
        }

        if(_vEnemy[i]->getReleased())
        {
            _om->addCoin(_vEnemy[i]->GetEnemyPosX(), _vEnemy[i]->GetEnemyPosY());
            _vEnemy.erase(_vEnemy.begin() + i);
        }
    }
}



