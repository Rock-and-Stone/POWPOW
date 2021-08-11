#pragma once
#pragma comment (lib, "Vfw32.lib")

#include <Vfw.h>

#include "gameNode.h"
#include "boss.h"
#include "UserInterface.h"
#include "Ramona.h"




class bossScene : public gameNode
{
private:
	image* _bossBackground;
    HWND _bossIntro;

	boss* _boss;
	UserInterface* _ui;
	player* _player;

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
};	

