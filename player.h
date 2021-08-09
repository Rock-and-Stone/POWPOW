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

	int				_dirX, _dirY;	// �÷��̾��� X��� Y�� ���� ���� 
	int				_indexX, _indexY;		// ���� �ִϸ��̼� ������
	int				_count;			
	int				_atkCount;		// ���� ī��Ʈ 
	int				_jumpCount;		// ���� ���� Ƚ��

	int				_maxHp, _currentHP; // �ִ� ü��, ���� ü��

	bool			_animLoop;		// �ִϸ��̼��� �������� ����
	bool			_trigger;		// �ִϸ��̼��� �������� �۵��ϴ� Ʈ����
	bool			_isAttack;		// ���� �������� ����
	bool			_isAir;			// ���� �������� ����
	bool			_isRoll;
	bool			_isRun;

	float			_posX, _posY;	// ���� ��ǥ
	float			_probeX, _probeY;
	float			_groundY, _airY;	// �ٴ� ��ǥ���� ������ ���߱����� Y��
	float			_jumpPower, _gravity; // ������ 

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

	void Movement(); //���� �̵� ���� �Լ�

	void CountFrame(); //�̹��� ������ �Լ�

	void Collision(); 

	void hitDamage(int damage);

	void ChangeState(Statement statement); //���� ���� �Լ�

	void AttackCollision();

	bool getTrigger() { return _trigger; } //�ִϸ��̼� �������� �������� �۵��ϴ� Ʈ���� ������

	virtual float getRenderPosY();	//�����Ŵ����� �����ִ� ���� ��

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

