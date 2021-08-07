#pragma once
#include "gameNode.h"

#define VOLUMEMAX 160

class settingScene: public gameNode
{
private:
	image* _backgroundVolume;
	image* _SFXvolume;

	//box rect
	RECT _rc;
	int _selectNum;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

