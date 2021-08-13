#pragma once
#include "gameNode.h"
#include "UserInterface.h"
#include "player.h"

class cafeScene :
    public gameNode
{
private:
	image* _select;
	RECT _rc;
	float _x, _y;

	UserInterface* _ui;
	player* _player;


public:
	cafeScene();
	~cafeScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Interaction();
};

