#pragma once
#include "gameNode.h"
#include "CameraManager.h"
#include "EnemyState.h"
#include "player.h"
#include "Object.h"

#define MAXSPEEDX 4.0f
#define MAXSPEEDY 2.0f

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
	WANDER,
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
	EnemyMove* _move;
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
	int _randomHit;					//�´� �̹��� ��������
	int _stateCount;				//���� ���� ������� ī��Ʈ
	int _hitGauge;					//�ǰ� ������ (���� �̻� ������ ��ٿ�) //
	int	_hitCount;					//�ǰ� ������ ���� ī��Ʈ(�ش� ī��Ʈ�� ������ ���� �پ��)'
	int _wanderDirX, _wanderDirY;
	int _attackCount;

	bool _isAir;
	bool _isChange;
	bool _isAttack;
	bool _isTrace;
	bool _isRun;

	float _posX, _posY;				//���� x, y ��ǥ
	float _rendX, _rendY;			//���� x, y ��ǥ
	float _probeX, _probeY;			//�ȼ� �浹 ��
	float _jumpPower, _gravity;		//����, �߷�
	float _speedX, _speedY, _speedRes;
	float _maxSpeedX, _maxSpeedY;
	float _distance;				//�÷��̾���� �Ÿ� ���
	float _objectDistance;			//������Ʈ���� �Ÿ� ���
	float _attackRange;				//���� ������ �Ÿ�
	float _searchRange;				//�÷��̾� ���� �Ÿ�
	float _airY;					//���� Y ��ǥ

	int _maxHP, _currentHP;			//�ִ� ü��, ���� ü��
	int _rndSelection;
	int _probeEnemyX, _probeEnemyRX, _probeEnemyLX, _probeEnemyY, _probeEnemyBY;
	

public:
	Enemy();
	~Enemy();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, const char* animationName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void SwitchImage() = 0;

	void EnemyUpdate();

	void Move();

	void Draw();

	void Collision();

	void pixelCollision();

	void TracePlayer();
	
	void ChangeStatement(ENEMYSTATEMENT enemyStatement);

	void MakeAttackRect();

	void DownGauge();

	void StateCount();

#pragma region GETSET

	void setWanderDirX(int dir) { _wanderDirX = dir; }

	void setWanderDirY(int dir) { _wanderDirY = dir; }

	int getAtkCount() { return _attackCount; }
	void setAtkCount(int count) { _attackCount = count; }

	int getHitGauge() { return _hitGauge; }

	bool getIsChange() { return _isChange; }
	void setIsChange(bool isChange) { _isChange = isChange; }

	int getStateCount() { return _stateCount; }
	void setStateCount(int count) { _stateCount = count; }

	bool getIsTrace() { return _isTrace; }
	void setIsTrace(bool isTrace) { _isTrace = isTrace; }

	bool getIsAttack() { return _isAttack; }
	void setIsAttack(bool isAttack) { _isAttack = isAttack; }

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

	float getSpeedX() { return _speedX; }
	void setSpeedX(float speed) { _speedX = speed; }

	float getSpeedY() { return _speedY; }
	void setSpeedY(float speed) { _speedY = speed; }
#pragma endregion
	virtual float getRenderPosY();

	bool ChaseSession();

	bool AttackSession();

	bool ObjectSession();

	void SetPlayerLink(player* player) { _player = player; }

	void HitDamage(int Damage);

};

