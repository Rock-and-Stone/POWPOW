#include "pch.h"
#include "EnemyWalk.h"
#include "Enemy.h"

HRESULT EnemyWalk::init()
{
	//���ǵ尪
	return S_OK;
}

void EnemyWalk::release()
{
}

void EnemyWalk::update()
{
	//������ ������ �����ѻ����ΰ�?
	if (_enemy->AttackSession())
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::ATTACK1);
		_enemy->ChangeStatement();
	}
}
