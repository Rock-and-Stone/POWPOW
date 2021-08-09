#include "pch.h"
#include "EnemyJump.h"
#include "Enemy.h"

HRESULT EnemyJump::init()
{
	_saveJump = _enemy->GetEnemyPosY();
	_enemy->SetJumpPower(8.0f);
	_enemy->SetIsAir(true);
	
	return S_OK;
}

void EnemyJump::release()
{
}

void EnemyJump::update()
{
	
	if (_enemy->GetMotionName()->GetNowPlayIdx() == 4)
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::FALL);
		_enemy->ChangeStatement();
	}
}
