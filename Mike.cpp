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
	return S_OK;
}

void Mike::release()
{
}

void Mike::update()
{
    _state->update();
    Move();
    TracePlayer();
}

void Mike::SwitchImage()
{
    switch (_enemyStatement)
    {
    case ENEMYSTATEMENT::IDLE:
        _imageName = IMAGEMANAGER->findImage("MIKE_IDLE");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftIdle");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightIdle");
        }
        break;
    case ENEMYSTATEMENT::WALK:
        _imageName = IMAGEMANAGER->findImage("MIKE_WALK");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftWalk");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightWalk");
        }
        break;
    case ENEMYSTATEMENT::RUN:
        _imageName = IMAGEMANAGER->findImage("MIKE_RUN");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftRun");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightRun");
        }
        break;
    case ENEMYSTATEMENT::JUMP:
        _imageName = IMAGEMANAGER->findImage("MIKE_JUMP");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftJump");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightJump");
        }
        break;
    case ENEMYSTATEMENT::GUARD:
        _imageName = IMAGEMANAGER->findImage("MIKE_GUARD");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftGuard");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightGuard");
        }
        break;
    case ENEMYSTATEMENT::DOWN:
        _imageName = IMAGEMANAGER->findImage("MIKE_DOWN");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftDown");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightDown");
        }
        break;
    case ENEMYSTATEMENT::DAMAGED:
        _imageName = IMAGEMANAGER->findImage("MIKE_DAMAGED");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftDamaged");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightDamaged");
        }
        break;
    case ENEMYSTATEMENT::ATTACK1:
        _imageName = IMAGEMANAGER->findImage("MIKE_ATTACK1");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftAttack1");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightAttack1");
        }
        break;
    case ENEMYSTATEMENT::ATTACK3:
        _imageName = IMAGEMANAGER->findImage("MIKE_ATTACK3");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftAttack3");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightAttack3");
        }
        break;
    case ENEMYSTATEMENT::UP:
        _imageName = IMAGEMANAGER->findImage("MIKE_UP");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKEleftUp");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("MIKErightUp");
        }
        break;

    }
    _motionName->start();
}

