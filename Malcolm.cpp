#include "pch.h"
#include "Malcolm.h"

Malcolm::Malcolm()
{
}

Malcolm::~Malcolm()
{
}

HRESULT Malcolm::init()
{
	return S_OK;
}

void Malcolm::release()
{
}

void Malcolm::update()
{
	SwitchImage();
}

void Malcolm::SwitchImage()
{
}

//����� �޺����� �ݹ��Լ�
void Malcolm::ComboAttack1(void* obj)
{
    Enemy* e = (Enemy*)obj;

    e->SetEnemyStatement(ENEMYSTATEMENT::ATTACK1);
    e->SetMotionName(KEYANIMANAGER->findAnimation("MalcolmleftAttack2"));
    e->GetMotionName()->start();
}

//������ �޺����� �ݹ��Լ�
void Malcolm::ComboAttack2(void* obj)
{
    Enemy* e = (Enemy*)obj;

    e->SetEnemyStatement(ENEMYSTATEMENT::ATTACK1);
    e->SetMotionName(KEYANIMANAGER->findAnimation("MalcolmleftAttack2"));
    e->GetMotionName()->start();
}
