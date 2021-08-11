#pragma once
#include "gameNode.h"
#include "UserInterface.h"
class cafeScene :
    public gameNode
{
private:
	image* _select;
	RECT _rc;
	float _x, _y;

	UserInterface* _ui;


public:
	cafeScene();
	~cafeScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Interaction();
};

