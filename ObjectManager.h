#pragma once
#include "gameNode.h"
#include <vector>
#include "CameraManager.h"
#include "Bat.h"

class ObjectManager : public gameNode
{
private:
	typedef vector<Object*>				vObject;
	typedef vector<Object*>::iterator	viObject;

private:
	vObject		_vObject;
	viObject	_viObject;

	CameraManager* _cm;
	player* _player;
	Enemy* _enemy;


	Bat* _bat;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	void SetBat();

	vector<Object*> GetVObject() { return _vObject; }
	vector<Object*>::iterator GetVIObject() { return _viObject; }

	void SetCamera(CameraManager* cm) { _cm = cm; }
	void SetPlayerLink(player* player) { _player = player; }
	void SetEnemyLink(Enemy* enemy) { _enemy = enemy; }
};

