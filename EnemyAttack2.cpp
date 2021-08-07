#include "pch.h"
#include "EnemyAttack2.h"
#include "Enemy.h"

HRESULT EnemyAttack2::init()
{
	return S_OK;
}

void EnemyAttack2::release()
{
}

void EnemyAttack2::update()
{
	if (_enemy->GetEnemyMotion()->GetNowPlayIdx() == 3)
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::DAEGI);
		_enemy->ChangeStatement();
	}
}
