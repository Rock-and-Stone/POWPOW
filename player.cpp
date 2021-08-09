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
	_attack = new Attack;

	_idle->setPlayer(this);
	_walk->setPlayer(this);
	_jump->setPlayer(this);
	_fall->setPlayer(this);
	_attack->setPlayer(this);

	_state = _idle;

#pragma region Variables
	_posX = 1000;
	_groundY = 500;
	_posY = _groundY + _airY;

	_maxSpeedX = MAXSPEEDX;
	_maxSpeedY = MAXSPEEDY;

	_gravity = 0;
	_jumpPower = 0;
	_speedRes = 0.50f;
	_airY = 0;

	_dirX = 0;
	_dirY = 0;

	_indexX = _indexY = 0;

	_animLoop = true;
	_trigger = false;
	_isAir = false;
	_isAttack = false;
	_isRun = false;

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
		Rectangle(getMemDC(), _attackRC);
		//LineMake(getMemDC(), _hitRC.left, _hitRC.bottom, _hitRC.right, _hitRC.bottom);
	}

	if (_dirX < 0) _indexY = 0;
	else if(_dirX > 0)_indexY = 1;

	_img->frameRender(getMemDC(), _renderRC.left, _renderRC.top, _indexX, _indexY);
	_hitRC = RectMakeCenter(_rendX, _rendY, 80, 180);

}


float player::getRenderPosY()
{
	return _groundY;
}


void player::Movement()
{
	_posY = _groundY + _airY;

	if (_isRun)
	{
		_maxSpeedX = MAXSPEEDX * 2;
		_maxSpeedY = MAXSPEEDY * 2;
	}

	else
	{
		_maxSpeedX = MAXSPEEDX;
		_maxSpeedY = MAXSPEEDY;
	}

	if (!_isAir)
	{
		if (_speedX > 0.01) _speedX -= _speedRes;
		else _speedX = 0;

		if (_speedY > 0.01) _speedY -= _speedRes;
		else _speedY = 0;
	}

	if (_speedX >= _maxSpeedX) _speedX = _maxSpeedX;

	if (_speedY >= _maxSpeedY) _speedY = _maxSpeedY;

	if (_indexY == 0) _posX -= _speedX;
	else if(_indexY == 1) _posX += _speedX;

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

void player::hitDamage(int damage)
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
		_state = _walk;
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
		_state = _idle;
		break;
	case Statement::ATTACK:
		_state = _attack;
		_isAttack = true;
		break;

	}

	_state->init();
}

void player::AttackCollision()
{
	if (_isAttack && _indexX < 2)
	{
		switch (_atkCount)
		{
			case 0:
			{
					_attackRC = RectMakeCenter(_rendX, _rendY, 200, 50);
				break;
			}
			case 1:
			{
					_attackRC = RectMakeCenter(_rendX, _rendY, 200, 50);
				break;
			}
			case 2:
			{
					_attackRC = RectMakeCenter(_rendX, _rendY, 200, 60);
				break;
			}
		}

	}

	else _attackRC = RectMakeCenter(_rendX, _rendY, 0, 0);

}

