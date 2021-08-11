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
    _move = new EnemyMove;
    _jump = new EnemyJump;
    _attack = new EnemyAttack;
    _damaged = new EnemyDamaged;
    _down = new EnemyDown;
    _getUp = new EnemyGetUp;
    _guard = new EnemyGuard;
    _fall = new EnemyFall;


    _idle->SetEnemy(this);
    _move->SetEnemy(this);
    _jump->SetEnemy(this);
    _attack->SetEnemy(this);
    _damaged->SetEnemy(this);
    _down->SetEnemy(this);
    _getUp->SetEnemy(this);
    _guard->SetEnemy(this);
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

    _hitGauge = _hitCount = 0;

    _gravity = _jumpPower = 0;

    _isAir = false;
    _isAttack = false;
    _isTrace = true;
    _isChange = false;

    _speedX = _speedY = 0;
    _speedRes = 0.52f;
    _stateCount = 0;
    _wanderDirX = 1;

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

void Enemy::EnemyUpdate()
{
    Move();
    TracePlayer();
    MakeAttackRect();
    DownGauge();
    StateCount();
    SwitchImage();
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

    if (_enemyStatement == ENEMYSTATEMENT::WANDER)
    {
        if (_direction == -1) _posX -= _speedX * _wanderDirX;
        else if (_direction == 1)_posX += _speedX * _wanderDirX;

        if (_highlow == -1) _posY -= _speedY * _wanderDirY;
        else if (_highlow == 1)_posY += _speedY * _wanderDirY;
    }
    else
    {
        if(_isTrace)
        {
            if (_direction == -1) _posX -= _speedX;
            else if (_direction == 1)_posX += _speedX;
        }
        if (_highlow == -1) _posY -= _speedY;
        else if (_highlow == 1)_posY += _speedY;
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
    if (_player->getPosX() + 5 > _posX && _player->getPosX() - 5 < _posX)
    {
        _isTrace = false;
    }

    else if (_player->getPosX() + 5 < _posX)
    {
        _direction = -1;
        _isTrace = true;
    }
    else if (_player->getPosX() - 5 >= _posX)
    {
        _direction = 1;
        _isTrace = true;
    }

    //만약 플레이어가 에너미보다 위에 있으면
    if (_player->getPosY() + 30 < _posY)
    {
        _highlow = -1;
    }
    //만약 플레이어가 에너미보다 아래에 있으면
    else if (_player->getPosY() - 30 > _posY)
    {
        _highlow = 1;
    }
    else
    {
        _highlow = 0;
    }
}



void Enemy::ChangeStatement(ENEMYSTATEMENT enemyStatement)
{
    _enemyStatement = enemyStatement;

    switch (_enemyStatement)
    {
    case ENEMYSTATEMENT::IDLE:
        _state = _idle;
        break;
    case ENEMYSTATEMENT::WALK:
        _state = _move;
        break;
    case ENEMYSTATEMENT::RUN:
        _state = _move;
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
    case ENEMYSTATEMENT::ATTACK:
        _state = _attack;
        break;
    case ENEMYSTATEMENT::GETUP:
        _state = _getUp;
        break;
    case ENEMYSTATEMENT::WANDER:
        _state = _move;
        break;
    }
    SwitchImage();
    _stateCount = 0;
    _isTrace = true;
    _state->init();
}

void Enemy::MakeAttackRect()
{
    if (_isAttack)
    {
        if (_direction == -1)
        {
            _attackRect = RectMakeCenter(_rendX-60, _rendY, 50, 50);
        }
        else if(_direction == 1)  _attackRect = RectMakeCenter(_rendX + 60, _rendY, 50, 50);
       
    }
    else _attackRect = RectMakeCenter(0, 0, 0, 0);

    if (ComboSession())
    {
        if (_direction == -1)
        {
            _attackComboRect = RectMakeCenter(_rendX - 60, _rendY, 50, 50);
        }
        else _attackComboRect = RectMakeCenter(_rendX + 60, _rendY, 50, 50);
    }
    else _attackComboRect = RectMakeCenter(0, 0, 0, 0);

}

void Enemy::DownGauge()
{
    if (_hitGauge > 0)
    {
        _hitCount++;

        if (_hitCount % 10 == 0)
        {
            _hitGauge--;
            _hitCount = 0;
        }
    }
}

void Enemy::StateCount()
{
    _stateCount++;
    if (_stateCount % 50 == 0)
    {
        _isChange = true;
    }
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
    if (_highlow == 0 &&_distance <= 82)
    {
        return true;
    }
    return false;
}

bool Enemy::ComboSession()
{
    if (_enemyStatement == ENEMYSTATEMENT::ATTACK)
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
            ChangeStatement(ENEMYSTATEMENT::DAMAGED);
        }
        if (_rndSelection == 1)
        {
            ChangeStatement(ENEMYSTATEMENT::GUARD);
        }
    }
}






