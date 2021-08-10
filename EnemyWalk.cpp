#include "pch.h"
#include "EnemyWalk.h"
#include "Enemy.h"

HRESULT EnemyWalk::init()
{
	//카운트 랜덤으로 주기
	_count = RND->getInt(2);
	return S_OK;
}

void EnemyWalk::release()
{
}

void EnemyWalk::update()
{
	if (_enemy->WalkSession())
	{
		_enemy->ChaseWalk();
	}

	//지금이 어택이 가능한상태인가?
	if (_enemy->AttackSession())
	{
		if (_count == 0)
		{
			_enemy->ChangeStatement();
			_enemy->SetEnemyStatement(ENEMYSTATEMENT::ATTACK1);
		}
		if (_count == 1)
		{
			_enemy->ChangeStatement();
			_enemy->SetEnemyStatement(ENEMYSTATEMENT::ATTACK3);
		}
	}
}

