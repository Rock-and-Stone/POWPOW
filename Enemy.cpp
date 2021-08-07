#include "pch.h"
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

HRESULT Enemy::init()
{
    return S_OK;
}

HRESULT Enemy::init(const char* imageName, const char* animationName, POINT position)
{

#pragma region STATES
    _idle = new EnemyIdle;
    _walk = new EnemyWalk;
    _run = new EnemyRun;
    _jump = new EnemyJump;
    _attack1 = new EnemyAttack1;
    _attack2 = new EnemyAttack2;
    _attack3 = new EnemyAttack3;
    _attack4 = new EnemyAttack4;
    _damaged = new EnemyDamaged;
    _down = new EnemyDown;
    _up = new EnemyUp;
    _guard = new EnemyGuard;

    _idle->SetEnemy(this);
    _walk->SetEnemy(this);
    _run->SetEnemy(this);
    _jump->SetEnemy(this);
    _attack1->SetEnemy(this);
    _attack2->SetEnemy(this);
    _attack3->SetEnemy(this);
    _attack4->SetEnemy(this);
    _damaged->SetEnemy(this);
    _down->SetEnemy(this);
    _up->SetEnemy(this);
    _guard->SetEnemy(this);

    _state = _idle;
    _direction = 0;
    _enemyStatement = ENEMYSTATEMENT::IDLE;

#pragma endregion
    _imageName = IMAGEMANAGER->findImage(imageName);

    _motionName = KEYANIMANAGER->findAnimation(animationName);
    _motionName->GetNowPlayIdx();

    _posX = position.x;
    _posY = position.y;

    _gravity = _jumpPower = 0;

    _rc = RectMakeCenter(_posX, _posY,
        _imageName->getFrameWidth(), _imageName->getFrameHeight());

    _motionName->start();

   
    

    return S_OK;
}

void Enemy::release()
{
}

void Enemy::update()
{

}

void Enemy::render()
{
    Draw();
}

void Enemy::Move()
{
    if (_isJump)
    {
        _gravity = 0.18f;
        _posY -= _jumpPower;
        _jumpPower -= _gravity;
    }
    else
    {
        _gravity = 0;
        _jumpPower = 0;
    }
}

void Enemy::Draw()
{
    _imageName->aniRender(getMemDC(), _rc.left - _cm->getCamX() , _rc.top - _cm->getCamY(), _motionName);
    LineMake(getMemDC(), _posX, _posY, _player->getPosX(), _player->getPosY());

}

void Enemy::Collision()
{
}

void Enemy::TracePlayer() // 플레이어 추적하여 좌우 변경
{
    if (_player->getPosX() < _posX && _direction == 1)
    {
        _direction = 0;
        SwitchImage();

    }
    else if (_player->getPosX() >= _posX && _direction == 0)
    {
        _direction = 1;
        SwitchImage();
    }
}

void Enemy::ChangeStatement()
{
    
    switch (_enemyStatement)
    {
    case ENEMYSTATEMENT::IDLE:
        _state = _idle;
        break;
    case ENEMYSTATEMENT::WALK:
        _state = _walk;
        break;
    case ENEMYSTATEMENT::RUN:
        _state = _run;
        break;
    case ENEMYSTATEMENT::JUMP:
        _state = _jump;
        break;
    case ENEMYSTATEMENT::GUARD:
        _state = _guard;
        break;
    case ENEMYSTATEMENT::DOWN:
        _state = _down;
        break;
    case ENEMYSTATEMENT::DAMAGED:
        _state = _damaged;
        break;
    case ENEMYSTATEMENT::ATTACK1:
        _state = _attack1;
        break;
    case ENEMYSTATEMENT::ATTACK2:
        _state = _attack2;
        break;
    case ENEMYSTATEMENT::ATTACK3:
        _state = _attack3;
        break;
    case ENEMYSTATEMENT::ATTACK4:
        _state = _attack4;
        break;
    case ENEMYSTATEMENT::UP:
        _state = _up;
        break;
    case ENEMYSTATEMENT::DAEGI:
        _state = _daegi;
        break;
    }
    SwitchImage();
    _state->init();

}

bool Enemy::ChaseSession()
{
    if (getDistance(_player->getPosX(), _player->getPosY(), _posX, _posY) < 300)
    {
        return true;
    }
    else return false;

}

bool Enemy::AttackSession()
{
    if (ChaseSession() && getDistance(_player->getPosX(), _player->getPosY(), _posX, _posY) < 30)
    {
        return true;
    }
    return false;
}



