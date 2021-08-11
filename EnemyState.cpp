#include "pch.h"
#include "EnemyState.h"
#include "Enemy.h"

EnemyState::EnemyState()
{
}

EnemyState::~EnemyState()
{
}

HRESULT EnemyIdle::init()
{
	_enemy->setIsChange(false);
	_enemy->SetIsAir(false);
	_enemy->setSpeedX(0);
	_enemy->setSpeedY(0);
	return S_OK;
}

void EnemyIdle::release()
{
}

void EnemyIdle::update()
{
	if(_enemy->getIsChange())
	{
		if (_enemy->AttackSession()) _enemy->ChangeStatement(ENEMYSTATEMENT::ATTACK);

		else if (_enemy->ChaseSession())
		{
			_enemy->ChangeStatement(ENEMYSTATEMENT::WALK);
		}

		else _enemy->ChangeStatement(ENEMYSTATEMENT::WANDER);
	}
}


HRESULT EnemyMove::init()
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
	return S_OK;
}

void EnemyMove::release()
{
}

void EnemyMove::update()
{
	_enemy->setSpeedX(_enemy->getSpeedX() + 2.0f);
	_enemy->setSpeedY(_enemy->getSpeedY() + 1.0f);

	if (_enemy->GetEnemyStatement() == ENEMYSTATEMENT::WANDER)
	{
		if (_enemy->getIsChange())
		{
			if (_enemy->AttackSession())	_enemy->ChangeStatement(ENEMYSTATEMENT::ATTACK);

			else if (_enemy->ChaseSession())
			{
				_enemy->ChangeStatement(ENEMYSTATEMENT::WALK);
			}

			else _enemy->ChangeStatement(ENEMYSTATEMENT::IDLE);
		}
	}

	else
	{
		if (_enemy->AttackSession())	_enemy->ChangeStatement(ENEMYSTATEMENT::ATTACK);

		if (_enemy->getIsChange())
		{
			
			if (!_enemy->ChaseSession())
			{
				int rnd = RND->getInt(2);

				if(rnd == 0)_enemy->ChangeStatement(ENEMYSTATEMENT::WANDER);
				else _enemy->ChangeStatement(ENEMYSTATEMENT::IDLE);
			}
		}
	}

}


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
	if (!_enemy->GetMotionName()->isPlay())
	{
		_enemy->ChangeStatement(ENEMYSTATEMENT::IDLE);
	}
}


HRESULT EnemyDamaged::init()
{
	//IMAGEMANAGER->addImage("attackEffect", "source/effect/attackEffect.bmp", 350, 50, true, MAGENTA);
	//EFFECTMANAGER->addEffect("attackEffect1", "source/effect/attackEffect.bmp", 350, 50, 50, 50, 1, 0.08f, 1000);
	_enemy->SetEnemyHP(_enemy->GetEnemyHP() - 10);
	_enemy->setIsTrace(false);
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
	if (_enemy->GetEnemyHP() == 0)
	{
		_enemy->ChangeStatement(ENEMYSTATEMENT::DOWN);
	}
	if (_enemy->GetMotionName()->GetNowPlayIdx() == 4)
	{
		_enemy->ChangeStatement(ENEMYSTATEMENT::IDLE);
	}
}


HRESULT EnemyDown::init()
{
	_enemy->setIsTrace(false);
	return S_OK;
}

void EnemyDown::release()
{
}

void EnemyDown::update()
{
	//만약 아직 HP가 0이 아니면 -> UP
	//만약 뒤지면 -> 알파블렌드로 처리한다음에-> DEAD // findIMAGE-> 마젠타
}


HRESULT EnemyGuard::init()
{
	_enemy->setIsTrace(false);

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
	if (!_enemy->GetMotionName()->isPlay())
	{
		_enemy->ChangeStatement(ENEMYSTATEMENT::IDLE);
	}
}

HRESULT EnemyGetUp::init()
{
	_enemy->setIsTrace(false);
	return S_OK;
}

void EnemyGetUp::release()
{
}

void EnemyGetUp::update()
{
}
