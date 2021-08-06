#include "pch.h"
#include "EnemyIdle.h"
#include "Enemy.h"

HRESULT EnemyIdle::init()
{

	return S_OK;
}

void EnemyIdle::release()
{
}

void EnemyIdle::update()
{
	if (_enemy->ChaseSession())
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::WALK);

		_enemy->ChangeStatement();

	}
}
