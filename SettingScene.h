#pragma once
#include "gameNode.h"
#include "volumeProgressBar.h"

class settingScene: public gameNode
{
private:
	volumeProgressBar* _BGMbar;
	volumeProgressBar* _SFXbar;

	//box rect
	RECT _rc;
	int _selectNum;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

