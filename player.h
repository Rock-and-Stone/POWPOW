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
	ATTACK,
	DAMAGED,
	DOWN,
	GETUP
};

class player : public gameNode
{
protected:


	Statement		_statement;		//현재 상태 Enum
	RECT			_renderRC;		//이미지 렌더를 위한 렉트
	RECT			_hitRC;			//히트박스 렉트
	RECT			_attackRC;		//공격 렉트
	RECT			_shadowRC;
	image*			_img;			//현재 이미지
	image*			_shadow;

	State*			_state;			//현재 상태 (이하 자식 상태들)
	Idle*			_idle;
	Move*			_move;
	Jump*			_jump;
	Fall*			_fall;
	Attack*			_attack;
	Damaged*		_damaged;
	Down*			_down;
	GetUp*			_getUp;

	int				_dirX, _dirY;	// 플레이어의 X축과 Y축 진행 방향 
	int				_indexX, _indexY;		// 현재 애니메이션 프레임
	int				_count;			//프레임 카운트
	int				_atkCount;		// 공격 카운트 
	int				_jumpCount;		// 현재 점프 횟수
	int				_hitCount;
	int				_maxHP, _currentHP; // 최대 체력, 현재 체력
	int				_coin;

	bool			_animLoop;		// 애니메이션이 루프인지 여부
	bool			_trigger;		// 애니메이션이 끝났을때 작동하는 트리거
	bool			_isAttack;		// 공격 상태인지 여부
	bool			_isAir;			// 공중 상태인지 여부
	bool			_isRoll;		// 구르는 상태인지 여부
	bool			_isRun;			// 달리는 상태인지 여부
	bool			_isVulnerable;	// 맞을수 있는 상태인지 여부

	float			_posX, _posY;	// 실제 좌표
	float			_probeX, _probeY;	//픽셀 콜라이더 검색값
	float			_airY;				//땅에서 공중까지의 Y값
	float			_jumpPower, _gravity; // 점프력, 중력값

	float			_rendX, _rendY;		//렌더를 위한 X, Y 값
	float			_shadowY;
	float			_speedX, _speedY;	//속도 X, Y
	float			_maxSpeedX, _maxSpeedY; //최대속도 X, Y
	float			_speedRes;			// 속도 마찰값

	

public:
	player();
	~player();

	virtual HRESULT InitVariables();
	virtual HRESULT init(float posX, float posY);

	virtual void release();
	virtual void update();
	virtual void render();

	void Movement(); //실제 이동 관련 함수

	void CountFrame(); //이미지 프레임 함수

	void Collision(); 

	void coinGet(int coin);

	void hitDamage(int damage); // 피격 함수

	void ChangeState(Statement statement); //상태 변경 함수

	void AttackCollision();

#pragma region GETSET

	bool getIsVulnerable() { return _isVulnerable; }
	void setIsVulnuerable(bool isvul) { _isVulnerable = isvul; }

	bool getTrigger() { return _trigger; } //애니메이션 프레임이 끝났을때 작동하는 트리거 접근자

	virtual float getRenderPosY();	//렌더매니저에 보내주는 기준 Y값

	Statement getStatement() { return _statement; }
	void SetStatement(Statement statement) { _statement = statement; }

	void setAnimLoop(bool loop) { _animLoop = loop; }

	RECT getAttackRC() { return _attackRC; }
	RECT getHitRC() { return _hitRC; }

	bool getIsAttack() { return _isAttack; }
	void setIsAttack(bool isAtk) { _isAttack = isAtk; }
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

	void setShadowY(float shadowY) { _shadowY = shadowY; }

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

	int getCoin() { return _coin; }
	void setCoin(int coin) { _coin = coin; }


	int getCurrentHp() { return _currentHP; }


#pragma endregion
};

