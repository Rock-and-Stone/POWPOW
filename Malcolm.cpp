#include "pch.h"
#include "Malcolm.h"

Malcolm::Malcolm()
{
}

Malcolm::~Malcolm()
{
}

HRESULT Malcolm::init()
{

	_searchRange = 500;
	_attackRange = 130;
	_maxHP = _currentHP = 300;

	return S_OK;
}

void Malcolm::release()
{
}

void Malcolm::update()
{
	_state->update();
	EnemyUpdate();
}

void Malcolm::SwitchImage()
{
    switch (_enemyStatement)
    {
    case ENEMYSTATEMENT::INIT:
        _imageName = IMAGEMANAGER->findImage("MALCOLM_IDLE");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftIdle");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightIdle");
        }
        break;

    case ENEMYSTATEMENT::IDLE:
        _imageName = IMAGEMANAGER->findImage("MALCOLM_IDLE");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftIdle");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightIdle");
        }
        break;

    case ENEMYSTATEMENT::WANDER:
        _imageName = IMAGEMANAGER->findImage("MALCOLM_WALK");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftWalk");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightWalk");
        }
        break;

    case ENEMYSTATEMENT::CHASE:
        _imageName = IMAGEMANAGER->findImage("MALCOLM_RUN");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftRun");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightRun");
        }
        break;
    case ENEMYSTATEMENT::JUMP:
        _imageName = IMAGEMANAGER->findImage("MALCOLM_JUMP");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftJump");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightJump");
        }
        break;
    case ENEMYSTATEMENT::FALL:
        _imageName = IMAGEMANAGER->findImage("MALCOLM_JUMP");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftFall");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightFall");
        }
        break;
    case ENEMYSTATEMENT::GUARD:
        _imageName = IMAGEMANAGER->findImage("MALCOLM_GUARD");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftGuard");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightGuard");
        }
        break;
    case ENEMYSTATEMENT::DOWN:
        _imageName = IMAGEMANAGER->findImage("MALCOLM_DOWN");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftDown");
        }
        else if (_direction == 1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightDown");
        }
        break;

    case ENEMYSTATEMENT::DAMAGED:
        _imageName = IMAGEMANAGER->findImage("MALCOLM_DAMAGED");
        if (_direction == -1)
        {
            if (_randomHit == 0) _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftDamaged");
            else _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftDamaged");
        }
        else
        {
            if (_randomHit == 0) _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightDamaged");
            else _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightDamaged");
        }
        break;

    case ENEMYSTATEMENT::ATTACK:
        if (_attackCount < 2)_imageName = IMAGEMANAGER->findImage("MALCOLM_ATTACK1");
        else if (_attackCount == 2)_imageName = IMAGEMANAGER->findImage("MALCOLM_ATTACK2");
        else _imageName = IMAGEMANAGER->findImage("MALCOLM_ATTACK3");

        if (_direction == -1)
        {
            switch (_attackCount)
            {
            case 0: _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftAttack1");
                break;
            case 1: _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftAttack2");
                break;
            case 2: _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftAttack3");
                break;
            case 3: _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftAttack4");
                break;
            }
        }
        else
        {
            switch (_attackCount)
            {
            case 0: _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightAttack1");
                break;
            case 1: _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightAttack2");
                break;
            case 2: _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightAttack3");
                break;
            case 3: _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightAttack4");
                break;
            }
        }
        break;

    case ENEMYSTATEMENT::GETUP:
        _imageName = IMAGEMANAGER->findImage("MALCOLM_UP");
        if (_direction == -1)
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMleftUp");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("MALCOLMrightUp");
        }
        break;

    }
    _motionName->resume();
}

