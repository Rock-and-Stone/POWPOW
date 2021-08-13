#pragma once
#include "gameNode.h"
#include "volumeProgressBar.h"

//player 데이터 받아오기

class player;

class UserInterface : public gameNode
{
private:

	image* _hp100;
	image* _hp10;
	image* _hp1;

	image* _gp100;
	image* _gp10;
	image* _gp1;

	image* _coin100;
	image* _coin10;
	image* _coin1;

	image* _option;
	image* _ingameSettingImg;
	image* _intgameSettingBox;

	bool _isPause;
	bool _ingameSetting;

	RECT _selectRc;
	int _selectNum;
	int _volumeSelectNum;

	volumeProgressBar* _BGMbar;
	volumeProgressBar* _SFXbar;

	float _currentBGMVolume;
	float _currentSFXVolume;

	player* _player;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	bool GetIsPause() { return _isPause; }

	void setPlayerMemoryAddress(player* player) { _player = player; }

};

