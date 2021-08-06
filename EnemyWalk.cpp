#include "pch.h"
#include "EnemyWalk.h"
#include "Enemy.h"

HRESULT EnemyWalk::init()
{
	//스피드값
	return S_OK;
}

void EnemyWalk::release()
{
}

void EnemyWalk::update()
{
	//지금이 어택이 가능한상태인가?
	if (_enemy->AttackSession())
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::ATTACK1);
		_enemy->ChangeStatement();
	}
}
