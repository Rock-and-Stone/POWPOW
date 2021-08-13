#include "pch.h"
#include "EnemyState.h"
#include "Enemy.h"

EnemyState::EnemyState()
{
}

EnemyState::~EnemyState()
{
}


#pragma region INIT
HRESULT EnemyInit::init()
{

	_enemy->setIsChange(false);
	_enemy->setIsAttack(false);
	_enemy->setIsVulnerable(false);
	_enemy->SetIsAir(false);
	_enemy->setAtkCount(0);

	return S_OK;
}

void EnemyInit::release()
{

}

void EnemyInit::update()
{
	_enemy->StateCount();
	if (_enemy->getIsChange()) _enemy->ChangeStatement(ENEMYSTATEMENT::WANDER);
}
#pragma endregion 

#pragma region IDLE
HRESULT EnemyIdle::init()
{
	_enemy->setIsChange(false);
	_enemy->setIsAttack(false);
	_enemy->setIsVulnerable(true);
	_enemy->SetIsAir(false);
	_enemy->setAtkCount(0);
	return S_OK;
}

void EnemyIdle::release()
{
}

void EnemyIdle::update()
{
	_enemy->StateCount();

	if(_enemy->getIsChange())
	{
		if (_enemy->AttackSession()) _enemy->ChangeStatement(ENEMYSTATEMENT::ATTACK);

		else 
		{
			int rnd = RND->getInt(2);
			if (rnd == 0) _enemy->ChangeStatement(ENEMYSTATEMENT::CHASE);
			else _enemy->ChangeStatement(ENEMYSTATEMENT::WANDER);
		}
	}
}
#pragma endregion

#pragma region MOVE
HRESULT EnemyWander::init()
{
	//rndX = RND->getFromIntTo(-1, 2);
	//rndY = RND->getFromIntTo(-1, 2);

	while (rndX == 0 && rndY == 0)
	{
		rndX = RND->getFromIntTo(-1, 2);
		rndY = RND->getFromIntTo(-1, 2);
	}

	_enemy->setWanderDirX(rndX);
	_enemy->setWanderDirY(rndY);

	_enemy->setIsChange(false);
	_enemy->setIsVulnerable(true);
	_enemy->setIsRun(false);
	return S_OK;
}

void EnemyWander::release()
{
}

void EnemyWander::update()
{
	_enemy->StateCount();

	if (_enemy->GetEnemyRendX() < 50) _enemy->setWanderDirX(1);
	else if (_enemy->GetEnemyRendX() > WINSIZEX - 50) _enemy->setWanderDirX(-1);
	_enemy->setSpeedX(_enemy->getSpeedX() + 2.0f);
	_enemy->setSpeedY(_enemy->getSpeedY() + 1.0f);



	if (_enemy->getIsChange())
	{
		_enemy->ChasePlayer();
		if (_enemy->AttackSession())_enemy->ChangeStatement(ENEMYSTATEMENT::ATTACK);
		else _enemy->ChangeStatement(ENEMYSTATEMENT::IDLE);
	}

}

#pragma endregion


HRESULT EnemyChase::init()
{
	_enemy->setIsChange(false);
	_enemy->setIsVulnerable(true);
	_enemy->setIsRun(true);
	return S_OK;
}

void EnemyChase::release()
{

}

void EnemyChase::update()
{
	_enemy->StateCount();
	_enemy->ChasePlayer();
	_enemy->setSpeedX(_enemy->getSpeedX() + 4.0f);
	_enemy->setSpeedY(_enemy->getSpeedY() + 2.0f);

	if (_enemy->AttackSession()) _enemy->ChangeStatement(ENEMYSTATEMENT::ATTACK);

	else if (_enemy->getIsChange())
	{
		_enemy->ChangeStatement(ENEMYSTATEMENT::WANDER);
	}

}

#pragma region JUMP

HRESULT EnemyJump::init()
{
	_enemy->setIsChange(false);
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
		_enemy->ChangeStatement(ENEMYSTATEMENT::FALL);
	}
}

