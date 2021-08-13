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

HRESULT player::init(float posX, float posY)
{

	_idle = new Idle;
	_move = new Move;
	_jump = new Jump;
	_fall = new Fall;
	_damaged = new Damaged;
	_down = new Down;
	_getUp = new GetUp;
	_attack = new Attack;

	_idle->setPlayer(this);
	_move->setPlayer(this);
	_jump->setPlayer(this);
	_fall->setPlayer(this);
	_damaged->setPlayer(this);
	_down->setPlayer(this);
	_getUp->setPlayer(this);
	_attack->setPlayer(this);

	_state = _idle;

#pragma region Variables
	_posX = posX;
	_posY = posY;

	_maxSpeedX = MAXSPEEDX;
	_maxSpeedY = MAXSPEEDY;

	_gravity = 0;
	_jumpPower = 0;
	_speedRes = 0.50f;
	_airY = 0;
	_coin = getSaveCoin();

	_dirX = 1;
	_dirY = 0;

	_indexX = _indexY = 0;

	_animLoop = true;
	_trigger = false;
	_isAir = false;
	_isAttack = false;
	_isRun = false;
	_isVulnerable = true;
	_currentHP = _maxHP = getPlayerSaveHP();

	_statement = Statement::IDLE;
	_shadow = IMAGEMANAGER->findImage("shadow");

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
	}
	_shadowRC = RectMakeCenter(_rendX, _rendY + (_hitRC.bottom - _hitRC.top) / 2, _shadow->getWidth(), _shadow->getHeight());
	

	if (_dirX < 0) _indexY = 0;
	else if(_dirX > 0)_indexY = 1;
	_shadow->render(getMemDC(), _shadowRC.left, _shadowRC.top);
	_img->frameRender(getMemDC(), _renderRC.left, _renderRC.top + _airY, _indexX, _indexY);
	
	_hitRC = RectMakeCenter(_rendX, _rendY + _airY, 80, 180);

}


float player::getRenderPosY()
{
	return _posY;
}


void player::Movement()
{
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


	if (_rendX > WINSIZEX) _posX -= _speedX;
	else if (_rendX < 0) _posX += _speedX;


	if (_indexY == 0) _posX -= _speedX;
	else if(_indexY == 1) _posX += _speedX;

	if (_dirY == -1)_posY -= _speedY;
	else if(_dirY == 1) _posY += _speedY;

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

void player::coinGet(int coin)
{
	_coin += coin;
}

void player::hitDamage(int damage)
{
	if (_isVulnerable)
	{
		_hitCount++;
		if (_hitCount > 2)	ChangeState(Statement::DOWN);
		else	ChangeState(Statement::DAMAGED);
		_currentHP -= damage;
	}
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
		_state = _move;
		break;
	case Statement::WALK:
		_state = _move;
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
	case Statement::DAMAGED:
		_state = _damaged;
		break;
	case Statement::DOWN:
		_state = _down;
		break;
	case Statement::GETUP:
		_state = _getUp;
		_hitCount = 0;
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
					_attackRC = RectMakeCenter(_rendX - 60 + _indexY * 120, _rendY, 50, 30);
				break;
			}
			case 1:
			{
					_attackRC = RectMakeCenter(_rendX - 60 + _indexY * 120, _rendY , 50, 30);
				break;
			}
			case 2:
			{
					_attackRC = RectMakeCenter(_rendX - 60 + _indexY * 120, _rendY, 50, 30);
				break;
			}
		}

	}

	else _attackRC = RectMakeCenter(_rendX, _rendY, 0, 0);

}

