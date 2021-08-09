#pragma once
#include "EnemyState.h"
#include "effect.h"

class Enemy;

class EnemyDamaged :  public EnemyState
{
private:
	Enemy* _enemy;

public:

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;


	void SetEnemy(Enemy* enemy) { _enemy = enemy; }

};

