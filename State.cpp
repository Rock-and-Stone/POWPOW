#include "pch.h"
#include "State.h"
#include "player.h"

State::State()
{
}

State::~State()
{
}

#pragma region Idle

HRESULT Idle::init()
{
	_player->setIsAir(false);
	_player->setAirY(0);
	_player->setIsRun(false);
	_player->setIsVulnuerable(true);
	_player->setAtkCount(0);
	return S_OK;
}

void Idle::release()
{
}

void Idle::update()
{
	Input();
	if (_player->getTrigger()) Trigger();
}

void Idle::render(HDC hdc)
{

}

void Idle::Input()
{
	int currentDirX = _player->getDirectionX();
	int currentDirY = _player->getDirectionY();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player->ChangeState(Statement::WALK);
		_player->setDirectionX(-1);
		_player->setAnimLoop(true);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player->ChangeState(Statement::WALK);
		_player->setDirectionX(1);
		_player->setAnimLoop(true);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_player->ChangeState(Statement::WALK);
		_player->setDirectionY(-1);
		_player->setAnimLoop(true);
		_player->setSpeedY(2);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_player->ChangeState(Statement::WALK);
		_player->setDirectionY(1);
		_player->setAnimLoop(true);
		_player->setSpeedY(2);
	}
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		_player->ChangeState(Statement::JUMP);
		_player->setAnimLoop(false);
		_player->setJumpPower(12.0f);
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_player->ChangeState(Statement::ATTACK);
		_player->setAnimLoop(false);
		_player->setSpeedX(2);
	}
}

void Idle::Trigger()
{
	_player->ChangeState(Statement::IDLE);
	_player->setAnimLoop(true);
}
#pragma endregion

#pragma region MOVE
HRESULT Move::init()
{
	_player->setAnimLoop(true);
	return S_OK;
}

void Move::release()
{
}

void Move::update()
{
	Input();
	Speed();
}
	
void Move::render(HDC hdc)
{

}

void Move::Input()
{
	int currentDirX = _player->getDirectionX();
	int currentDirY = _player->getDirectionY();

	if (KEYMANAGER->isOnceKeyDown(VK_SHIFT) && !_player->getIsRun())
	{
		_player->ChangeState(Statement::RUN);
		_player->setIsRun(true);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _player->setDirectionX(-1);

	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))_player->setDirectionX(1);

	if (KEYMANAGER->isStayKeyDown(VK_UP))	_player->setDirectionY(-1);

	else if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _player->setDirectionY(1);

	if (!KEYMANAGER->isStayKeyDown(VK_LEFT) &&
		!KEYMANAGER->isStayKeyDown(VK_RIGHT)) _player->setDirectionX(0);

	if (!KEYMANAGER->isStayKeyDown(VK_UP) &&
		!KEYMANAGER->isStayKeyDown(VK_DOWN)) _player->setDirectionY(0);

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		_player->ChangeState(Statement::JUMP);
		_player->setAnimLoop(false);
		_player->setJumpPower(12.0f);
	}

	if (!KEYMANAGER->isStayKeyDown(VK_LEFT) &&
		!KEYMANAGER->isStayKeyDown(VK_RIGHT) &&
		!KEYMANAGER->isStayKeyDown(VK_UP) &&
		!KEYMANAGER->isStayKeyDown(VK_DOWN))	_player->ChangeState(Statement::IDLE);
	
}

void Move::Trigger()
{

}

void Move::Speed()
{
	if (_player->getDirectionX() != 0) _player->setSpeedX(_player->getSpeedX() + 2.0f);
	if(_player->getDirectionY() != 0)  _player->setSpeedY(_player->getSpeedY() + 1.0f);
}

#pragma endregion

#pragma region JUMP
HRESULT Jump::init()
{
	_player->setIsAir(true);
	return S_OK;
}

void Jump::release()
{
}

void Jump::update()
{
	if (_player->getJumpPower() < 1)
	{
		_player->ChangeState(Statement::FALL);
		_player->setAnimLoop(false);
	}
}

void Jump::render(HDC hdc)
{
}

void Jump::Input()
{

}

void Jump::Trigger()
{

}

#pragma endregion

#pragma region FALL
HRESULT Fall::init()
{

	return S_OK;
}

void Fall::release()
{

}

void Fall::update()
{

	if (_player->getAirY() >= 0)
	{
		_player->ChangeState(Statement::LAND);
		_player->setAnimLoop(false);
	}
}

void Fall::render(HDC hdc)
{

}

void Fall::Input()
{
}

void Fall::Trigger()
{
}

#pragma endregion

#pragma region ATTACK
HRESULT Attack::init()
{
	_keyPressed = false;
	return S_OK;
}

void Attack::release()
{
}

void Attack::update()
{
	Input();
	if (_player->getTrigger())Trigger();
}

void Attack::render(HDC hdc)
{

}

void Attack::Input()
{
	_player->setIsAttack(false);
	if (KEYMANAGER->isOnceKeyDown('X') && _player->getAtkCount() < 2 && _player->getIndexX() > 0)
	{
		_player->setAtkCount(_player->getAtkCount() + 1);
		_player->setSpeedX(2.0f);
		_player->ChangeState(Statement::ATTACK);
	}
}

void Attack::Trigger()
{
	_player->ChangeState(Statement::IDLE);
}

#pragma endregion

HRESULT Damaged::init()
{
	_player->setIsVulnuerable(false);
	_player->setAnimLoop(false);
	return S_OK;
}

void Damaged::release()
{

}

void Damaged::update()
{
	Input();
	if (_player->getTrigger()) Trigger();
}

void Damaged::render(HDC hdc)
{

}

void Damaged::Input()
{

}

void Damaged::Trigger()
{
	_player->ChangeState(Statement::IDLE);
	_player->setAnimLoop(true);
}

HRESULT Down::init()
{
	_player->setIsVulnuerable(false);
	_player->setAnimLoop(false);
	_count = 0;
	return S_OK;
}

void Down::release()
{

}

void Down::update()
{
	Input();
	if (_player->getTrigger()) Trigger();
}

void Down::render(HDC hdc)
{

}

void Down::Input()
{

}

void Down::Trigger()
{
	_count++;

	if (_count % 20 == 0)
	{
		_player->ChangeState(Statement::GETUP);
		_player->setAnimLoop(false);
	}
}

HRESULT GetUp::init()
{
	return S_OK;
}

void GetUp::release()
{
}

void GetUp::update()
{
	Input();
	if (_player->getTrigger()) Trigger();
}

void GetUp::render(HDC hdc)
{

}

void GetUp::Input()
{

}

void GetUp::Trigger()
{
	_player->ChangeState(Statement::IDLE);
	_player->setAnimLoop(true);
}
