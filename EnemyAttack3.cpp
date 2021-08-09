#include "pch.h"
#include "EnemyAttack3.h"
#include "Enemy.h"

HRESULT EnemyAttack3::init()
{
	return S_OK;
}

void EnemyAttack3::release()
{
}

void EnemyAttack3::update()
{
	if (_enemy->GetMotionName()->GetNowPlayIdx() == 6)
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::ATTACK4);
		_enemy->ChangeStatement();
	}
}
