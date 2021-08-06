#pragma once
#include "Enemy.h"
class Malcolm :
    public Enemy
{
private:

public:
	Malcolm();
	~Malcolm();

	virtual HRESULT init();
	virtual void release();
	virtual void update();


	virtual void SwitchImage() override;

	static void ComboAttack1(void* obj);
	static void ComboAttack2(void* obj);
};

