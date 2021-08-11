#pragma once
#include "gameNode.h"
#include "bossState.h"

enum class BOSSDIRECTION
{
	leftIdle,
	rightIdle,
	leftMove,
	rightMove,
	leftRun,
	rightRun,
	leftJump,
	rightJump,
	leftAttack1,
	rightAttack1,
	leftAttack2,
	rightAttack2,
	leftAttack3,
	rightAttack3,
	leftSpecialAttack,
	rightSpecialAttack,
	leftDown,
	rightDown,
	leftUp,
	rightUp,
	leftDownKick,
	rightDownKick,
	leftDefence,
	rightDefence,
	SecondPhase
};

class boss : public gameNode
{
private:
	bossState* _bossState;

	BOSSDIRECTION _bossDirection;

	float _bossX, _bossY;
	RECT _bossRc;

	animation* _bossAnim;
	image* _bossImg;

public:
	boss();
	~boss();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual float getRenderPosY() { return _bossY; }
};
