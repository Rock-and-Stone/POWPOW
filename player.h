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


	Statement		_statement;		//���� ���� Enum
	RECT			_renderRC;		//�̹��� ������ ���� ��Ʈ
	RECT			_hitRC;			//��Ʈ�ڽ� ��Ʈ
	RECT			_attackRC;		//���� ��Ʈ
	RECT			_shadowRC;
	image*			_img;			//���� �̹���
	image*			_shadow;

	State*			_state;			//���� ���� (���� �ڽ� ���µ�)
	Idle*			_idle;
	Move*			_move;
	Jump*			_jump;
	Fall*			_fall;
	Attack*			_attack;
	Damaged*		_damaged;
	Down*			_down;
	GetUp*			_getUp;

	int				_dirX, _dirY;	// �÷��̾��� X��� Y�� ���� ���� 
	int				_indexX, _indexY;		// ���� �ִϸ��̼� ������
	int				_count;			//������ ī��Ʈ
	int				_atkCount;		// ���� ī��Ʈ 
	int				_jumpCount;		// ���� ���� Ƚ��
	int				_hitCount;
	int				_maxHP, _currentHP; // �ִ� ü��, ���� ü��
	int				_coin;

	bool			_animLoop;		// �ִϸ��̼��� �������� ����
	bool			_trigger;		// �ִϸ��̼��� �������� �۵��ϴ� Ʈ����
	bool			_isAttack;		// ���� �������� ����
	bool			_isAir;			// ���� �������� ����
	bool			_isRoll;		// ������ �������� ����
	bool			_isRun;			// �޸��� �������� ����
	bool			_isVulnerable;	// ������ �ִ� �������� ����

	float			_posX, _posY;	// ���� ��ǥ
	float			_probeX, _probeY;	//�ȼ� �ݶ��̴� �˻���
	float			_airY;				//������ ���߱����� Y��
	float			_jumpPower, _gravity; // ������, �߷°�

	float			_rendX, _rendY;		//������ ���� X, Y ��
	float			_shadowY;
	float			_speedX, _speedY;	//�ӵ� X, Y
	float			_maxSpeedX, _maxSpeedY; //�ִ�ӵ� X, Y
	float			_speedRes;			// �ӵ� ������

	

public:
	player();
	~player();

	virtual HRESULT InitVariables();
	virtual HRESULT init(float posX, float posY);

	virtual void release();
	virtual void update();
	virtual void render();

	void Movement(); //���� �̵� ���� �Լ�

	void CountFrame(); //�̹��� ������ �Լ�

	void Collision(); 

	void coinGet(int coin);

	void hitDamage(int damage); // �ǰ� �Լ�

	void ChangeState(Statement statement); //���� ���� �Լ�

	void AttackCollision();

#pragma region GETSET

	bool getIsVulnerable() { return _isVulnerable; }
	void setIsVulnuerable(bool isvul) { _isVulnerable = isvul; }

	bool getTrigger() { return _trigger; } //�ִϸ��̼� �������� �������� �۵��ϴ� Ʈ���� ������

	virtual float getRenderPosY();	//�����Ŵ����� �����ִ� ���� Y��

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

