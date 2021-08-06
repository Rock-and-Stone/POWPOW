#pragma once
#include "gameNode.h"
#include "CameraManager.h"
#include "State.h"

enum class Statement
{
	IDLE,
	RUN,
	WALK,
	JUMP,
	FALL,
	LAND
};

class player : public gameNode
{
protected:


	Statement		_statement;
	RECT			_renderRC;
	RECT			_hitRC;
	image*			_img;

	State*			_state;
	Idle*			_idle;
	Walk*			_walk;
	Jump*			_jump;
	Fall*			_fall;

	int				_dirX;
	int				_dirY;
	int				_indexX;
	int				_count;
	int				_jumpCount;

	bool			_animLoop;
	bool			_trigger;
	bool			_isAttack;
	bool			_isAir;

	int				_posX, _posY;
	int				_probeX, _probeY;
	int				_groundY, _airY;
	float			_jumpPower, _gravity;
	int				_keyCount;
	int				_absolX, _absolY;
	int				_rendX, _rendY;

	int				_speedX, _speedY;

public:
	player();
	~player();

	virtual HRESULT InitVariables();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Movement();

	void CountFrame();

	void Collision();

	void ChangeState(Statement statement);

	bool getTrigger() { return _trigger; }

	virtual int getRenderPosY();

	Statement getStatement() { return _statement; }
	void SetStatement(Statement statement) { _statement = statement; }

	void setAnimLoop(bool loop) { _animLoop = loop; }

	float getJumpPower() { return _jumpPower; }
	void setJumpPower(float jumpPower) { _jumpPower = jumpPower; }

	int getAirY() { return _airY; }
	void setAirY(int airY) { _airY = airY; }

	int getPosX() { return _posX; }
	void setPosX(int posX) { _posX = posX; }

	int getPosY() { return _posY; }
	void setPosY(int posY) { _posY = posY; }

	int getGroundY() { return _groundY; }

	bool getIsAir() { return _isAir; }
	void setIsAir(bool isAir) { _isAir = isAir; }

	int getRenderY() { return _hitRC.bottom; }

	void setRendX(int rendX) { _rendX = rendX; }
	void setRendY(int rendY) { _rendY = rendY; }

	int getDirectionX() { return _dirX; }
	void setDirectionX(int dirX) { _dirX = dirX; }

	int getDirectionY() { return _dirY; }
	void setDirectionY(int dirY) { _dirY = dirY; }

	int getSpeedX() { return _speedX; }
	void setSpeedX(int speedX) { _speedX = speedX; }

	int getSpeedY() { return _speedY; }
	void setSpeedY(int speedY) { _speedY = speedY; }
};

