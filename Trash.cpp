#include "pch.h"
#include "Trash.h"

HRESULT Trash::init()
{
	return S_OK;
}

void Trash::release()
{
}

void Trash::update()
{
}

void Trash::SwitchImage()
{
	switch (_objectStatement)
	{
	case OBJECTSTATEMENT::LEFT_ATK:
		_direction = 0;
		_imageName = IMAGEMANAGER->findImage("trash_left_atk");
		_motionName = KEYANIMANAGER->findAnimation("trash_left_atk");
		break;
	case OBJECTSTATEMENT::LEFT_DASH:
		_direction = 0;
		_imageName = IMAGEMANAGER->findImage("trash_left_dash");
		_motionName = KEYANIMANAGER->findAnimation("trash_left_dash");
		break;
	case OBJECTSTATEMENT::LEFT_GET:
		_direction = 0;
		_imageName = IMAGEMANAGER->findImage("trash_left_get");
		_motionName = KEYANIMANAGER->findAnimation("trash_left_get");
		break;
	case OBJECTSTATEMENT::LEFT_IDLE:
		_direction = 0;
		_imageName = IMAGEMANAGER->findImage("trash_left_idle");
		_motionName = KEYANIMANAGER->findAnimation("trash_left_idle");
		break;
	case OBJECTSTATEMENT::LEFT_JUMP:
		_direction = 0;
		_imageName = IMAGEMANAGER->findImage("trash_left_jump");
		_motionName = KEYANIMANAGER->findAnimation("trash_left_jump");
		break;
	case OBJECTSTATEMENT::LEFT_NEUTRAL:
		_direction = 0;
		_imageName = IMAGEMANAGER->findImage("trash_left_neutral");
		_motionName = KEYANIMANAGER->findAnimation("trash_left_neutral");
		break;
	case OBJECTSTATEMENT::LEFT_THROW:
		_direction = 0;
		_imageName = IMAGEMANAGER->findImage("trash_left_throw");
		_motionName = KEYANIMANAGER->findAnimation("trash_left_throw");
		break;
	case OBJECTSTATEMENT::LEFT_WALK:
		_direction = 0;
		_imageName = IMAGEMANAGER->findImage("trash_left_walk");
		_motionName = KEYANIMANAGER->findAnimation("trash_left_walk");
		break;
	case OBJECTSTATEMENT::RIGHT_ATK:
		_direction = 1;
		_imageName = IMAGEMANAGER->findImage("trash_right_atk");
		_motionName = KEYANIMANAGER->findAnimation("trash_right_atk");
		break;
	case OBJECTSTATEMENT::RIGHT_DASH:
		_direction = 1;
		_imageName = IMAGEMANAGER->findImage("trash_right_dash");
		_motionName = KEYANIMANAGER->findAnimation("trash_right_dash");
		break;
	case OBJECTSTATEMENT::RIGHT_GET:
		_direction = 1;
		_imageName = IMAGEMANAGER->findImage("trash_right_get");
		_motionName = KEYANIMANAGER->findAnimation("trash_right_get");
		break;
	case OBJECTSTATEMENT::RIGHT_IDLE:
		_direction = 1;
		_imageName = IMAGEMANAGER->findImage("trash_right_idle");
		_motionName = KEYANIMANAGER->findAnimation("trash_right_idle");
		break;
	case OBJECTSTATEMENT::RIGHT_JUMP:
		_direction = 1;
		_imageName = IMAGEMANAGER->findImage("trash_right_jump");
		_motionName = KEYANIMANAGER->findAnimation("trash_right_jump");
		break;
	case OBJECTSTATEMENT::RIGHT_NEUTRAL:
		_direction = 1;
		_imageName = IMAGEMANAGER->findImage("trash_right_neutral");
		_motionName = KEYANIMANAGER->findAnimation("trash_right_neutral");
		break;
	case OBJECTSTATEMENT::RIGHT_THROW:
		_direction = 1;
		_imageName = IMAGEMANAGER->findImage("trash_right_throw");
		_motionName = KEYANIMANAGER->findAnimation("trash_right_throw");
		break;
	case OBJECTSTATEMENT::RIGHT_WALK:
		_direction = 1;
		_imageName = IMAGEMANAGER->findImage("trash_right_walk");
		_motionName = KEYANIMANAGER->findAnimation("trash_right_walk");
		break;
	default:
		break;
	}
}
