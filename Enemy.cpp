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
    _daegi = new EnemyDaegi;
    _fall = new EnemyFall;


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
    _daegi->SetEnemy(this);
    _fall->SetEnemy(this);

    _state = _idle;
    _direction = 0;
    _enemyStatement = ENEMYSTATEMENT::IDLE;

#pragma endregion
    _imageName = IMAGEMANAGER->findImage(imageName);

    _motionName = KEYANIMANAGER->findAnimation(animationName);
    _motionName->GetNowPlayIdx();

    _posX = position.x;
    _posY = position.y;
    _airY = 0;

    _hp = 100;

    _gravity = _jumpPower = 0;

    _isAir = false;

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
    if (_isAir)
    {
        _gravity = 0.18f;
        _airY -= _jumpPower;
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
    _distance = getDistance(_player->getPosX(), _player->getPosY(), _posX, _posY);
    //_objectDistance = getDistance(_object->GetObjectPosX(), _object->GetObjectPosY(), _posX, _posY);

    _rendX = _posX  - _cm->getCamX();
    _rendY = _posY  - _cm->getCamY();

    //Rectangle(getMemDC(), _rc);
    _rc = RectMakeCenter(_rendX, _rendY, _imageName->getFrameWidth(), _imageName->getFrameHeight());

    _randomChoice = RND->getFromIntTo(0, 1);

    _imageName->aniRender(getMemDC(), _rc.left , _rc.top, _motionName);
    LineMake(getMemDC(), _rendX, _rendY, _player->getRendX(), _player->getRendY());
    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        Rectangle(getMemDC(), _attackRect);
        Rectangle(getMemDC(), _attackComboRect);
    }
   

}

void Enemy::Collision()
{
}

void Enemy::TracePlayer() // 플레이어 추적하여 좌우 변경
{
    if (_enemyStatement != ENEMYSTATEMENT::DAMAGED)
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
    //만약 플레이어가 에너미보다 위에 있으면
    if (_player->getPosY() - 50 < _posY)
    {
        _highlow = -1;
    }
    //만약 플레이어가 에너미보다 아래에 있으면
    if (_player->getPosY() + 50 > _posY)
    {
        _highlow = 1;
    }
    else
    {
        _highlow = 0;
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
    case ENEMYSTATEMENT::FALL:
        _state = _fall;
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

void Enemy::ChaseRun()
{
    if (ChaseSession())
    {
        if (_player->getPosX() + 80 < _posX)
        {
            _posX -= ENEMYSPEED;
        }
        if (_player->getPosX() - 80 > _posX)
        {
            _posX += ENEMYSPEED;
        }
        if (_player->getPosY() > _posY)
        {
            _posY += 3;
        }
        if (_player->getPosY() < _posY)
        {
            _posY -= 3;
        }
    }
}

void Enemy::ChaseWalk()
{
    if (WalkSession())
    {
        if (_player->getPosX() + 80 < _posX)
        {
            _posX -= 2;
        }
        if (_player->getPosX() - 80 > _posX)
        {
            _posX += 2;
        }
        if (_player->getPosY() > _posY)
        {
            _posY += 2;
        }
        if (_player->getPosY() < _posY)
        {
            _posY -= 2;
        }
    }
}

void Enemy::ChaseObject()
{
    if (WalkSession())
    {
        /*if (_object->GetObjectPosX() < _posX)
        {
            _posX -= 2;
        }
        if (_object->GetObjectPosX() > _posX)
        {
            _posX += 2;
        }
        if (_object->GetObjectPosY() > _posY)
        {
            _posY += 2;
        }
        if (_object->GetObjectPosY() < _posY)
        {
            _posY -= 2;
        }*/
    }
}

void Enemy::MakeAttackRect()
{
    if (AttackSession())
    {
        if (_direction == 0)
        {
            _attackRect = RectMakeCenter(_rendX-60, _rendY, 50, 50);
        }
        else  _attackRect = RectMakeCenter(_rendX + 60, _rendY, 50, 50);
       
    }
    else _attackRect = RectMakeCenter(0, 0, 0, 0);

    if (ComboSession())
    {
        if (_direction == 0)
        {
            _attackComboRect = RectMakeCenter(_rendX - 60, _rendY, 50, 50);
        }
        else _attackComboRect = RectMakeCenter(_rendX + 60, _rendY, 50, 50);
    }
    else _attackComboRect = RectMakeCenter(0, 0, 0, 0);
}

float Enemy::getRenderPosY()
{
    return _posY;
}

bool Enemy::ChaseSession()
{
    if (_distance < 500)
    {
        return true;
    }
    else return false;

}

bool Enemy::WalkSession()
{
    if (_distance < WINSIZEX)
    {
        return true;
    }
    return false;
}

bool Enemy::AttackSession()
{
    if (ChaseSession() && _distance <= 82 && _enemyStatement != ENEMYSTATEMENT::DAEGI && _enemyStatement != ENEMYSTATEMENT::ATTACK2 && _enemyStatement != ENEMYSTATEMENT::ATTACK4)
    {
        return true;
    }
    return false;
}

bool Enemy::ComboSession()
{
    if (_enemyStatement == ENEMYSTATEMENT::ATTACK2 || _enemyStatement == ENEMYSTATEMENT::ATTACK4)
    {
        return true;
    }
    return false;
}

bool Enemy::ObjectSession()
{
    if (_objectDistance < 500)
    {
        return true;
    }
    return false;
}

void Enemy::HitDamage(int Damage)
{
    _rndSelection = RND->getInt(2);

    if (_enemyStatement != ENEMYSTATEMENT::DAMAGED && _enemyStatement != ENEMYSTATEMENT::GUARD)
    {
        if (_rndSelection == 0)
        {
            _enemyStatement = ENEMYSTATEMENT::DAMAGED;
            ChangeStatement();
        }
        if (_rndSelection == 1)
        {
            _enemyStatement = ENEMYSTATEMENT::GUARD;
            ChangeStatement();
        }
    }
}






