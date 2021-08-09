#include "pch.h"
#include "EnemyFall.h"
#include "Enemy.h"

HRESULT EnemyFall::init()
{
	return S_OK;
}

void EnemyFall::release()
{
}

void EnemyFall::update()
{
	if (_enemy->GetJumpPower() < 0) _enemy->SetIsAir(false);
}
