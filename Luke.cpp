#include "pch.h"
#include "Luke.h"

Luke::Luke()
{
}

Luke::~Luke()
{
}

HRESULT Luke::init()
{
	_searchRange = 800;
	_attackRange = 100;
	_maxHP = _currentHP = 100;

	return S_OK;
}

void Luke::release()
{
}

void Luke::update()
{
	_state->update();
	Move();
    TracePlayer();
    MakeAttackRect();
}

void Luke::SwitchImage()
{
   switch (_enemyStatement)
    {
    case ENEMYSTATEMENT::IDLE:
        _imageName = IMAGEMANAGER->findImage("LUKE_IDLE");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftIdle");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightIdle");
        }
        break;
    case ENEMYSTATEMENT::WALK:
        _imageName = IMAGEMANAGER->findImage("LUKE_WALK");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftWalk");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightWalk");
        }
        break;
    case ENEMYSTATEMENT::RUN:
        _imageName = IMAGEMANAGER->findImage("LUKE_RUN");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftRun");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightRun");
        }
        break;
    case ENEMYSTATEMENT::JUMP:
        _imageName = IMAGEMANAGER->findImage("LUKE_JUMP");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftJump");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightJump");
        }
        break;
    case ENEMYSTATEMENT::FALL:
        _imageName = IMAGEMANAGER->findImage("LUKE_JUMP");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftFall");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightFall");
        }
        break;
    case ENEMYSTATEMENT::GUARD:
        _imageName = IMAGEMANAGER->findImage("LUKE_GUARD");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftGuard");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightGuard");
        }
        break;
    case ENEMYSTATEMENT::DOWN:
        _imageName = IMAGEMANAGER->findImage("LUKE_DOWN");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftDown");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightDown");
        }
        break;

    case ENEMYSTATEMENT::DAMAGED:
        _imageName = IMAGEMANAGER->findImage("LUKE_DAMAGED");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftDamaged");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightDamaged");
        }
        break;

    case ENEMYSTATEMENT::ATTACK:
        _imageName = IMAGEMANAGER->findImage("LUKE_ATTACK1");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftAttack1");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightAttack1");
        }
        break;

    case ENEMYSTATEMENT::GETUP:
        _imageName = IMAGEMANAGER->findImage("LUKE_UP");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftUp");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightUp");
        }
        break;

    }
    _motionName->start();
}





