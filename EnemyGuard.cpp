#include "pch.h"
#include "EnemyGuard.h"
#include "Enemy.h"

HRESULT EnemyGuard::init()
{
	
	if (_enemy->GetEnemyDirection() == 0)
	{
		EFFECTMANAGER->play("defenseEffect1", _enemy->GetEnemyRendX() - 20, _enemy->GetEnemyRendY());
	}
	if (_enemy->GetEnemyDirection() == 1)
	{
		EFFECTMANAGER->play("defenseEffect1", _enemy->GetEnemyRendX() + 20, _enemy->GetEnemyRendY());
	}
	
	return S_OK;
}

void EnemyGuard::release()
{
}

void EnemyGuard::update()
{
	if (_enemy->GetMotionName()->GetNowPlayIdx() == 2)
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::DAEGI);
		_enemy->ChangeStatement();
	}
}
