#pragma once
#include "gameNode.h"
#include <vector>
#include "CameraManager.h"
#include "Bat.h"
#include "Trash.h"
#include "sCoin.h"
#include "mCoin.h"
#include "lCoin.h"

class EnemyManager;

class ObjectManager : public gameNode
{
private:
	typedef vector<Object*>				vObject;
	typedef vector<Object*>::iterator	viObject;

private:
	vObject		_vObject;
	viObject	_viObject;

	vObject _vCoin;
	viObject _viCoin;

	CameraManager* _cm;
	player* _player;
	Enemy* _enemy;
	POINT _pos;
	EnemyManager* _em;

	Bat* _bat;
	Trash* _trash;
	sCoin* _sCoin;
	mCoin* _mCoin;
	lCoin* _lCoin;



public:
	HRESULT init();
	void release();
	void update();
	void render();

	void SetBat();
	void SetTrash();
	void SetsCoin();

	void CoinCollision();

	void addCoin(float x, float y);
	void removeCoin(int arrNum);

	vector<Object*> GetVObject() { return _vObject; }
	vector<Object*>::iterator GetVIObject() { return _viObject; }

	vector<Object*> GetVCoin() { return _vCoin; }
	vector<Object*>::iterator GetVICoin() { return _viCoin; }

	void SetCamera(CameraManager* cm) { _cm = cm; }
	void SetPlayerLink(player* player) { _player = player; }
	void SetEnemyLink(Enemy* enemy) { _enemy = enemy; }
	void SetEMLink(EnemyManager* em) { _em = em; }
};

