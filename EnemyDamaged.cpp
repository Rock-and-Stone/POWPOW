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


	if (_enemy->GetEnemyMotion()->GetNowPlayIdx() > 4)
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::DOWN);
		_enemy->ChangeStatement();
	}
}
