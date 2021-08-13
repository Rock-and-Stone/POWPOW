#pragma once
#include "gameNode.h"
#include "UserInterface.h"
#include "player.h"

class restaurantScene :public gameNode
{
private:
	image* _select;
	RECT _rc;
	float _x, _y;

	UserInterface* _ui;
	player* _player;

public:
	restaurantScene();
	~restaurantScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Interaction();
};

