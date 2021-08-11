#pragma once
#include "gameNode.h"
class restaurantScene :
    public gameNode
{
private:
	image* _select;
	RECT _rc;
	float _x, _y;

	

public:
	restaurantScene();
	~restaurantScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Interaction();
};

