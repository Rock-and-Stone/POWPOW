#pragma once
#pragma comment (lib, "Vfw32.lib")

#include "gameNode.h"
#include <Vfw.h>

class bossScene : public gameNode
{
private:	
	image* _bossBackground;
    HWND _bossIntro;

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
};	

