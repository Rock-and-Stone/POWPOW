#pragma once
#include "gameNode.h"
#include "CameraManager.h"
#include "player.h"
#include "Enemy.h"

enum class OBJECTSTATEMENT
{
	LEFT_ATK, RIGHT_ATK,
	LEFT_DASH, RIGHT_DASH,
	LEFT_GET, RIGHT_GET,
	LEFT_IDLE, RIGHT_IDLE,
	LEFT_JUMP, RIGHT_JUMP,
	LEFT_NEUTRAL, RIGHT_NEUTRAL,
	LEFT_THROW, RIGHT_THROW,
	LEFT_WALK, RIGHT_WALK
	
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

	int _direction;

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

	//카메라 설정
	void SetCamera(CameraManager* cm) { _cm = cm; }

	void SetPlayerLink(player* player) { _player = player; }

	
};

