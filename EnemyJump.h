#pragma once
#include "EnemyState.h"

class Enemy;

class EnemyJump :
    public EnemyState
{
private:
	Enemy* _enemy;

	float _saveJump;

public:

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;

	void SetEnemy(Enemy* enemy) { _enemy = enemy; }

	float GetSaveJump() { return _saveJump; }
};

