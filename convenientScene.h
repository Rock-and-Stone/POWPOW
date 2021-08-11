#pragma once
#include "gameNode.h"
class convenientScene :
    public gameNode
{
private:
	image* _select;
	RECT _rc;
	float _x, _y;

public:
	convenientScene();
	~convenientScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Interaction();
};

