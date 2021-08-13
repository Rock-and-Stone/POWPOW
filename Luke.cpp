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
    EnemyUpdate();
}

void Luke::SwitchImage()
{
   switch (_enemyStatement)
    {
   case ENEMYSTATEMENT::INIT:
       _imageName = IMAGEMANAGER->findImage("LUKE_INIT");
       if (_direction == -1)
       {
           _motionName = KEYANIMANAGER->findAnimation("LUKEleftInit");
       }
       else if (_direction == 1)
       {
           _motionName = KEYANIMANAGER->findAnimation("LUKErightInit");
       }
       break;

    case ENEMYSTATEMENT::IDLE:
        _imageName = IMAGEMANAGER->findImage("LUKE_IDLE");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftIdle");
        }
        else if(_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightIdle");
        }
        break;

    case ENEMYSTATEMENT::WANDER:
        _imageName = IMAGEMANAGER->findImage("LUKE_WALK");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftWalk");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightWalk");
        }
        break;
    case ENEMYSTATEMENT::CHASE:
        _imageName = IMAGEMANAGER->findImage("LUKE_RUN");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftRun");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightRun");
        }
        break;
    case ENEMYSTATEMENT::JUMP:
        _imageName = IMAGEMANAGER->findImage("LUKE_JUMP");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftJump");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightJump");
        }
        break;
    case ENEMYSTATEMENT::FALL:
        _imageName = IMAGEMANAGER->findImage("LUKE_JUMP");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftFall");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightFall");
        }
        break;
    case ENEMYSTATEMENT::GUARD:
        _imageName = IMAGEMANAGER->findImage("LUKE_GUARD");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftGuard");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightGuard");
        }
        break;
    case ENEMYSTATEMENT::DOWN:
        _imageName = IMAGEMANAGER->findImage("LUKE_DOWN");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftDown");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightDown");
        }
        break;

    case ENEMYSTATEMENT::DAMAGED:
        _imageName = IMAGEMANAGER->findImage("LUKE_DAMAGED");
        if (_direction == -1)
        {
            if(_randomHit == 0 ) _motionName = KEYANIMANAGER->findAnimation("LUKE_LEFT_DAMAGED_1");
            else _motionName = KEYANIMANAGER->findAnimation("LUKE_LEFT_DAMAGED_2");
        }
        else
        {
            if (_randomHit == 0) _motionName = KEYANIMANAGER->findAnimation("LUKE_RIGHT_DAMAGED_1");
            else _motionName = KEYANIMANAGER->findAnimation("LUKE_RIGHT_DAMAGED_2");
        }
        break;

    case ENEMYSTATEMENT::ATTACK:
        if(_attackCount < 2)_imageName = IMAGEMANAGER->findImage("LUKE_PUNCH");
        else if (_attackCount == 2)_imageName = IMAGEMANAGER->findImage("LUKE_KICK");
        else _imageName = IMAGEMANAGER->findImage("LUKE_FINISHKICK");

        if (_direction == -1)
        {
            switch (_attackCount)
            {
                case 0: _motionName = KEYANIMANAGER->findAnimation("LUKE_LEFT_PUNCH_1");
                    break;
                case 1: _motionName = KEYANIMANAGER->findAnimation("LUKE_LEFT_PUNCH_2");
                    break;
                case 2: _motionName = KEYANIMANAGER->findAnimation("LUKE_LEFT_KICK");
                    break;
                case 3: _motionName = KEYANIMANAGER->findAnimation("LUKE_LEFT_FINISHKICK");
                    break;
            }
        }
        else
        {
            switch (_attackCount)
            {
            case 0: _motionName = KEYANIMANAGER->findAnimation("LUKE_RIGHT_PUNCH_1");
                break;
            case 1: _motionName = KEYANIMANAGER->findAnimation("LUKE_RIGHT_PUNCH_2");
                break;
            case 2: _motionName = KEYANIMANAGER->findAnimation("LUKE_RIGHT_KICK");
                break;
            case 3: _motionName = KEYANIMANAGER->findAnimation("LUKE_RIGHT_FINISHKICK");
                break;
            }
        }
        break;

    case ENEMYSTATEMENT::GETUP:
        _imageName = IMAGEMANAGER->findImage("LUKE_UP");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKEleftUp");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LUKErightUp");
        }
        break;

    }
    _motionName->resume();
}





