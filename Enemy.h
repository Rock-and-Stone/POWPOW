#pragma once
#include "gameNode.h"
#include "CameraManager.h"
#include "EnemyIdle.h"
#include "EnemyWalk.h"
#include "EnemyRun.h"
#include "EnemyJump.h"
#include "EnemyAttack1.h"
#include "EnemyAttack2.h"
#include "EnemyAttack3.h"
#include "EnemyAttack4.h"
#include "EnemyDamaged.h"
#include "EnemyGuard.h"
#include "EnemyDown.h"
#include "EnemyUp.h"
#include "EnemyDaegi.h"
#include "EnemyFall.h"
#include "player.h"

#define ENEMYSPEED 5

//에너미 방향 enum 클래스
//enum class ENEMYDIRECTION
//{
//	LEFT,
//	RIGHT
//};

//에너미 상태 enum 클래스
enum class ENEMYSTATEMENT
{
	INIT,						//등장
	IDLE,						//기본
	WALK,						//걷기
	RUN,						//뛰기
	JUMP,						//점프
	FALL,						//떨어짐
	ATTACK1,					//약공격1
	ATTACK2,					//약공격2(콤보)
	ATTACK3,					//강공격1
	ATTACK4,					//강공격2(콤보)
	DAMAGED,					//피격
	DOWN,						//피격시 다운(죽음)
	DOWN_DAMAGED,				//누운상태에서의 피격
	DOWN_ATTACK,				//누운상태에서 공격
	UP,							//누운상태에서 일어나기
	GUARD,						//가드
	OBJECT_ATTACK,				//오브젝트 들고 공격
	OBJECT_THROW,				//오브젝트 던지기
	OBJECT_GRAB,				//오브젝트 들기
	DAEGI						//말그대로 대기상태
};

class Enemy : public gameNode
{
protected:
	//ENEMYDIRECTION _enemyDirection;
	ENEMYSTATEMENT _enemyStatement;
	CameraManager* _cm;

	player* _player;
	image* _imageName;
	animation* _motionName;
	RECT _rc;

	//상태패턴
	EnemyState* _state;
	EnemyIdle* _idle;
	EnemyWalk* _walk;
	EnemyRun* _run;
	EnemyJump* _jump;
	EnemyAttack1* _attack1;
	EnemyAttack2* _attack2;
	EnemyAttack3* _attack3;
	EnemyAttack4* _attack4;
	EnemyDamaged* _damaged;
	EnemyDown* _down;
	EnemyGuard* _guard;
	EnemyUp* _up;
	EnemyDaegi* _daegi;
	EnemyFall* _fall;
	
	
	int _direction;			//에너미의 방향
	int _highlow;			//에너미 높낮이 (플레이어와의 비교)
	int _randomChoice;		//막기, 맞기 랜덤값

	bool _isAir;

	float _posX, _posY;				//에너미 x, y 좌표
	float _rendX, _rendY;
	float _probeX, _probeY;			//픽셀 충돌 시
	float _jumpPower, _gravity;		//점프, 중력
	float _distance; //플레이어와의 거리 계산
	float _attackRange;
	float _searchRange;
	float _airY;

	int _hp;	//플레이어 체력
	int _rndSelection;
	

public:
	Enemy();
	~Enemy();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, const char* animationName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void SwitchImage() = 0;

	void Move();
	void Draw();

	void Collision();

	void TracePlayer();
	
	void ChangeStatement();


	void ChaseRun();
	void ChaseWalk();

	


	//에너미 렉트 접근자
	inline RECT GetRect() { return _rc; }

	//에너미 상태 설정자, 접근자
	void SetEnemyStatement(ENEMYSTATEMENT enemyStatement) { _enemyStatement = enemyStatement; }
	ENEMYSTATEMENT GetEnemyStatement() { return _enemyStatement; }

	//이미지 접근자
	image* GetImageName() { return _imageName; }
	

	//애니메이션 따오기
	void SetMotionName(animation* motionName) { _motionName =  motionName; }
	animation* GetMotionName() { return _motionName; }

	//카메라 설정
	void SetCamera(CameraManager* cm) { _cm = cm; }

	//에너미 x, y 좌표 설정자
	float GetEnemyPosX() { return _posX; }
	float GetEnemyPosY() { return _posY; }

	void SetEnemyPosX(float x) { _posX = x; }
	void SetEnemyPosY(float y) { _posY = y; }

	//에너미 그림 좌표 받아오기
	float GetEnemyRendX() { return _rendX; }
	float GetEnemyRendY() { return _rendY; }

	//에너미 방향 받아오기
	int GetEnemyDirection() { return _direction; }

	//점프 상태 받아오기
	void SetJumpPower(float jumpPower) { _jumpPower = jumpPower; }
	void SetIsAir(bool air) { _isAir = air; }
	float GetJumpPower() { return _airY; }

	virtual float getRenderPosY();

	bool ChaseSession();
	bool WalkSession();

	bool AttackSession();

	void SetPlayerLink(player* player) { _player = player; }

	void HitDamage();


};

