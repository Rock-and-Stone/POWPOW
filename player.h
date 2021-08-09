#pragma once
#include "gameNode.h"
#include "CameraManager.h"
#include "State.h"

#define MAXSPEEDX 4.0f
#define MAXSPEEDY 2.0f

enum class Statement
{
	IDLE,
	RUN,
	WALK,
	JUMP,
	FALL,
	LAND,
	ATTACK
};

class player : public gameNode
{
protected:


	Statement		_statement;
	RECT			_renderRC;
	RECT			_hitRC;
	RECT			_attackRC;
	image*			_img;

	State*			_state;
	Idle*			_idle;
	Walk*			_walk;
	Jump*			_jump;
	Fall*			_fall;
	Attack*			_attack;

	int				_dirX, _dirY;	// 플레이어의 X축과 Y축 진행 방향 
	int				_indexX, _indexY;		// 현재 애니메이션 프레임
	int				_count;			
	int				_atkCount;		// 공격 카운트 
	int				_jumpCount;		// 현재 점프 횟수

	int				_maxHp, _currentHP; // 최대 체력, 현재 체력

	bool			_animLoop;		// 애니메이션이 루프인지 여부
	bool			_trigger;		// 애니메이션이 끝났을때 작동하는 트리거
	bool			_isAttack;		// 공격 상태인지 여부
	bool			_isAir;			// 공중 상태인지 여부
	bool			_isRoll;
	bool			_isRun;

	float			_posX, _posY;	// 실제 좌표
	float			_probeX, _probeY;
	float			_groundY, _airY;	// 바닥 좌표값과 땅에서 공중까지의 Y값
	float			_jumpPower, _gravity; // 점프력 

	float			_rendX, _rendY; 
	float			_speedX, _speedY;
	float			_maxSpeedX, _maxSpeedY;
	float			_speedRes;

	

public:
	player();
	~player();

	virtual HRESULT InitVariables();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Movement(); //실제 이동 관련 함수

	void CountFrame(); //이미지 프레임 함수

	void Collision(); 

	void hitDamage(int damage);

	void ChangeState(Statement statement); //상태 변경 함수

	void AttackCollision();

	bool getTrigger() { return _trigger; } //애니메이션 프레임이 끝났을때 작동하는 트리거 접근자

	virtual float getRenderPosY();	//렌더매니저에 보내주는 기준 값

	Statement getStatement() { return _statement; }
	void SetStatement(Statement statement) { _statement = statement; }

	void setAnimLoop(bool loop) { _animLoop = loop; }

	RECT getAttackRC() { return _attackRC; }
	RECT getHitRC() { return _hitRC; }

	int  getIndexX() { return _indexX; }
	void setIndexX(int indexX) { _indexX = indexX; }

	float getJumpPower() { return _jumpPower; }
	void setJumpPower(float jumpPower) { _jumpPower = jumpPower; }

	float getAirY() { return _airY; }	
	void setAirY(float airY) { _airY = airY; }

	float getPosX() { return _posX; }
	void setPosX(float posX) { _posX = posX; }

	float getPosY() { return _posY; }
	void setPosY(float posY) { _posY = posY; }

	float getGroundY() { return _groundY; }

	bool getIsAir() { return _isAir; }
	void setIsAir(bool isAir) { _isAir = isAir; }

	float getRenderY() { return _hitRC.bottom; }

	float getRendX() { return _rendX; }
	void setRendX(int rendX) { _rendX = rendX; }


	float getRendY() { return _rendY; }
	void setRendY(int rendY) { _rendY = rendY; }

	int getDirectionX() { return _dirX; }
	void setDirectionX(int dirX) { _dirX = dirX; }

	int getDirectionY() { return _dirY; }
	void setDirectionY(int dirY) { _dirY = dirY; }

	float getSpeedX() { return _speedX; }
	void setSpeedX(float speedX) { _speedX = speedX; }

	float getSpeedY() { return _speedY; }
	void setSpeedY(float speedY) { _speedY = speedY; }

	bool getIsRun() { return _isRun; }
	void setIsRun(bool isRun) { _isRun = isRun; }

	int getAtkCount() { return _atkCount; }
	void setAtkCount(int atkCount) { _atkCount = atkCount; }
};

