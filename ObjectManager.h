#pragma once
#include "gameNode.h"
#include <vector>
#include "CameraManager.h"
#include "Bat.h"

class ObjectManager : public gameNode
{
private:
	typedef vector<Object*>				vObject;
	typedef vector<Object*>::iterator	viObject;

private:
	vObject		_vObject;
	viObject	_viObject;

	Bat* _bat;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

