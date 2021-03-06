#pragma once


#include "gameNode.h"
#include "string"
#include "CameraManager.h"
#include "Ramona.h"
#include "UserInterface.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "ObjectManager.h"
#include "Luke.h"

#define MAPSIZEX 31812
#define MAPSIZEY 1000

class stage1 :public gameNode
{
private:
	CameraManager* _cm;
	player* _player;
	UserInterface* _ui;
	EnemyManager* _em;
	ObjectManager* _om;

	int _posX;
	int _posY;

	int _probePlayerX, _probePlayerRX, _probePlayerLX, _probePlayerY, _probePlayerBY;
	int _probeEnemyX, _probeEnemyRX, _probeEnemyLX, _probeEnemyY, _probeEnemyBY;

	char* _str;

	int _power;
	float _minMapX;
	float _mapX;
	float _maxY;
	bool _isBattle;

	int _stage;

public : 
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	bool getIsBattle() { return _isBattle; }
	int getStage() { return _stage; }

	void pixelCollision();
	void CameraLock();
};

