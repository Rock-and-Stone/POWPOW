#include "pch.h"
#include "Mike.h"

Mike::Mike()
{
}

Mike::~Mike()
{
}

HRESULT Mike::init()
{
	return S_OK;
}

void Mike::release()
{
}

void Mike::update()
{
	SwitchImage();
}

void Mike::SwitchImage()
{
}

//����� �޺����� �ݹ��Լ�
void Mike::ComboAttack1(void* obj)
{
    Enemy* e = (Enemy*)obj;

    e->SetEnemyStatement(ENEMYSTATEMENT::ATTACK1);
    e->SetMotionName(KEYANIMANAGER->findAnimation("MikeleftAttack2"));
    e->GetMotionName()->start();
}

//������ �޺����� �ݹ��Լ�
void Mike::ComboAttack2(void* obj)
{
    Enemy* e = (Enemy*)obj;

    e->SetEnemyStatement(ENEMYSTATEMENT::ATTACK1);
    e->SetMotionName(KEYANIMANAGER->findAnimation("MikeleftAttack2"));
    e->GetMotionName()->start();
}

