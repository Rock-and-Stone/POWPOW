#include "pch.h"
#include "Mike.h"

Mike::Mike()
{
}

Mike::~Mike()
{
}

HRESULT Mike::init()
{
	_searchRange = 700;
	_attackRange = 100;
	_maxHP = _currentHP = 150;
	return S_OK;
}

void Mike::release()
{
}

void Mike::update()
{
	_state->update();
	EnemyUpdate();
}

void Mike::SwitchImage()
{
    switch (_enemyStatement)
    {
    case ENEMYSTATEMENT::IDLE:
        _imageName = IMAGEMANAGER->findImage("MIKE_IDLE");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftIdle");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightIdle");
        }
        break;
    case ENEMYSTATEMENT::WALK:
        _imageName = IMAGEMANAGER->findImage("MIKE_WALK");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftWalk");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightWalk");
        }
        break;

    case ENEMYSTATEMENT::WANDER:
        _imageName = IMAGEMANAGER->findImage("MIKE_WALK");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftWalk");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightWalk");
        }
        break;
    case ENEMYSTATEMENT::RUN:
        _imageName = IMAGEMANAGER->findImage("MIKE_RUN");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftRun");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightRun");
        }
        break;
    case ENEMYSTATEMENT::JUMP:
        _imageName = IMAGEMANAGER->findImage("MIKE_JUMP");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftJump");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightJump");
        }
        break;
    case ENEMYSTATEMENT::FALL:
        _imageName = IMAGEMANAGER->findImage("MIKE_JUMP");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftFall");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightFall");
        }
        break;
    case ENEMYSTATEMENT::GUARD:
        _imageName = IMAGEMANAGER->findImage("MIKE_GUARD");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftGuard");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightGuard");
        }
        break;
    case ENEMYSTATEMENT::DOWN:
        _imageName = IMAGEMANAGER->findImage("MIKE_DOWN");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftDown");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightDown");
        }
        break;

    case ENEMYSTATEMENT::DAMAGED:
        _imageName = IMAGEMANAGER->findImage("MIKE_DAMAGED");
        if (_direction == -1)
        {
            if (_randomHit == 0) _motionName = KEYANIMANAGER->findAnimation("MIKEleftDamaged");
            else _motionName = KEYANIMANAGER->findAnimation("MIKEleftDamaged");
        }
        else
        {
            if (_randomHit == 0) _motionName = KEYANIMANAGER->findAnimation("MIKErightDamaged");
            else _motionName = KEYANIMANAGER->findAnimation("MIKErightDamaged");
        }
        break;

    case ENEMYSTATEMENT::ATTACK:
        if (_attackCount < 2)_imageName = IMAGEMANAGER->findImage("MIKE_ATTACK1");
        else if (_attackCount == 2)_imageName = IMAGEMANAGER->findImage("MIKE_ATTACK2");
        else _imageName = IMAGEMANAGER->findImage("MIKE_ATTACK3");

        if (_direction == -1)
        {
            switch (_attackCount)
            {
            case 0: _motionName = KEYANIMANAGER->findAnimation("MIKEleftAttack1");
                break;
            case 1: _motionName = KEYANIMANAGER->findAnimation("MIKEleftAttack2");
                break;
            case 2: _motionName = KEYANIMANAGER->findAnimation("MIKEleftAttack3");
                break;
            case 3: _motionName = KEYANIMANAGER->findAnimation("MIKEleftAttack4");
                break;
            }
        }
        else
        {
            switch (_attackCount)
            {
            case 0: _motionName = KEYANIMANAGER->findAnimation("MIKErightAttack1");
                break;
            case 1: _motionName = KEYANIMANAGER->findAnimation("MIKErightAttack2");
                break;
            case 2: _motionName = KEYANIMANAGER->findAnimation("MIKErightAttack3");
                break;
            case 3: _motionName = KEYANIMANAGER->findAnimation("MIKErightAttack4");
                break;
            }
        }
        break;

    case ENEMYSTATEMENT::GETUP:
        _imageName = IMAGEMANAGER->findImage("MIKE_UP");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftUp");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightUp");
        }
        break;

    }
    _motionName->resume();
}

