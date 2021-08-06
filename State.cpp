#include "pch.h"
#include "State.h"
#include "player.h"

State::State()
{
}

State::~State()
{
}

HRESULT Idle::init()
{
	_player->setIsAir(false);
	_player->setSpeedX(0);
	_player->setSpeedY(0);
	_player->setAirY(0);
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
		_player->setDirectionX(0);
		_player->setAnimLoop(true);
		_player->setSpeedX(5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player->ChangeState(Statement::WALK);
		_player->setDirectionX(1);
		_player->setAnimLoop(true);
		_player->setSpeedX(5);
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
		_player->setJumpPower(7);
	}
}

void Idle::Trigger()
{

}

HRESULT Walk::init()
{

	return S_OK;
}

void Walk::release()
{
}

void Walk::update()
{
	Input();
}
	
void Walk::render(HDC hdc)
{

}

void Walk::Input()
{
	int currentDirX = _player->getDirectionX();
	int currentDirY = _player->getDirectionY();

	if (LEFTKEYDOWN)
	{
		_player->setDirectionX(0);
		_player->setAnimLoop(true);
		_player->setSpeedX(5);
	}

	if (LEFTKEYUP && currentDirX == 0)
	{
		if(currentDirY == 0)_player->ChangeState(Statement::IDLE);
		_player->setDirectionX(0);
		_player->setAnimLoop(true);
		_player->setSpeedX(0);
	}

	if (RIGHTKEYDOWN)
	{
		
		_player->setDirectionX(1);
		_player->setAnimLoop(true);
		_player->setSpeedX(5);
	}

	if (RIGHTKEYUP && currentDirX == 1)
	{
		if (currentDirY == 0)_player->ChangeState(Statement::IDLE);
		_player->setDirectionX(1);
		_player->setAnimLoop(true);
		_player->setSpeedX(0);
	}

	if (UPKEYDOWN)
	{
		_player->setDirectionY(-1);
		_player->setAnimLoop(true);
		_player->setSpeedY(2);
	}

	if (UPKEYUP && currentDirY == -1)
	{
		if(_player->getSpeedX() == 0)_player->ChangeState(Statement::IDLE);
		_player->setDirectionY(0);
		_player->setAnimLoop(true);

	}

	if (DOWNKEYDOWN)
	{
		_player->setDirectionY(1);
		_player->setAnimLoop(true);
		_player->setSpeedY(2);
	}

	if (DOWNKEYUP && currentDirY == 1)
	{
		if (_player->getSpeedX() == 0)_player->ChangeState(Statement::IDLE);
		_player->setDirectionY(0);
		_player->setAnimLoop(true);
	}

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		_player->ChangeState(Statement::JUMP);
		_player->setJumpPower(12.0f);
	}
}

void Walk::Trigger()
{

}

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
		_player->ChangeState(Statement::IDLE);
		_player->setAnimLoop(true);
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
