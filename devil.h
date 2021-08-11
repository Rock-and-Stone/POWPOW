#pragma once
#include "gameNode.h"

struct TAGBULLET
{
	RECT rc;
	float speed,x,y;
	int damage;
	image* image;
};


class devil : public gameNode
{
private:
	float _devilY, _devilX;
	RECT _devilRc;
	int _devilHP;



public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual float getRenderPosY() { return _devilY; }
};	

