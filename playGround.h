#pragma once


#include "gameNode.h"
#include "string"
#include "stage1.h"
#include "titleScene.h"
#include "selectScene.h"
#include "loadingScene.h"
#include "settingScene.h"




class playGround : public gameNode
{
private:


public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�
};