#pragma endregion

#pragma region FALL
HRESULT EnemyFall::init()
{
	_enemy->setIsChange(false);
	return S_OK;
}

void EnemyFall::release()
{
}

void EnemyFall::update()
{
	if (_enemy->GetJumpPower() < 0) _enemy->SetIsAir(false);
}

#pragma endregion

#pragma region ATTACK

HRESULT EnemyAttack::init()
{
	_enemy->setIsChange(false);
	_enemy->setIsAttack(true);
	_enemy->setIsTrace(false);

	return S_OK;
}

void EnemyAttack::release()
{
}

void EnemyAttack::update()
{
	_enemy->StateCount();

	_enemy->setIsAttack(false);
	if (!_enemy->GetMotionName()->isPlay())
	{
		_enemy->setAtkCount(_enemy->getAtkCount() + 1);

		if (_enemy->getAtkCount() >= 3) 
		{
			_enemy->ChangeStatement(ENEMYSTATEMENT::WANDER);
			return;
		}

		if(_enemy->getAtkCount() == 2) _enemy->setAtkCount(RND->getFromIntTo(2,4));

		if (_enemy->getAtkCount() < 4) _enemy->ChangeStatement(ENEMYSTATEMENT::ATTACK);

	}
}

#pragma endregion

#pragma region DAMAGED
HRESULT EnemyDamaged::init()
{
	//IMAGEMANAGER->addImage("attackEffect", "source/effect/attackEffect.bmp", 350, 50, true, MAGENTA);
	//EFFECTMANAGER->addEffect("attackEffect1", "source/effect/attackEffect.bmp", 350, 50, 50, 50, 1, 0.08f, 1000);
	_enemy->setSpeedX(-4.0f);
	_enemy->SetEnemyHP(_enemy->GetEnemyHP() - 10);
	if (_enemy->GetEnemyDirection() == -1)
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
	if (_enemy->getHitGauge() > 2 || _enemy->GetEnemyHP() <= 0)
	{
		_enemy->ChangeStatement(ENEMYSTATEMENT::DOWN);
		return;
	}

	if (!_enemy->GetMotionName()->isPlay())
	{
		_enemy->ChangeStatement(ENEMYSTATEMENT::IDLE);
	}
}
#pragma endregion 

#pragma region DOWN
HRESULT EnemyDown::init()
{
	_enemy->SetIsAir(true);
	_enemy->SetJumpPower(6.0f);
	_enemy->setIsVulnerable(false);
	return S_OK;
}

void EnemyDown::release()
{
}

void EnemyDown::update()
{
	if (!_enemy->getReleased() && _enemy->GetMotionName()->GetNowPlayIdx() < 6  )
	{
		_enemy->setSpeedX(-4.0f);
	}
	else _enemy->SetIsAir(false);


	if (!_enemy->GetMotionName()->isPlay())
	{
		if (_enemy->GetEnemyHP() > 0)_enemy->ChangeStatement(ENEMYSTATEMENT::GETUP);
		else _enemy->setIsDead(true);
	}
}
#pragma endregion 

#pragma region GUARD
HRESULT EnemyGuard::init()
{
	_enemy->setIsTrace(false);

	if (_enemy->GetEnemyDirection() == -1)
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
	if (!_enemy->GetMotionName()->isPlay())
	{
		_enemy->ChangeStatement(ENEMYSTATEMENT::IDLE);
	}
}
#pragma endregion 

#pragma region GETUP
HRESULT EnemyGetUp::init()
{
	_enemy->setIsVulnerable(false);
	_enemy->setIsTrace(false);
	return S_OK;
}

void EnemyGetUp::release()
{

}

void EnemyGetUp::update()
{
	if (!_enemy->GetMotionName()->isPlay())
	{
		_enemy->ChangeStatement(ENEMYSTATEMENT::IDLE);
	}
}
#pragma endregion 

