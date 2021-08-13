#pragma once
#include "Object.h"
class mCoin :
    public Object
{
private:
	

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();


	virtual void SwitchImage() override;

	
};

