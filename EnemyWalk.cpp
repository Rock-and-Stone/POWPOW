#include "pch.h"
#include "EnemyWalk.h"
#include "Enemy.h"

HRESULT EnemyWalk::init()
{
	//ī��Ʈ �������� �ֱ�
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

	//������ ������ �����ѻ����ΰ�?
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

