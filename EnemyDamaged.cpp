#include "pch.h"
#include "EnemyDamaged.h"
#include "Enemy.h"

HRESULT EnemyDamaged::init()
{

	return S_OK;
}

void EnemyDamaged::release()
{

}

void EnemyDamaged::update()
{
	if (_enemy->GetMotionName()->GetNowPlayIdx() == 4)
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::DAEGI);
		_enemy->ChangeStatement();
	}
}
