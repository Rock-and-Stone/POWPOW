#pragma once
#include "gameNode.h"
#include "CameraManager.h"

class Object : public gameNode
{
private:

public:
	Object();
	~Object();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, const char* animationName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();
};

