#include "pch.h"
#include "Ramona.h"

Ramona::Ramona()
{
}

Ramona::~Ramona()
{
}

HRESULT Ramona::InitVariables()
{
	_img = IMAGEMANAGER->findImage("Ramona_Idle");
	_renderRC = RectMakeCenter(_rendX, _rendY, _img->getFrameWidth(), _img->getFrameHeight());
	return S_OK;
}

void Ramona::update()
{
	_state->update();
	Movement();
	SwitchImage();
	CountFrame();
	Collision();
	AttackCollision();
}

void Ramona::SwitchImage()
{
	_renderRC = RectMakeCenter(_rendX, _rendY, _img->getFrameWidth(), _img->getFrameHeight());
	switch (_statement)
	{
	case Statement::IDLE:
	{
		_img = IMAGEMANAGER->findImage("Ramona_Idle");
		break;
	}

	case Statement::JUMP:
	{
		_img = IMAGEMANAGER->findImage("Ramona_Jump");
		break;
	}

	case Statement::RUN:
	{
		_img = IMAGEMANAGER->findImage("Ramona_Run");
		break;
	}

	case Statement::FALL:
	{
		_img = IMAGEMANAGER->findImage("Ramona_Fall");
		break;
	}

	case Statement::LAND:
	{
		_img = IMAGEMANAGER->findImage("Ramona_Land");
		break;
	}
	case Statement::WALK:
	{
		_img = IMAGEMANAGER->findImage("Ramona_Walk");
		break;
	}

	case Statement::ATTACK:
	{
		switch (_atkCount)
		{
		case 0:
			_img = IMAGEMANAGER->findImage("Ramona_Attack_0");
			break;
		case 1:
			_img = IMAGEMANAGER->findImage("Ramona_Attack_1");
			break;
		case 2:
			_img = IMAGEMANAGER->findImage("Ramona_Attack_2");
			break;
		}
		break;
	}

	}
}
