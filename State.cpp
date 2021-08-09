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
	_player->setAirY(0);
	_player->setIsRun(false);
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

HRESULT Walk::init()
{
	_player->setAnimLoop(true);
	return S_OK;
}

void Walk::release()
{
}

void Walk::update()
{
	Input();
	Speed();
}
	
void Walk::render(HDC hdc)
{

}

void Walk::Input()
{
	int currentDirX = _player->getDirectionX();
	int currentDirY = _player->getDirectionY();

	if (KEYMANAGER->isOnceKeyDown(VK_SHIFT) && !_player->getIsRun())
	{
		_player->ChangeState(Statement::RUN);
		_player->setIsRun(true);
	}

	if (LEFTKEYDOWN)
	{
		_player->setDirectionX(-1);
	}

	if (LEFTKEYUP && currentDirX == -1)
	{
		if(currentDirY == 0)_player->ChangeState(Statement::IDLE);
		_player->setDirectionX(0);
	}

	if (RIGHTKEYDOWN)
	{
		_player->setDirectionX(1);
	}

	if (RIGHTKEYUP && currentDirX == 1)
	{
		if (currentDirY == 0)_player->ChangeState(Statement::IDLE);
		_player->setDirectionX(0);
	}

	if (UPKEYDOWN)
	{
		_player->setDirectionY(-1);
	}

	if (UPKEYUP && currentDirY == -1)
	{
		if (currentDirX == 0)_player->ChangeState(Statement::IDLE);
		_player->setDirectionY(0);
	}

	if (DOWNKEYDOWN)
	{
		_player->setDirectionY(1);
	}

	if (DOWNKEYUP && currentDirY == 1)
	{
		if (currentDirX == 0)_player->ChangeState(Statement::IDLE);
		_player->setDirectionY(0);
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

void Walk::Speed()
{
	if (_player->getDirectionX() != 0) _player->setSpeedX(_player->getSpeedX() + 2.0f);
	if(_player->getDirectionY() != 0)  _player->setSpeedY(_player->getSpeedY() + 1.0f);
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

HRESULT Attack::init()
{
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
