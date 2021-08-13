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

    _init = new EnemyInit;
    _idle = new EnemyIdle;
    _wander = new EnemyWander;
    _jump = new EnemyJump;
    _attack = new EnemyAttack;
    _damaged = new EnemyDamaged;
    _down = new EnemyDown;
    _getUp = new EnemyGetUp;
    _guard = new EnemyGuard;
    _fall = new EnemyFall;
    _chase = new EnemyChase;

    _init->SetEnemy(this);
    _idle->SetEnemy(this);
    _wander->SetEnemy(this);
    _jump->SetEnemy(this);
    _attack->SetEnemy(this);
    _damaged->SetEnemy(this);
    _down->SetEnemy(this);
    _getUp->SetEnemy(this);
    _guard->SetEnemy(this);
    _fall->SetEnemy(this);
    _chase->SetEnemy(this);


    _enemyStatement = ENEMYSTATEMENT::INIT;
    _state = _init;
    _direction = -1;

#pragma endregion

    _imageName = IMAGEMANAGER->findImage(imageName);

    _motionName = KEYANIMANAGER->findAnimation(animationName);
    _motionName->GetNowPlayIdx();

    _posX = position.x;
    _posY = position.y;
    _airY = 0;

    _hitGauge = _hitCount = 0;
    _attackCount = 0;
    _gravity = _jumpPower = 0;
    _alpha = 100;

    _isDead = false;
    _isAir = false;
    _isAttack = false;
    _isTrace = true;
    _isChange = false;
    _isVulnerable = true;

    _speedX = _speedY = 0;
    _speedRes = 0.49f;
    _stateCount = 0;
    _releaseCount = 0;
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
    MakeAttackRect();
    DownGauge();
    //SwitchImage();
    pixelCollision();
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
        _airY = 0;
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
        if (_speedX > 0.1) _speedX -= _speedRes;
        else if(_speedX < -0.1) _speedX += _speedRes;
        else _speedX = 0;

        if (_speedY > 0.01) _speedY -= _speedRes;
        else _speedY = 0;
    }

    if (_speedX >= _maxSpeedX) _speedX = _maxSpeedX;
    else if (_speedX <= -_maxSpeedX) _speedX = -_maxSpeedX;

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
    _rc = RectMakeCenter(_rendX, _rendY + _airY, _imageName->getFrameWidth(), _imageName->getFrameHeight());

    _randomChoice = RND->getFromIntTo(0, 1);

    _imageName->aniRender(getMemDC(), _rc.left, _rc.top, _motionName);

    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        Rectangle(getMemDC(), _attackRect);
        Rectangle(getMemDC(), _attackComboRect);
    }
}

void Enemy::Collision()
{
}

void Enemy::pixelCollision()
{
    //픽셀 콜리전

    _probeEnemyX = _posX;
    _probeEnemyY = _posY;
    _probeEnemyRX = _posX + 40;
    _probeEnemyLX = _posX - 40;
    _probeEnemyBY = _posY + 90;

    //픽셀 윗 충돌
   

    //에너미
    for (int i = _probeEnemyBY - 5; i < _probeEnemyBY; ++i)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), _posX, i);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if ((r == 255 && g == 255 && b == 0))
        {
            //_speedY = 0;
            _posY = (i - 85);
        }
    }
   

    //픽셀 아랫 충돌
    
    //에너미
    for (int i = _probeEnemyBY + 5; i > _probeEnemyBY; --i)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), _posX, i);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if ((r == 255 && g == 255 && b == 0))
        {
            _speedY = 0;
            _posY = (i - 95);
        }
    }

    //픽셀 오른쪽 충돌
   

    //에너미
    for (int i = _probeEnemyRX + 5; i > _probeEnemyRX; --i)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(),i, _probeEnemyBY);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if ((r == 255 && g == 255 && b == 0))
        {
            _speedX = 0;
            _posX = (i - 45);
        }
    }

    //픽셀 왼쪽 충돌
  
    //에너미
    for (int i = _probeEnemyLX - 5; i < _probeEnemyLX; ++i)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("col")->getMemDC(), i, _probeEnemyBY);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if ((r == 255 && g == 255 && b == 0))
        {
            _speedX = 0;
            _posX = i + 45;
        }
    }
}



void Enemy::ChasePlayer() // 플레이어 추적하여 좌우 변경
{
    if (_isVulnerable)
    {
        if (_player->getPosX() + 10 > _posX && _player->getPosX() - 10 < _posX)
        {
            _isTrace = false;
        }

        else if (_player->getPosX() + 10 < _posX)
        {
            _direction = -1;
            _isTrace = true;
            SwitchImage();
        }
        else if (_player->getPosX() - 10 >= _posX)
        {
            _direction = 1;
            _isTrace = true;
            SwitchImage();
        }
    }
    

    //만약 플레이어가 에너미보다 위에 있으면
    if (_player->getPosY() + 10 < _posY)
    {
        _highlow = -1;
    }
    //만약 플레이어가 에너미보다 아래에 있으면
    else if (_player->getPosY() - 10 > _posY)
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
    case ENEMYSTATEMENT::INIT:
        _state = _init;
        break;
    case ENEMYSTATEMENT::IDLE:
        _state = _idle;
        break;
    case ENEMYSTATEMENT::CHASE:
        _state = _chase;
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
        _state = _wander;
        break;
    }

    _motionName->stop();
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
            _attackRect = RectMakeCenter(_rendX - 60, _rendY, 50, 50);
        }
        else if (_direction == 1)  _attackRect = RectMakeCenter(_rendX + 60, _rendY, 50, 50);

    }
    else _attackRect = RectMakeCenter(0, 0, 0, 0);
}

void Enemy::DownGauge()
{
    if (_hitGauge > 0)
    {
        _hitCount++;

        if (_hitCount % 50 == 0)
        {
            _hitGauge--;
            _hitCount = 0;
        }
    }
}

void Enemy::StateCount()
{
    _stateCount++;
    if (_stateCount % 80 == 0)
    {
        _isChange = true;
    }
}


float Enemy::getRenderPosY()
{
    return _posY;
}

bool Enemy::getReleased()
{
    if (_isDead)
    {
        _releaseCount++;
        if (_releaseCount % 50 == 0) return true;
    }
    return false;
}

bool Enemy::ChaseSession()
{
    if (_distance < 500)
    {
        return true;
    }
    else return false;
}

bool Enemy::AttackSession()
{
    if (_highlow == 0 &&_distance <= 80)
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
    _randomHit = RND->getInt(2);
    if (_isVulnerable)
    {
        if (_rndSelection == 0)
        {
            _hitGauge++;
            _currentHP -= Damage;
            ChangeStatement(ENEMYSTATEMENT::DAMAGED);
        }
        if (_rndSelection == 1)
        {
            ChangeStatement(ENEMYSTATEMENT::GUARD);
        }
    }
}






