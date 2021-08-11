#pragma once


#include "gameNode.h"
#include "string"
#include "CameraManager.h"
#include "Ramona.h"
#include "UserInterface.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "ObjectManager.h"

#define ARRSIZE 10

class stage1 :public gameNode
{
private:
	CameraManager* _cm;
	player* _player;
	UserInterface* _ui;
	EnemyManager* _em;
	Enemy* _enemy;
	ObjectManager* _om;

	int _posX;
	int _posY;

	int _probePlayerX, _probePlayerRX, _probePlayerLX, _probePlayerY, _probePlayerBY;
	int _probeEnemyX, _probeEnemyY;

	char* _str;

	int _power;

	float _maxY;

	int _arr[ARRSIZE] = { 2 , 5 ,1 , 4 , 7 , 8 , 9, 3, 11, 10 };

	


public : 
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	void pixelCollision();
};

