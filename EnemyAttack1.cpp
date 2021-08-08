#include "pch.h"
#include "EnemyAttack1.h"
#include "Enemy.h"

HRESULT EnemyAttack1::init()
{
	return S_OK;
}

void EnemyAttack1::release()
{
}

void EnemyAttack1::update()
{
	if (_enemy->GetEnemyMotion()->GetNowPlayIdx() == 3)
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::ATTACK2);
		_enemy->ChangeStatement();
	}
}
