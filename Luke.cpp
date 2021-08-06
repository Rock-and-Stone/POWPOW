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
	_hp = 300;

	return S_OK;
}

void Luke::release()
{
}

void Luke::update()
{
	_state->update();
	Move();
	SwitchImage();
	
}

void Luke::SwitchImage()
{
    switch (_enemyStatement)
    {
    case ENEMYSTATEMENT::IDLE:
        _imageName = IMAGEMANAGER->findImage("LUKE_IDLE");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LukeleftIdle");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LukerightIdle");
        }
        break;
    case ENEMYSTATEMENT::WALK:
        _imageName = IMAGEMANAGER->findImage("LUKE_WALK");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LukeleftWalk");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LukerightWalk");
        }
        break;
    case ENEMYSTATEMENT::RUN:
        _imageName = IMAGEMANAGER->findImage("LUKE_RUN");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LukeleftRUN");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LukerightRUN");
        }
        break;
    case ENEMYSTATEMENT::JUMP:
        _imageName = IMAGEMANAGER->findImage("LUKE_JUMP");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LukeleftJUMP");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LukerightJUMP");
        }
        break;
    case ENEMYSTATEMENT::GUARD:
        _imageName = IMAGEMANAGER->findImage("LUKE_GUARD");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LukeleftGUARD");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LukerightGUARD");
        }
        break;
    case ENEMYSTATEMENT::DOWN:
        _imageName = IMAGEMANAGER->findImage("LUKE_DOWN");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LukeleftDOWN");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LukerightDOWN");
        }
        break;
    case ENEMYSTATEMENT::DAMAGED:
        _imageName = IMAGEMANAGER->findImage("LUKE_DAMAGED");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LukeleftDAMAGED");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LukerightDAMAGED");
        }
        break;
    case ENEMYSTATEMENT::ATTACK1:
        _imageName = IMAGEMANAGER->findImage("LUKE_ATTACK1");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LukeleftATTACK1");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LukerightATTACK1");
        }
        break;
    case ENEMYSTATEMENT::ATTACK3:
        _imageName = IMAGEMANAGER->findImage("LUKE_ATTACK3");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LukeleftATTACK3");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LukerightATTACK3");
        }
        break;
    case ENEMYSTATEMENT::UP:
        _imageName = IMAGEMANAGER->findImage("LUKE_UP");
        if (_direction == 0)
        {
            _motionName = KEYANIMANAGER->findAnimation("LukeleftUP");
        }
        else
        {
            _motionName = KEYANIMANAGER->findAnimation("LukerightUP");
        }
        break;

    }


}


//약공격 콤보어택 콜백함수
void Luke::ComboAttack1(void* obj)
{
    Enemy* e = (Enemy*)obj;

    e->SetEnemyStatement(ENEMYSTATEMENT::ATTACK1);
    e->SetMotionName(KEYANIMANAGER->findAnimation("LUKEleftAttack2"));
    e->GetMotionName()->start();
}

//강공격 콤보어택 콜백함수
void Luke::ComboAttack2(void* obj)
{
    Enemy* e = (Enemy*)obj;

    e->SetEnemyStatement(ENEMYSTATEMENT::ATTACK1);
    e->SetMotionName(KEYANIMANAGER->findAnimation("LUKEleftAttack2"));
    e->GetMotionName()->start();
}



