#pragma once
#include "gameNode.h"
#include <vector>
#include "Luke.h"
#include "Mike.h"
#include "Malcolm.h"
#include "CameraManager.h"


class ObjectManager;

class EnemyManager : public gameNode
{
private:
	typedef vector<Enemy*>				 vEnemy;
	typedef vector<Enemy*>::iterator	 viEnemy;

private:
	vEnemy	_vEnemy;
	viEnemy _viEnemy;

	ObjectManager* _om;
	CameraManager* _cm;
	player* _player;
	
	int _enemyCount;

public:
	HRESULT init();
	void release();
	void update();
	void render();


	void SetLuke(POINT pos);
	void SetMike(POINT pos);
	void SetMalcolm(POINT pos);
	
	void SpawnEnemy(int lukeNum, int mikeNum, int malcolmNum, int currentstage);

	void Collision();

	vector<Enemy*> GetVEnemy() { return _vEnemy; }
	vector<Enemy*>::iterator GetVIEnemy() { return _viEnemy; }

	int GetEnemyCount() { return _enemyCount; }

	void SetCamera(CameraManager* cm) { _cm = cm; }
	void SetPlayerLink(player* player) { _player = player; }
	void SetOMLink(ObjectManager* om) { _om = om; }
};

