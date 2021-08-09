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
#include "player.h"

#define ENEMYSPEED 5

//���ʹ� ���� enum Ŭ����
//enum class ENEMYDIRECTION
//{
//	LEFT,
//	RIGHT
//};

//���ʹ� ���� enum Ŭ����
enum class ENEMYSTATEMENT
{
	INIT,						//����
	IDLE,						//�⺻
	WALK,						//�ȱ�
	RUN,						//�ٱ�
	JUMP,						//����
	ATTACK1,					//�����1
	ATTACK2,					//�����2(�޺�)
	ATTACK3,					//������1
	ATTACK4,					//������2(�޺�)
	DAMAGED,					//�ǰ�
	DOWN,						//�ǰݽ� �ٿ�(����)
	DOWN_DAMAGED,				//������¿����� �ǰ�
	DOWN_ATTACK,				//������¿��� ����
	UP,							//������¿��� �Ͼ��
	GUARD,						//����
	OBJECT_ATTACK,				//������Ʈ ��� ����
	OBJECT_THROW,				//������Ʈ ������
	OBJECT_GRAB,				//������Ʈ ���
	DAEGI						//���״�� ������
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

	//��������
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
	
	int _direction;			//���ʹ��� ����
	int _highlow;			//���ʹ� ������ (�÷��̾���� ��)

	bool _isJump;

	float _posX, _posY;				//���ʹ� x, y ��ǥ
	float _rendX, _rendY;
	float _probeX, _probeY;			//�ȼ� �浹 ��
	float _jumpPower, _gravity;		//����, �߷�
	float _distance; //�÷��̾���� �Ÿ� ���
	float _attackRange;
	float _searchRange;

	int _hp;	//�÷��̾� ü��
	

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

	void KeyTest();
	void ChaseRun();

	


	//���ʹ� ��Ʈ ������
	inline RECT GetRect() { return _rc; }

	//���ʹ� ���� ������, ������
	void SetEnemyStatement(ENEMYSTATEMENT enemyStatement) { _enemyStatement = enemyStatement; }
	ENEMYSTATEMENT GetEnemyStatement() { return _enemyStatement; }

	//�̹��� ������
	image* GetImageName() { return _imageName; }
	

	//�ִϸ��̼� ������
	void SetMotionName(animation* motionName) { _motionName =  motionName; }
	animation* GetMotionName() { return _motionName; }

	//ī�޶� ����
	void SetCamera(CameraManager* cm) { _cm = cm; }

	//���ʹ� x, y ��ǥ ������
	float GetEnemyPosX() { return _posX; }
	float GetEnemyPosY() { return _posY; }

	void SetEnemyPosX(float x) { _posX = x; }
	void SetEnemyPosY(float y) { _posY = y; }

	virtual float getRenderPosY();

	//��ǿ� ���� ������ ������
	animation* GetEnemyMotion() { return _motionName; }
	void SetEnemyMotion(animation* ani) { _motionName = ani; }

	bool ChaseSession();

	bool AttackSession();

	void SetPlayerLink(player* player) { _player = player; }

	void HitDamage();

};

