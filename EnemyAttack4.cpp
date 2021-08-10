#include "pch.h"
#include "EnemyAttack4.h"
#include "Enemy.h"

HRESULT EnemyAttack4::init()
{
	_enemy->ComboSession();
	return S_OK;
}

void EnemyAttack4::release()
{
}

void EnemyAttack4::update()
{
	if (_enemy->GetMotionName()->GetNowPlayIdx() == 6)
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::DAEGI);
		_enemy->ChangeStatement();
	}
}
