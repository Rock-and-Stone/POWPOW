#pragma once
#include "gameNode.h"
#include <vector>
#include "Luke.h"
#include "Mike.h"
#include "Malcolm.h"
#include "CameraManager.h"
#include "Luke.h"



class EnemyManager : public gameNode
{
private:
	typedef vector<Enemy*>				 vEnemy;
	typedef vector<Enemy*>::iterator	 viEnemy;

private:
	vEnemy	_vLuke;
	viEnemy _viLuke;

	CameraManager* _cm;
	player* _player;
	
	Luke* _Luke;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void EnemyImageStorage();

	void SetLuke();
	void SetMike();
	void SetMalcolm();
	
	void Collision();

	vector<Enemy*> GetVLuke() { return _vLuke; }
	vector<Enemy*>::iterator GetVILuke() { return _viLuke; }

	void SetCamera(CameraManager* cm) { _cm = cm; }
	void SetPlayerLink(player* player) { _player = player; }
	
};

