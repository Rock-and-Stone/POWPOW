#pragma once
#include "gameNode.h"
#include "UserInterface.h"
#include "player.h"
class convenientScene :
    public gameNode
{
private:
	image* _select;
	RECT _rc;
	float _x, _y;

	player* _player;
	UserInterface* _ui;

public:
	convenientScene();
	~convenientScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Interaction();
};

