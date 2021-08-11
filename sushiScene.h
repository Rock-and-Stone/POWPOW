#pragma once
#include "gameNode.h"
class sushiScene : public gameNode
{
private:
	image* _select;
	RECT _rc;
	float _x, _y;

public:
	sushiScene();
	~sushiScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Interaction();
};

