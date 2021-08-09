#include "pch.h"
#include "EnemyDaegi.h"
#include "Enemy.h"

HRESULT EnemyDaegi::init()
{
	_countSelect = RND->getFromIntTo(150, 200);
	return S_OK;
}

void EnemyDaegi::release()
{
}

void EnemyDaegi::update()
{
	_count++;

	if (_countSelect == _count)
	{
		_count = 0;
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::WALK);
		_enemy->ChangeStatement();
	}
	
}
