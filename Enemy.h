#pragma once
#include "gameNode.h"
#include "CameraManager.h"
#include "EnemyState.h"
#include "player.h"
#include "Object.h"

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
	ATTACK,					    //약공격1
	DAMAGED,					//피격
	DOWN,						//피격시 다운(죽음)
	DOWN_DAMAGED,				//누운상태에서의 피격
	DOWN_ATTACK,				//누운상태에서 공격
	GETUP,							//누운상태에서 일어나기
	GUARD,						//가드
	OBJECT_ATTACK,				//오브젝트 들고 공격
	OBJECT_THROW,				//오브젝트 던지기
	OBJECT_GRAB				//오브젝트 들기
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
	RECT _attackRect;
	RECT _attackComboRect;

	//상태패턴
	EnemyState* _state;
	EnemyIdle* _idle;
	EnemyWalk* _walk;
	EnemyRun* _run;
	EnemyJump* _jump;
	EnemyAttack* _attack;
	EnemyDamaged* _damaged;
	EnemyDown* _down;
	EnemyGuard* _guard;
	EnemyGetUp* _getUp;
	EnemyFall* _fall;

	
	int _direction;					//에너미의 방향
	int _highlow;					//에너미 높낮이 (플레이어와의 비교)
	int _randomChoice;				//막기, 맞기 랜덤값

	bool _isAir;

	float _posX, _posY;				//실제 x, y 좌표
	float _rendX, _rendY;			//렌더 x, y 좌표
	float _probeX, _probeY;			//픽셀 충돌 시
	float _jumpPower, _gravity;		//점프, 중력
	float _distance;				//플레이어와의 거리 계산
	float _objectDistance;			//오브젝트와의 거리 계산
	float _attackRange;				//공격 가능한 거리
	float _searchRange;				//플레이어 감지 거리
	float _airY;					//공중 Y 좌표

	int _maxHP, _currentHP;			//최대 체력, 현재 체력
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
	void ChaseObject();

	void MakeAttackRect();


	//에너미 렉트 접근자
	inline RECT GetRect() { return _rc; }
	inline RECT GetAttackRect() { return _attackRect; }

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

	//에너미 체력 받아오기
	int GetEnemyHP() { return _currentHP; }
	void SetEnemyHP(int hp) { _currentHP = hp; }

	//점프 상태 받아오기
	float GetJumpPower() { return _jumpPower; }
	void SetJumpPower(float jumpPower) { _jumpPower = jumpPower; }
	
	bool GetIsAir() { return _isAir; }
	void SetIsAir(bool air) { _isAir = air; }

	virtual float getRenderPosY();

	bool ChaseSession();

	bool WalkSession();

	bool AttackSession();

	bool ComboSession();

	bool ObjectSession();

	void SetPlayerLink(player* player) { _player = player; }

	void HitDamage(int Damage);


};

