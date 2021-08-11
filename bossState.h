#pragma once
#include "gameNode.h"

class bossState : public gameNode
{
public:
	bossState();
	~bossState();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};


class bossJump : public bossState
{
public:
	bossJump();
	~bossJump();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

class bossAttack1 : public bossState
{
	bossAttack1();
	~bossAttack1();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

class bossAttack2 : public bossState
{
	bossAttack2();
	~bossAttack2();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
