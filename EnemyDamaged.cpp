#include "pch.h"
#include "EnemyDamaged.h"
#include "Enemy.h"

HRESULT EnemyDamaged::init()
{
	//IMAGEMANAGER->addImage("attackEffect", "source/effect/attackEffect.bmp", 350, 50, true, MAGENTA);
	//EFFECTMANAGER->addEffect("attackEffect1", "source/effect/attackEffect.bmp", 350, 50, 50, 50, 1, 0.08f, 1000);
	if (_enemy->GetEnemyDirection() == 0)
	{
		EFFECTMANAGER->play("attackEffect1", _enemy->GetEnemyRendX() - 40, _enemy->GetEnemyRendY());
	}
	if (_enemy->GetEnemyDirection() == 1)
	{
		EFFECTMANAGER->play("attackEffect1", _enemy->GetEnemyRendX() + 40, _enemy->GetEnemyRendY());
	}
	
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

