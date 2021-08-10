#pragma once
#include "gameNode.h"
#include "CameraManager.h"
#include "EnemyState.h"
#include "player.h"
#include "Object.h"

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
	FALL,						//������
	ATTACK,					    //�����1
	DAMAGED,					//�ǰ�
	DOWN,						//�ǰݽ� �ٿ�(����)
	DOWN_DAMAGED,				//������¿����� �ǰ�
	DOWN_ATTACK,				//������¿��� ����
	GETUP,							//������¿��� �Ͼ��
	GUARD,						//����
	OBJECT_ATTACK,				//������Ʈ ��� ����
	OBJECT_THROW,				//������Ʈ ������
	OBJECT_GRAB				//������Ʈ ���
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

	//��������
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

	
	int _direction;					//���ʹ��� ����
	int _highlow;					//���ʹ� ������ (�÷��̾���� ��)
	int _randomChoice;				//����, �±� ������

	bool _isAir;

	float _posX, _posY;				//���� x, y ��ǥ
	float _rendX, _rendY;			//���� x, y ��ǥ
	float _probeX, _probeY;			//�ȼ� �浹 ��
	float _jumpPower, _gravity;		//����, �߷�
	float _distance;				//�÷��̾���� �Ÿ� ���
	float _objectDistance;			//������Ʈ���� �Ÿ� ���
	float _attackRange;				//���� ������ �Ÿ�
	float _searchRange;				//�÷��̾� ���� �Ÿ�
	float _airY;					//���� Y ��ǥ

	int _maxHP, _currentHP;			//�ִ� ü��, ���� ü��
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


	//���ʹ� ��Ʈ ������
	inline RECT GetRect() { return _rc; }
	inline RECT GetAttackRect() { return _attackRect; }

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

	//���ʹ� �׸� ��ǥ �޾ƿ���
	float GetEnemyRendX() { return _rendX; }
	float GetEnemyRendY() { return _rendY; }

	//���ʹ� ���� �޾ƿ���
	int GetEnemyDirection() { return _direction; }

	//���ʹ� ü�� �޾ƿ���
	int GetEnemyHP() { return _currentHP; }
	void SetEnemyHP(int hp) { _currentHP = hp; }

	//���� ���� �޾ƿ���
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

