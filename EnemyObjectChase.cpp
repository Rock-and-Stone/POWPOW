#include "pch.h"
#include "EnemyObjectGrab.h"
#include "Enemy.h"

HRESULT EnemyObjectGrab::init()
{
    return S_OK;
}

void EnemyObjectGrab::release()
{
}

void EnemyObjectGrab::update()
{
    if (_enemy->ObjectSession())
    {
        _enemy->ChaseObject();
    }
}
