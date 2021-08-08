#include "pch.h"
#include "player.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::InitVariables()
{
	return S_OK;
}

HRESULT player::init()
{

	_idle = new Idle;
	_walk = new Walk;
	_jump = new Jump;
	_fall = new Fall;

	_idle->setPlayer(this);
	_walk->setPlayer(this);
	_jump->setPlayer(this);
	_fall->setPlayer(this);

	_state = _idle;

#pragma region Variables
	_posX = 200;
	_groundY = 1000;
	_posY = _groundY + _airY;

	_gravity = 0;
	_jumpPower = 0;
	_airY = 0;
	_dirX = 0;
	_dirY = 0;
	_indexX = 0;
	_keyCount = 0;
	_animLoop = true;
	_trigger = false;
	_isAir = false;
	_isAttack = false;

	_statement = Statement::IDLE;

	RENDERMANAGER->addRender(this);

#pragma endregion

	return S_OK;
}

void player::release()
{

}

void player::update()
{

}

void player::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _hitRC);
		//LineMake(getMemDC(), _hitRC.left, _hitRC.bottom, _hitRC.right, _hitRC.bottom);
	}
	_absolX = _rendX - (_renderRC.right - _renderRC.left) / 2;
	_absolY = _rendY - (_renderRC.bottom - _renderRC.top) / 2;

	_img->frameRender(getMemDC(), _absolX, _absolY, _indexX, _dirX);
	_hitRC = RectMakeCenter(_rendX, _rendY, 80, 180);

}


int player::getRenderPosY()
{
	return _groundY;
}


void player::Movement()
{
	_posY = _groundY + _airY;
	if (_dirX == 0)_posX -= _speedX;
	else _posX += _speedX;

	if (_dirY == -1)_groundY -= _speedY;
	else if(_dirY == 1) _groundY += _speedY;

	if (_isAir)
	{
		_gravity = 0.52f;

		_airY -= _jumpPower;

		_jumpPower -= _gravity;
	}
	else
	{
		_gravity = 0;
		_jumpPower = 0;
	}

}

void player::CountFrame()
{
	_count++;

	_img->setFrameX(_indexX);
	_img->setFrameY(_dirX);

	if (_count % 7 == 0)
	{
		//맥스 프레임 조건 확인.
		_indexX++;

		if (_indexX > _img->getMaxFrameX())  // 최대 프레임 도달
		{
			if (_animLoop) _indexX = 0; // 루프일때 프레임 초기화

			
	else // 루프가 아닐때
			{
				_indexX = _img->getMaxFrameX(); // 프레임 고정
				_trigger = true;
			}
		}

		_count = 0;
	}
}

void player::Collision()
{

}

void player::ChangeState(Statement statement)
{
	_indexX = 0;
	_trigger = false;
	_isAttack = false;
	_statement = statement;

	switch (_statement)
	{
	case Statement::IDLE:
		_state = _idle;
		break;
	case Statement::RUN:
		break;
	case Statement::WALK:
		_state = _walk;
		break;
	case Statement::JUMP:
		_state = _jump;
		break;
	case Statement::FALL:
		_state = _fall;
		break;
	case Statement::LAND:
		break;

	}

	_state->init();
}

