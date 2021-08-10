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

	return S_OK;
}

void EnemyIdle::release()
{
}

void EnemyIdle::update()
{
	if (_enemy->ChaseSession())
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::RUN);
		_enemy->ChangeStatement();
	}
}


HRESULT EnemyWalk::init()
{
	//카운트 랜덤으로 주기
	_count = RND->getInt(2);
	return S_OK;
}

void EnemyWalk::release()
{
}

void EnemyWalk::update()
{
	if (_enemy->WalkSession())
	{
		_enemy->ChaseWalk();
	}

	//지금이 어택이 가능한상태인가?
	if (_enemy->AttackSession())
	{
		if (_count == 0)
		{
			_enemy->ChangeStatement();
			_enemy->SetEnemyStatement(ENEMYSTATEMENT::ATTACK);
		}
	}
}


HRESULT EnemyRun::init()
{
	return S_OK;
}

void EnemyRun::release()
{
}

void EnemyRun::update()
{
	if (_enemy->ChaseSession())
	{
		_enemy->ChaseRun();
	}

	//지금이 어택이 가능한상태인가?
	if (_enemy->AttackSession())
	{
		_enemy->ChangeStatement();
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::ATTACK);
	}
}

HRESULT EnemyJump::init()
{
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

HRESULT EnemyFall::init()
{
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
	return S_OK;
}

void EnemyAttack::release()
{
}

void EnemyAttack::update()
{
	if (_enemy->GetMotionName()->GetNowPlayIdx() == 3)
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::ATTACK);
		_enemy->ChangeStatement();
		_enemy->ComboSession();
	}
}


HRESULT EnemyDamaged::init()
{
	//IMAGEMANAGER->addImage("attackEffect", "source/effect/attackEffect.bmp", 350, 50, true, MAGENTA);
	//EFFECTMANAGER->addEffect("attackEffect1", "source/effect/attackEffect.bmp", 350, 50, 50, 50, 1, 0.08f, 1000);
	_enemy->SetEnemyHP(_enemy->GetEnemyHP() - 10);

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
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::DOWN);
		_enemy->ChangeStatement();
	}
	if (_enemy->GetMotionName()->GetNowPlayIdx() == 4)
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::IDLE);
		_enemy->ChangeStatement();
	}
}


HRESULT EnemyDown::init()
{
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
	if (_enemy->GetMotionName()->GetNowPlayIdx() == 2)
	{
		_enemy->SetEnemyStatement(ENEMYSTATEMENT::IDLE);
		_enemy->ChangeStatement();
	}
}

HRESULT EnemyGetUp::init()
{
	return S_OK;
}

void EnemyGetUp::release()
{
}

void EnemyGetUp::update()
{
}
