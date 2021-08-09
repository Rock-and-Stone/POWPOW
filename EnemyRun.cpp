#include "pch.h"
#include "EnemyRun.h"
#include "Enemy.h"

HRESULT EnemyRun::init()
{
	return S_OK;
}

void EnemyRun::release()
{
}

void EnemyRun::update()
{
	if (_enemy->ChaseSession())
	{
		_enemy->ChaseRun();
	}

	//지금이 어택이 가능한상태인가?
	if (_enemy->AttackSession())
	{
		_enemy->ChangeStatement();
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::ATTACK1);
	}
}
