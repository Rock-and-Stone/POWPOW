#pragma once
#include "gameNode.h"
#include "CameraManager.h"
#include "player.h"
#include "Enemy.h"

class Object : public gameNode
{
private:
	RECT _rc;
	CameraManager* _cm;

	player* _player;
	image* _imageName;
	animation* _motionName;

	float _posX, _posY;
	float _rendX, _rendY;

public:
	Object();
	~Object();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, const char* animationName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void Draw();

	inline RECT GetRect() { return _rc; }

	//카메라 설정
	void SetCamera(CameraManager* cm) { _cm = cm; }

	void SetPlayerLink(player* player) { _player = player; }
};

