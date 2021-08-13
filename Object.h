#pragma once
#include "gameNode.h"
#include "CameraManager.h"
#include "player.h"
#include "Enemy.h"

enum class OBJECTSTATEMENT
{
	LEFT_ATK, 
	LEFT_DASH, 
	LEFT_GET, 
	LEFT_IDLE,
	LEFT_JUMP, 
	LEFT_NEUTRAL, 
	LEFT_THROW, 
	LEFT_WALK, 
	RIGHT_ATK,
	RIGHT_DASH,
	RIGHT_GET,
	RIGHT_IDLE,
	RIGHT_JUMP,
	RIGHT_NEUTRAL,
	RIGHT_THROW,
	RIGHT_WALK
};

class Object : public gameNode
{
protected:
	RECT _rc;
	RECT _collideRect;
	CameraManager* _cm;

	player* _player;
	Enemy* _enemy;
	image* _imageName;
	animation* _motionName;
	OBJECTSTATEMENT _objectStatement;

	float _posX, _posY;
	float _rendX, _rendY;
	float _speedX, _speedY;
	int _direction;

	int _value;

	bool _isDelete;

public:
	Object();
	~Object();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, const char* animationName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void SwitchImage() = 0;

	void Draw();

	inline RECT GetRect() { return _rc; }
	inline RECT GetCollideRect() { return _collideRect; }

	float GetObjectPosX() { return _posX; }
	float GetObjectPosY() { return _posY; }
	virtual bool getReleased();
	void SetReleased(bool b) { _isDelete = b; }

	int GetCoin() { return _value; }

	//카메라 설정
	void SetCamera(CameraManager* cm) { _cm = cm; }

	void SetPlayerLink(player* player) { _player = player; }

	void SetEnemyLink(Enemy* enemy) { _enemy = enemy; }

	
};

