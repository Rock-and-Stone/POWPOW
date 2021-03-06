#include "pch.h"
#include "loadingScene.h"
#include "progressBar.h"

loadingScene::loadingScene()
    : _loadingBG(nullptr),
    _loadingBar(nullptr),
    _currentCount(0)

{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
    _loadingBG = IMAGEMANAGER->addImage("로딩배경", "source/loadingBG.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

    _loadingBar = new progressBar;
    _loadingBar->init(0, WINSIZEY - 50, WINSIZEX, 50);
    _loadingBar->setGauge(0, 0);


    IMAGEMANAGER->addFrameImage("loading1", "source/로딩1.bmp", 120, 34, 4, 1, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("loading2", "source/로딩2.bmp", 120, 34, 4, 1, true, MAGENTA);

    _loadingImg = IMAGEMANAGER->findImage("loading1");

    _loadingBar = new progressBar;
    _loadingBar->init(0, WINSIZEY - 50, WINSIZEX, 50);
    _loadingBar->setGauge(0, 0);


    _loadingImageNum = RND->getInt(2);

    frameX = 0;
    _count = 0;

    SOUNDMANAGER->addSound("menuBGM", "source/music/메뉴.mp3", true, true);

    SOUNDMANAGER->play("menuBGM", getBGMVolume() / 10);

    CreateThread(
        NULL,				//스레드 보안속성(자식윈도우 존재할때)
        NULL,				//스레드의 스택크기(0이면 메인쓰레드 동일)
        threadFunction,		//사용할 함수
        this,				//스레드 매개변수(this 로 뒀으니 본 클래스)
        NULL,				//스레드 특성
        NULL);				//스레드 ID

    return S_OK;
}

void loadingScene::release()
{
    SAFE_DELETE(_loadingBar);
}

void loadingScene::update()
{
    _loadingBar->update();
    _loadingBar->setGauge(_currentCount, LOADINGMAX);


    if (_currentCount == LOADINGMAX)
    {
        SCENEMANAGER->changeScene("selectScene");
    }

    _count++;

    if (_count % 10 == 0)
    {
        frameX++;
    }

    if (frameX >= 4) frameX = 0;



}

void loadingScene::render()
{
    _loadingBG->render(getMemDC());
    _loadingBar->render();
    _loadingImg->frameRender(getMemDC(), WINSIZEX - 50, WINSIZEY - 100, frameX, 0);
}

DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
    loadingScene* loadingHelper = (loadingScene*)lpParameter;

    //이미지 및 사운드 추가 
    while (loadingHelper->_currentCount != LOADINGMAX)
    {
#pragma region 이미지 추가
    	IMAGEMANAGER->addImage("title", "source/titleImage.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("background", "source/Level 1 - Frozen Suburbs.bmp", 31812, 1000, true, RGB(255,0,255));
		IMAGEMANAGER->addImage("settingBackGround", "source/settingScene.bmp", WINSIZEX, WINSIZEY, true, MAGENTA);
		IMAGEMANAGER->addImage("mainMenu", "source/mainMenu.bmp", WINSIZEX, WINSIZEY, false, MAGENTA);
		IMAGEMANAGER->addImage("mainMenubox", "source/mainmenubox.bmp", 330, 70, true, MAGENTA);
        IMAGEMANAGER->addImage("bossBackground", "source/Level 1 - Boss Room.bmp", WINSIZEX, WINSIZEY, true, MAGENTA);
        IMAGEMANAGER->addImage("shadow", "source/Shadow.bmp", 126, 36, true, RGB(255,0,255));
        IMAGEMANAGER->addImage("title", "source/titleImage.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
        IMAGEMANAGER->addImage("background", "source/Level 1 - Frozen Suburbs.bmp", 31812, 1000, true, RGB(255, 0, 255));
        IMAGEMANAGER->addImage("settingBackGround", "source/settingScene.bmp", WINSIZEX, WINSIZEY, true, MAGENTA);
        IMAGEMANAGER->addImage("mainMenu", "source/mainMenu.bmp", WINSIZEX, WINSIZEY, false, MAGENTA);
        IMAGEMANAGER->addImage("mainMenubox", "source/mainmenubox.bmp", 200, 50, true, MAGENTA);
        IMAGEMANAGER->addImage("bossBackground", "source/Level 1 - Boss Room.bmp", WINSIZEX, WINSIZEY, true, MAGENTA);
        IMAGEMANAGER->addImage("shadow", "source/Shadow.bmp", 126, 36, true, RGB(255, 0, 255));
        IMAGEMANAGER->addImage("col", "source/col.bmp", 31812, 1000, false, RGB(255, 0, 255));
#pragma endregion


#pragma region 사운드 추가
        SOUNDMANAGER->addSound("상점", "source/music/상점.mp3", true, true);
        SOUNDMANAGER->addSound("인게임", "source/music/인게임.mp3", true, true);
        SOUNDMANAGER->addSound("보스방", "source/music/보스방.mp3", true, true);
        SOUNDMANAGER->addSound("강펀치", "source/music/효과음/강펀치.mp3", true, true);
        SOUNDMANAGER->addSound("고고", "source/music/효과음/고고.mp3", true, true);
        SOUNDMANAGER->addSound("동전먹기", "source/music/효과음/동전먹기.mp3", true, false);
        SOUNDMANAGER->addSound("막기", "source/music/효과음/막기.mp3", true, true);
        SOUNDMANAGER->addSound("문열기", "source/music/효과음/문열기.mp3", true, true);
        SOUNDMANAGER->addSound("보스에네르기파", "source/music/효과음/보스에네르기파.mp3", true, true);
        SOUNDMANAGER->addSound("악마누나쏘고사라지는소리", "source/music/효과음/악마누나쏘고사라지는소리.mp3", true, true);
        SOUNDMANAGER->addSound("악마패턴1", "source/music/효과음/악마패턴1.mp3", true, true);
        SOUNDMANAGER->addSound("펀치", "source/music/효과음/펀치.mp3", true, true);
        SOUNDMANAGER->addSound("허공펀치", "source/music/효과음/허공펀치.mp3", true, true);
        SOUNDMANAGER->addSound("휘리릭킥", "source/music/효과음/휘리릭킥.mp3", true, true);
#pragma endregion
        //루크 이미지 저장소
#pragma region LUKEIMAGES

        IMAGEMANAGER->addFrameImage("LUKE_INIT", "LUKE/LUKE_INIT.bmp", 240, 480, 1, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_IDLE", "LUKE/LUKE_IDLE.bmp", 2880, 480, 12, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_WALK", "LUKE/LUKE_WALK.bmp", 4320, 480, 18, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_RUN", "LUKE/LUKE_RUN.bmp", 5760, 480, 24, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_JUMP", "LUKE/LUKE_JUMP.bmp", 2400, 480, 10, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_PUNCH", "LUKE/LUKE_PUNCH.bmp", 1920, 480, 8, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_KICK", "LUKE/LUKE_KICK.bmp", 1680, 480, 7, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_FINISHKICK", "LUKE/LUKE_FINISHKICK.bmp", 1680, 480, 7, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_DAMAGED", "LUKE/LUKE_DAMAGED.bmp", 1680, 480, 7, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_DOWN", "LUKE/LUKE_DOWN.bmp", 3360, 480, 14, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_DOWN_DAMAGED", "LUKE/LUKE_DOWN_DAMAGED.bmp", 960, 480, 4, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_UP", "LUKE/LUKE_UP.bmp", 1920, 480, 8, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_GUARD", "LUKE/LUKE_GUARD.bmp", 720, 480, 3, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_OBJECT_ATTACK", "LUKE/LUKE_OBJECT_ATTACK.bmp", 2880, 480, 12, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_OBJECT_THROW_SELF_DAMAGED", "LUKE/LUKE_OBJECT_THROW_SELF_DAMAGED.bmp", 3120, 480, 13, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("LUKE_OBJECT_GRAB", "LUKE/LUKE_OBJECT_GRAB.bmp", 1200, 480, 5, 2, true, RGB(255, 0, 255));

#pragma endregion

        //마이크 이미지 저장소
#pragma region MIKEIMAGES
        IMAGEMANAGER->addFrameImage("MIKE_INIT", "MIKE/MIKE_INIT.bmp", 240, 480, 1, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_IDLE", "MIKE/MIKE_IDLE.bmp", 2880, 480, 12, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_WALK", "MIKE/MIKE_WALK.bmp", 4320, 480, 18, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_RUN", "MIKE/MIKE_RUN.bmp", 5760, 480, 24, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_JUMP", "MIKE/MIKE_JUMP.bmp", 2160, 480, 9, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_ATTACK1", "MIKE/MIKE_ATTACK1.bmp", 1920, 480, 8, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_ATTACK2", "MIKE/MIKE_ATTACK2.bmp", 1680, 480, 7, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_ATTACK3", "MIKE/MIKE_ATTACK3.bmp", 1680, 480, 7, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_DAMAGED", "MIKE/MIKE_DAMAGED.bmp", 1680, 480, 7, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_DOWN", "MIKE/MIKE_DOWN.bmp", 3360, 480, 14, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_DOWN_DAMAGED", "MIKE/MIKE_DOWN_DAMAGED.bmp", 960, 480, 4, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_UP", "MIKE/MIKE_UP.bmp", 1920, 480, 8, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_GUARD", "MIKE/MIKE_GUARD.bmp", 720, 480, 3, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_OBJECT_ATTACK", "MIKE/MIKE_OBJECT_ATTACK.bmp", 2880, 480, 12, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_OBJECT_THROW_SELF_DAMAGED", "MIKE/MIKE_OBJECT_THROW_SELF_DAMAGED.bmp", 3120, 480, 13, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MIKE_OBJECT_GRAB", "MIKE/MIKE_OBJECT_GRAB.bmp", 1200, 480, 5, 2, true, RGB(255, 0, 255));
#pragma endregion

        //말콤 이미지 저장소
#pragma region MALCOLMIMAGES

        IMAGEMANAGER->addFrameImage("MALCOLM_IDLE", "MALCOLM/MALCOLM_IDLE.bmp", 1400, 700, 4, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MALCOLM_WALK", "MALCOLM/MALCOLM_WALK.bmp", 2800, 700, 8, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MALCOLM_RUN", "MALCOLM/MALCOLM_RUN.bmp", 2800, 700, 8, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MALCOLM_JUMP", "MALCOLM/MALCOLM_JUMP.bmp", 4550, 700, 13, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MALCOLM_ATTACK1", "MALCOLM/MALCOLM_ATTACK1.bmp", 3150, 700, 9, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MALCOLM_ATTACK2", "MALCOLM/MALCOLM_ATTACK2.bmp", 1400, 700, 4, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MALCOLM_ATTACK3", "MALCOLM/MALCOLM_ATTACK3.bmp", 1750, 700, 5, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MALCOLM_ATTACK4", "MALCOLM/MALCOLM_ATTACK4.bmp", 2800, 700, 8, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MALCOLM_DAMAGED", "MALCOLM/MALCOLM_DAMAGED.bmp", 2450, 700, 7, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MALCOLM_DOWN", "MALCOLM/MALCOLM_DOWN.bmp", 4900, 700, 14, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MALCOLM_DOWN_DAMAGED", "MALCOLM/MALCOLM_DOWN_DAMAGED.bmp", 1750, 700, 5, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MALCOLM_DOWN_ATTACK", "MALCOLM/MALCOLM_DOWN_ATTACK.bmp", 1750, 700, 5, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MALCOLM_UP", "MALCOLM/MALCOLM_UP.bmp", 3150, 700, 9, 2, true, RGB(255, 0, 255));
        IMAGEMANAGER->addFrameImage("MALCOLM_GUARD", "MALCOLM/MALCOLM_GUARD.bmp", 700, 700, 2, 2, true, RGB(255, 0, 255));

#pragma endregion

        //루크 애니메이션 저장소
#pragma region LUKEANIMATIONS
        int LUKEleftInit[] = { 0 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleftInit", "LUKE_INIT", LUKEleftInit, 1, 8, true);
        int LUKErightInit[] = { 1 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKErightInit", "LUKE_INIT", LUKErightInit, 1, 8, true);

        int LUKEleftIdle[] = { 11,10,9,8 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleftIdle", "LUKE_IDLE", LUKEleftIdle, 4, 8, true);
        int LUKErightIdle[] = { 12,13,14,15 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKErightIdle", "LUKE_IDLE", LUKErightIdle, 4, 8, true);

        int LUKEleftWalk[] = { 17,16,15,14,13,12 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleftWalk", "LUKE_WALK", LUKEleftWalk, 6, 8, true);
        int LUKErightWalk[] = { 18,19,20,21,22,23 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKErightWalk", "LUKE_WALK", LUKErightWalk, 6, 8, true);

        int LUKEleftRun[] = { 23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleftRun", "LUKE_RUN", LUKEleftRun, 16, 8, true);
        int LUKErightRun[] = { 24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKErightRun", "LUKE_RUN", LUKErightRun, 16, 8, true);

        int LUKEleftJump[] = { 4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleftJump", "LUKE_JUMP", LUKEleftJump, 5, 6, true);
        int LUKErightJump[] = { 10,11,12,13,14 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKErightJump", "LUKE_JUMP", LUKErightJump, 5, 6, true);
        int LUKEleftFall[] = { 9,8,7,6,5 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleftFall", "LUKE_JUMP", LUKEleftFall, 5, 6, true);
        int LUKErightFall[] = { 15,16,17,18,19 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKErightFall", "LUKE_JUMP", LUKErightFall, 5, 6, true);

        int LUKEleftAttack1[] = { 7,6,5,4 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKE_LEFT_PUNCH_1", "LUKE_PUNCH", LUKEleftAttack1, 4, 8, false);
        int LUKErightAttack1[] = { 8,9,10,11 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKE_RIGHT_PUNCH_1", "LUKE_PUNCH", LUKErightAttack1, 4, 8, false);
        int LUKEleftAttack2[] = { 3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKE_LEFT_PUNCH_2", "LUKE_PUNCH", LUKEleftAttack2, 4, 8, false);
        int LUKErightAttack2[] = { 12,13,14,15 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKE_RIGHT_PUNCH_2", "LUKE_PUNCH", LUKErightAttack2, 4, 8, false);
        int LUKEleftAttack3[] = { 6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKE_LEFT_KICK", "LUKE_KICK", LUKEleftAttack3, 7, 8, false);
        int LUKErightAttack3[] = { 7,8,9,10,11,12,13 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKE_RIGHT_KICK", "LUKE_KICK", LUKErightAttack3, 7, 8, false);
        int LUKEleftAttack4[] = { 6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKE_LEFT_FINISHKICK", "LUKE_FINISHKICK", LUKEleftAttack4, 7, 8, false);
        int LUKErightAttack4[] = { 7,8,9,10,11,12,13 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKE_RIGHT_FINISHKICK", "LUKE_FINISHKICK", LUKErightAttack4, 7, 8, false);

        int LUKEleftDamaged_1[] = { 6,5,4 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKE_LEFT_DAMAGED_1", "LUKE_DAMAGED", LUKEleftDamaged_1, 3, 8, false);
        int LUKEleftDamaged_2[] = { 3,2,1 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKE_LEFT_DAMAGED_2", "LUKE_DAMAGED", LUKEleftDamaged_2, 3, 8, false);
        int LUKE_Left_Stun[] = { 0 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKE_LEFT_STUN", "LUKE_DAMAGED", LUKE_Left_Stun, 1, 8, false);

        int LUKErightDamaged_1[] = { 7,8,9 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKE_RIGHT_DAMAGED_1", "LUKE_DAMAGED", LUKErightDamaged_1, 3, 8, false);
        int LUKErightDamaged_2[] = { 10,11,12 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKE_RIGHT_DAMAGED_2", "LUKE_DAMAGED", LUKErightDamaged_2, 3, 8, false);
        int LUKE_Right_Stun[] = { 13 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKE_Right_STUN", "LUKE_DAMAGED", LUKE_Right_Stun, 1, 8, false);


        int LUKEleftDown[] = { 13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleftDown", "LUKE_DOWN", LUKEleftDown, 14, 8, false);
        int LUKErightDown[] = { 14,15,16,17,18,19,20,21,22,23,24,25,26,27 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKErightDown", "LUKE_DOWN", LUKErightDown, 14, 8, false);
        int LUKEleftDown_Damaged[] = { 3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleftDown_Damaged", "LUKE_DOWN_DAMAGED", LUKEleftDown_Damaged, 4, 10, false);
        int LUKErightDown_Damaged[] = { 4,5,6,7 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKErightDown_Damaged", "LUKE_DOWN_DAMAGED", LUKErightDown_Damaged, 4, 10, false);
        int LUKEleftUp[] = { 7,6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleftUp", "LUKE_UP", LUKEleftUp, 8, 8, false);
        int LUKErightUp[] = { 8,9,10,11,12,13,14,15 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKErightUp", "LUKE_UP", LUKErightUp, 8, 8, false);
        int LUKEleftGuard[] = { 2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleftGuard", "LUKE_GUARD", LUKEleftGuard, 3, 8, false);
        int LUKErightGuard[] = { 3,4,5 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKErightGuard", "LUKE_GUARD", LUKErightGuard, 3, 8, false);
        int LUKEleftObject_Hang[] = { 3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleftObject_Hang", "LUKE_IDLE", LUKEleftObject_Hang, 4, 8, true);
        int LUKErightObject_Hang[] = { 20,21,22,23 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKErightObject_Hang", "LUKE_IDLE", LUKErightObject_Hang, 4, 8, true);
        int LUKEleftObject_Attack[] = { 6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleftObject_Attack", "LUKE_OBJECT_ATTACK", LUKEleftObject_Attack, 7, 8, false);
        int LUKErightObject_Attack[] = { 17,18,19,20,21,22,23 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKErightObject_Attack", "LUKE_OBJECT_ATTACK", LUKErightObject_Attack, 7, 8, false);
        int LUKEleftObject_Throw[] = { 11,10,9,8,7 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleftObject_Throw", "LUKE_OBJECT_ATTACK", LUKEleftObject_Throw, 5, 8, false);
        int LUKErightObject_Throw[] = { 12,13,14,15,16 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKErightObject_Throw", "LUKE_OBJECT_ATTACK", LUKErightObject_Throw, 5, 8, false);
        int LUKEleft_Big_Object_Grab[] = { 4,3 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleft_Big_Object_Grab", "LUKE_OBJECT_GRAB", LUKEleft_Big_Object_Grab, 2, 8, false);
        int LUKEright_Big_Object_Grab[] = { 5,6 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEright_Big_Object_Grab", "LUKE_OBJECT_GRAB", LUKEright_Big_Object_Grab, 2, 8, false);
        int LUKEleft_Small_Object_Grab[] = { 2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEleft_Small_Object_Grab", "LUKE_OBJECT_GRAB", LUKEleft_Small_Object_Grab, 3, 8, false);
        int LUKEright_Small_Object_Grab[] = { 7,8,9 };
        KEYANIMANAGER->addArrayFrameAnimation("LUKEright_Small_Object_Grab", "LUKE_OBJECT_GRAB", LUKEright_Small_Object_Grab, 3, 8, false);
#pragma endregion

        //마이크 애니메이션 저장소
#pragma region MIKEANIMATIONS
        int MIKEleftInit[] = { 0 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftInit", "MIKE_INIT", MIKEleftInit, 1, 8, true);
        int MIKErightInit[] = { 1 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightInit", "MIKE_INIT", MIKErightInit, 1, 8, true);

        int MIKEleftIdle[] = { 11,10,9,8 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftIdle", "MIKE_IDLE", MIKEleftIdle, 4, 8, true);
        int MIKErightIdle[] = { 12,13,14,15 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightIdle", "MIKE_IDLE", MIKErightIdle, 4, 8, true);

        int MIKEleftWalk[] = { 17,16,15,14,13,12 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftWalk", "MIKE_WALK", MIKEleftWalk, 6, 8, true);
        int MIKErightWalk[] = { 18,19,20,21,22,23 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightWalk", "MIKE_WALK", MIKErightWalk, 6, 8, true);

        int MIKEleftRun[] = { 23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftRun", "MIKE_RUN", MIKEleftRun, 16, 8, true);
        int MIKErightRun[] = { 24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightRun", "MIKE_RUN", MIKErightRun, 16, 8, true);

        int MIKEleftJump[] = { 8,7,6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftJump", "MIKE_JUMP", MIKEleftJump, 9, 8, true);
        int MIKErightJump[] = { 9,10,11,12,13,14,15,16,17 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightJump", "MIKE_JUMP", MIKErightJump, 9, 8, true);

        int MIKEleftAttack1[] = { 7,6,5,4 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftAttack1", "MIKE_ATTACK1", MIKEleftAttack1, 4, 8, false);
        int MIKErightAttack1[] = { 8,9,10,11 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightAttack1", "MIKE_ATTACK1", MIKErightAttack1, 4, 8, false);
        int MIKEleftAttack2[] = { 3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftAttack2", "MIKE_ATTACK1", MIKEleftAttack2, 4, 8, false);
        int MIKErightAttack2[] = { 12,13,14,15 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightAttack2", "MIKE_ATTACK1", MIKErightAttack2, 4, 8, false);
        int MIKEleftAttack3[] = { 6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftAttack3", "MIKE_ATTACK2", MIKEleftAttack3, 7, 8, false);
        int MIKErightAttack3[] = { 7,8,9,10,11,12,13 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightAttack3", "MIKE_ATTACK2", MIKErightAttack3, 7, 8, false);
        int MIKEleftAttack4[] = { 6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftAttack4", "MIKE_ATTACK3", MIKEleftAttack4, 7, 8, false);
        int MIKErightAttack4[] = { 7,8,9,10,11,12,13 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightAttack4", "MIKE_ATTACK3", MIKErightAttack4, 7, 8, false);

        int MIKEleftDamaged[] = { 6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftDamaged", "MIKE_DAMAGED", MIKEleftDamaged, 7, 8, false);
        int MIKErightDamaged[] = { 7,8,9,10,11,12,13 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightDamaged", "MIKE_DAMAGED", MIKErightDamaged, 7, 8, false);

        int MIKEleftDown[] = { 13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftDown", "MIKE_DOWN", MIKEleftDown, 14, 8, false);
        int MIKErightDown[] = { 14,15,16,17,18,19,20,21,22,23,24,25,26,27 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightDown", "MIKE_DOWN", MIKErightDown, 14, 8, false);

        int MIKEleftDown_Damaged[] = { 3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftDown_Damaged", "MIKE_DOWN_DAMAGED", MIKEleftDown_Damaged, 4, 8, false);
        int MIKErightDown_Damaged[] = { 4,5,6,7 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightDown_Damaged", "MIKE_DOWN_DAMAGED", MIKErightDown_Damaged, 4, 8, false);
        int MIKEleftUp[] = { 7,6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftUp", "MIKE_UP", MIKEleftUp, 8, 8, false);
        int MIKErightUp[] = { 8,9,10,11,12,13,14,15 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightUp", "MIKE_UP", MIKErightUp, 8, 8, false);
        int MIKEleftGuard[] = { 2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftGuard", "MIKE_GUARD", MIKEleftGuard, 3, 8, false);
        int MIKErightGuard[] = { 3,4,5 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightGuard", "MIKE_GUARD", MIKErightGuard, 3, 8, false);
        int MIKEleftObject_Hang[] = { 3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftObject_Hang", "MIKE_IDLE", MIKEleftObject_Hang, 4, 8, true);
        int MIKErightObject_Hang[] = { 20,21,22,23 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightObject_Hang", "MIKE_IDLE", MIKErightObject_Hang, 4, 8, true);
        int MIKEleftObject_Attack[] = { 6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftObject_Attack", "MIKE_OBJECT_ATTACK", MIKEleftObject_Attack, 7, 8, false);
        int MIKErightObject_Attack[] = { 17,18,19,20,21,22,23 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightObject_Attack", "MIKE_OBJECT_ATTACK", MIKErightObject_Attack, 7, 8, false);
        int MIKEleftObject_Throw[] = { 11,10,9,8,7 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleftObject_Throw", "MIKE_OBJECT_ATTACK", MIKEleftObject_Throw, 5, 6, false);
        int MIKErightObject_Throw[] = { 12,13,14,15,16 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKErightObject_Throw", "MIKE_OBJECT_ATTACK", MIKErightObject_Throw, 5, 6, false);
        int MIKEleft_Big_Object_Grab[] = { 4,3 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleft_Big_Object_Grab", "MIKE_OBJECT_GRAB", MIKEleft_Big_Object_Grab, 2, 6, true);
        int MIKEright_Big_Object_Grab[] = { 5,6 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEright_Big_Object_Grab", "MIKE_OBJECT_GRAB", MIKEright_Big_Object_Grab, 2, 6, true);
        int MIKEleft_Small_Object_Grab[] = { 2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEleft_Small_Object_Grab", "MIKE_OBJECT_GRAB", MIKEleft_Small_Object_Grab, 3, 6, true);
        int MIKEright_Small_Object_Grab[] = { 7,8,9 };
        KEYANIMANAGER->addArrayFrameAnimation("MIKEright_Small_Object_Grab", "MIKE_OBJECT_GRAB", MIKEright_Small_Object_Grab, 3, 6, true);
#pragma endregion

        //말콤 애니메이션 저장소
#pragma region MALCOLMANIMATIONS
        int MALCOLMleftIdle[] = { 3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMleftIdle", "MALCOLM_IDLE", MALCOLMleftIdle, 4, 8, true);
        int MALCOLMrightIdle[] = { 4,5,6,7 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMrightIdle", "MALCOLM_IDLE", MALCOLMrightIdle, 4, 8, true);

        int MALCOLMleftWalk[] = { 7,6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMleftWalk", "MALCOLM_WALK", MALCOLMleftWalk, 8, 8, true);
        int MALCOLMrightWalk[] = { 8,9,10,11,12,13,14,15 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMrightWalk", "MALCOLM_WALK", MALCOLMrightWalk, 8, 8, true);

        int MALCOLMleftRun[] = { 7,6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMleftRun", "MALCOLM_RUN", MALCOLMleftRun, 8, 8, true);
        int MALCOLMrightRun[] = { 8,9,10,11,12,13,14,15 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMrightRun", "MALCOLM_RUN", MALCOLMrightRun, 8, 8, true);

        int MALCOLMleftJump[] = { 12,11,10,9,8,7,6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMleftJump", "MALCOLM_JUMP", MALCOLMleftJump, 13, 8, true);
        int MALCOLMrightJump[] = { 13,14,15,16,17,18,19,20,21,22,23,24,25 };

        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMrightJump", "MALCOLM_JUMP", MALCOLMrightJump, 13, 8, true);
        int MALCOLMleftAttack1[] = { 8,7,6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMleftAttack1", "MALCOLM_ATTACK1", MALCOLMleftAttack1, 9, 8, false);
        int MALCOLMrightAttack1[] = { 9,10,11,12,13,14,15,16,17 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMrightAttack1", "MALCOLM_ATTACK1", MALCOLMrightAttack1, 9, 8, false);

        int MALCOLMleftAttack2[] = { 3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMleftAttack2", "MALCOLM_ATTACK2", MALCOLMleftAttack2, 4, 8, false);
        int MALCOLMrightAttack2[] = { 4,5,6,7 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMrightAttack2", "MALCOLM_ATTACK2", MALCOLMrightAttack2, 4, 8, false);

        int MALCOLMleftAttack3[] = { 4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMleftAttack3", "MALCOLM_ATTACK3", MALCOLMleftAttack3, 5, 8, false);
        int MALCOLMrightAttack3[] = { 5,6,7,8,9 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMrightAttack3", "MALCOLM_ATTACK3", MALCOLMrightAttack3, 5, 8, false);

        int MALCOLMleftAttack4[] = { 7,6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMleftAttack4", "MALCOLM_ATTACK4", MALCOLMleftAttack4, 8, 8, false);
        int MALCOLMrightAttack4[] = { 8,9,10,11,12,13,14,15 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMrightAttack4", "MALCOLM_ATTACK4", MALCOLMrightAttack4, 8, 8, false);

        int MALCOLMleftDamaged[] = { 6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMleftDamaged", "MALCOLM_DAMAGED", MALCOLMleftDamaged, 7, 8, false);
        int MALCOLMrightDamaged[] = { 7,8,9,10,11,12,13 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMrightDamaged", "MALCOLM_DAMAGED", MALCOLMrightDamaged, 7, 8, false);

        int MALCOLMleftDown[] = { 13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMleftDown", "MALCOLM_DOWN", MALCOLMleftDown, 14, 8, false);
        int MALCOLMrightDown[] = { 14,15,16,17,18,19,20,21,22,23,24,25,26,27 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMrightDown", "MALCOLM_DOWN", MALCOLMrightDown, 14, 8, false);

        int MALCOLMleftDown_Damaged[] = { 4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMleftDown_Damaged", "MALCOLM_DOWN_DAMAGED", MALCOLMleftDown_Damaged, 5, 8, false);
        int MALCOLMrightDown_Damaged[] = { 5,6,7,8,9 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMrightDown_Damaged", "MALCOLM_DOWN_DAMAGED", MALCOLMrightDown_Damaged, 5, 8, false);

        int MALCOLMleftUp[] = { 8,7,6,5,4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMleftUp", "MALCOLM_UP", MALCOLMleftUp, 9, 8, false);
        int MALCOLMrightUp[] = { 9,10,11,12,13,14,15,16,17 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMrightUp", "MALCOLM_UP", MALCOLMrightUp, 9, 8, false);

        int MALCOLMleftGuard[] = { 1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMleftGuard", "MALCOLM_GUARD", MALCOLMleftGuard, 2, 8, false);
        int MALCOLMrightGuard[] = { 2,3 };
        KEYANIMANAGER->addArrayFrameAnimation("MALCOLMrightGuard", "MALCOLM_GUARD", MALCOLMrightGuard, 2, 8, false);

#pragma endregion

#pragma region Object Images
       //COIN 오브젝트
        IMAGEMANAGER->addFrameImage("smallCoin", "source/object/coin/smallCoin.bmp", 300, 50, 6, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("mediumCoin", "source/object/coin/mediumCoin.bmp", 360, 60, 6, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("largeCoin", "source/object/coin/largeCoin.bmp", 384, 64, 6, 1, true, MAGENTA);

        int smallCoin[] = { 0, 1, 2, 3, 4, 5 };
        KEYANIMANAGER->addArrayFrameAnimation("smallCoin", "smallCoin", smallCoin, 6, 8, true);
        int mediumCoin[] = { 0, 1, 2, 3, 4, 5 };
        KEYANIMANAGER->addArrayFrameAnimation("mediumCoin", "mediumCoin", mediumCoin, 6, 8, true);
        int largeCoin[] = { 0, 1, 2, 3, 4, 5 };
        KEYANIMANAGER->addArrayFrameAnimation("largeCoin", "largeCoin", largeCoin, 6, 8, true);


        //BAT 오브젝트 
        IMAGEMANAGER->addFrameImage("bat_left_atk", "source/object/bat/bat_left_atk.bmp", 1875, 375, 5, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_left_dash", "source/object/bat/bat_left_dash.bmp", 3000, 375, 8, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_left_get", "source/object/bat/bat_left_get.bmp", 750, 375, 2, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_left_idle", "source/object/bat/bat_left_atk.bmp", 1500, 375, 4, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_left_jump", "source/object/bat/bat_left_jump.bmp", 3000, 750, 8, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_left_neutral", "source/object/bat/bat_left_neutral.bmp", 375, 375, 1, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_left_neutral2", "source/object/bat/bat_left_neutral2.bmp", 750, 375, 2, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_left_throw", "source/object/bat/bat_left_throw.bmp", 750, 375, 2, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_left_walk", "source/object/bat/bat_left_walk.bmp", 2250, 375, 6, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_right_atk", "source/object/bat/bat_right_atk.bmp", 1875, 375, 5, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_right_dash", "source/object/bat/bat_right_dash.bmp", 3000, 375, 8, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_right_get", "source/object/bat/bat_right_get.bmp", 750, 375, 2, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_right_idle", "source/object/bat/bat_right_idle.bmp", 1500, 375, 4, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_right_jump", "source/object/bat/bat_right_jump.bmp", 3000, 750, 8, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_right_neutral", "source/object/bat/bat_right_neutral.bmp", 375, 375, 1, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_right_neutral2", "source/object/bat/bat_right_neutral2.bmp", 750, 375, 2, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_right_throw", "source/object/bat/bat_right_throw.bmp", 750, 375, 2, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("bat_right_walk", "source/object/bat/bat_right_walk.bmp", 2250, 375, 6, 1, true, MAGENTA);


        int bat_left_atk[] = { 0,1,2,3,4 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_left_atk", "bat_left_atk", bat_left_atk, 5, 8, false);
        int bat_left_dash[] = { 0,1,2,3,4,5,6,7 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_left_dash", "bat_left_dash", bat_left_dash, 5, 8, false);
        int bat_left_get[] = { 0,1 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_left_get", "bat_left_get", bat_left_get, 2, 8, false);
        int bat_left_idle[] = { 0,1,2,3 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_left_idle", "bat_left_idle", bat_left_idle, 4, 8, false);
        int bat_left_jump[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_left_jump", "bat_left_jump", bat_left_jump, 16, 8, false);
        int bat_left_neutral[] = { 0 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_left_neutral", "bat_left_neutral", bat_left_neutral, 1, 8, false);
        int bat_left_neutral2[] = { 0,1 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_left_neutral2", "bat_left_neutral2", bat_left_neutral2, 2, 8, false);
        int bat_left_throw[] = { 0,1 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_left_throw", "bat_left_throw", bat_left_throw, 2, 8, false);
        int bat_left_walk[] = { 0,1,2,3,4,5 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_left_walk", "bat_left_walk", bat_left_walk, 6, 8, false);

        int bat_right_atk[] = { 0,1,2,3,4 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_right_atk", "bat_right_atk", bat_right_atk, 5, 8, false);
        int bat_right_dash[] = { 0,1,2,3,4,5,6,7 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_right_dash", "bat_right_dash", bat_right_dash, 5, 8, false);
        int bat_right_get[] = { 0,1 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_right_get", "bat_right_get", bat_right_get, 2, 8, false);
        int bat_right_idle[] = { 0,1,2,3 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_right_idle", "bat_right_idle", bat_right_idle, 4, 8, false);
        int bat_right_jump[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_right_jump", "bat_right_jump", bat_right_jump, 16, 8, false);
        int bat_right_neutral[] = { 0 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_right_neutral", "bat_right_neutral", bat_right_neutral, 1, 8, false);
        int bat_right_neutral2[] = { 0,1 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_right_neutral2", "bat_right_neutral2", bat_right_neutral2, 2, 8, false);
        int bat_right_throw[] = { 0,1 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_right_throw", "bat_right_throw", bat_right_throw, 2, 8, false);
        int bat_right_walk[] = { 0,1,2,3,4,5 };
        KEYANIMANAGER->addArrayFrameAnimation("bat_right_walk", "bat_right_walk", bat_right_walk, 6, 8, false);


        //TRASH 오브젝트
        IMAGEMANAGER->addFrameImage("trash_left_atk", "source/object/trash/trash_left_atk.bmp", 2250, 375, 6, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_left_dash", "source/object/trash/trash_left_dash.bmp", 3000, 375, 8, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_left_get", "source/object/trash/trash_left_get.bmp", 750, 375, 2, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_left_idle", "source/object/trash/trash_left_idle.bmp", 1500, 375, 4, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_left_jump", "source/object/trash/trash_left_jump.bmp", 3375, 750, 9, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_left_neutral", "source/object/trash/trash_left_neutral.bmp", 750, 375, 2, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_left_throw", "source/object/trash/trash_left_throw.bmp", 1125, 375, 3, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_left_walk", "source/object/trash/trash_left_walk.bmp", 2250, 375, 6, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_right_atk", "source/object/trash/trash_right_atk.bmp", 2250, 375, 6, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_right_dash", "source/object/trash/trash_right_dash.bmp", 3000, 375, 8, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_right_get", "source/object/trash/trash_right_get.bmp", 750, 375, 2, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_right_idle", "source/object/trash/trash_right_idle.bmp", 1500, 375, 4, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_right_jump", "source/object/trash/trash_right_jump.bmp", 3375, 750, 9, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_right_neutral", "source/object/trash/trash_right_neutral.bmp", 750, 375, 2, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_right_throw", "source/object/trash/trash_right_throw.bmp", 1125, 375, 3, 1, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("trash_right_walk", "source/object/trash/trash_right_walk.bmp", 2250, 375, 6, 1, true, MAGENTA);

        int trash_left_atk[] = { 0,1,2,3,4,5 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_left_atk", "trash_left_atk", trash_left_atk, 6, 8, false);
        int trash_left_dash[] = { 0,1,2,3,4,5,6,7 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_left_dash", "trash_left_dash", trash_left_dash, 8, 8, false);
        int trash_left_get[] = { 0,1 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_left_get", "trash_left_get", trash_left_get, 2, 8, false);
        int trash_left_idle[] = { 0,1,2,3 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_left_idle", "trash_left_idle", trash_left_idle, 4, 8, false);
        int trash_left_jump[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_left_jump", "trash_left_jump", trash_left_jump, 9, 8, false);
        int trash_left_neutral[] = { 0,1 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_left_neutral", "trash_left_neutral", trash_left_neutral, 2, 8, false);
        int trash_left_throw[] = { 0,1,2 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_left_throw", "trash_left_throw", trash_left_throw, 3, 8, false);
        int trash_left_walk[] = { 0,1,2,3,4,5 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_left_walk", "trash_left_walk", trash_left_walk, 6, 8, false);

        int trash_right_atk[] = { 0,1,2,3,4,5 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_right_atk", "trash_right_atk", trash_right_atk, 6, 8, false);
        int trash_right_dash[] = { 0,1,2,3,4,5,6,7 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_right_dash", "trash_right_dash", trash_right_dash, 8, 8, false);
        int trash_right_get[] = { 0,1 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_right_get", "trash_right_get", trash_right_get, 2, 8, false);
        int trash_right_idle[] = { 0,1,2,3 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_right_idle", "trash_right_idle", trash_right_idle, 4, 8, false);
        int trash_right_jump[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_right_jump", "trash_right_jump", trash_right_jump, 9, 8, false);
        int trash_right_neutral[] = { 0,1 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_right_neutral", "trash_right_neutral", trash_right_neutral, 2, 8, false);
        int trash_right_throw[] = { 0,1,2 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_right_throw", "trash_right_throw", trash_right_throw, 3, 8, false);
        int trash_right_walk[] = { 0,1,2,3,4,5 };
        KEYANIMANAGER->addArrayFrameAnimation("trash_right_walk", "trash_right_walk", trash_right_walk, 6, 8, false);




#pragma endregion


#pragma region Ramona Images
        IMAGEMANAGER->addFrameImage("Ramona_Idle", "Ramona/Idle.bmp", 2064, 960, 6, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("Ramona_Jump", "Ramona/Jump_Loop.bmp", 344, 960, 1, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("Ramona_Fall", "Ramona/Fall.bmp", 2064, 960, 6, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("Ramona_Walk", "Ramona/Walk.bmp", 2064, 960, 6, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("Ramona_Land", "Ramona/Land.bmp", 344, 960, 1, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("Ramona_Run", "Ramona/Run.bmp", 2752, 960, 8, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("Ramona_Damaged", "Ramona/Damage_Front.bmp", 1376, 960, 4, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("Ramona_Down", "Ramona/Knock_Down.bmp", 4472, 960, 13, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("Ramona_GetUp", "Ramona/Get_Up.bmp", 3096, 960, 9, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("Ramona_Attack_0", "Ramona/Attack_Combo_0.bmp", 1032, 960, 3, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("Ramona_Attack_1", "Ramona/Attack_Combo_1.bmp", 1032, 960, 3, 2, true, MAGENTA);
        IMAGEMANAGER->addFrameImage("Ramona_Attack_2", "Ramona/Attack_Combo_2.bmp", 1032, 960, 3, 2, true, MAGENTA);

#pragma endregion

#pragma region bossImage & animation

        IMAGEMANAGER->addFrameImage("BOSS IDLE", "source/BOSS/BOSS IDLE.bmp", 2277, 600, 6, 2, true, MAGENTA);

        int bossLeftIdleArr[] = { 0, 1, 2, 3, 4, 5 };
        KEYANIMANAGER->addArrayFrameAnimation("bossRightIdle", "BOSS IDLE", bossLeftIdleArr, 6, 6, true);
        int bossRightIdleArr[] = { 6, 7, 8, 9, 10, 11 };
        KEYANIMANAGER->addArrayFrameAnimation("bossLeftIdle", "BOSS IDLE", bossRightIdleArr, 6, 6, true);


        IMAGEMANAGER->addFrameImage("BOSS ATTACK1", "source/BOSS/BOSS ATTACK1.bmp", 2277, 600, 6, 2, true, MAGENTA);

        int bossLeftAttack1Arr[] = { 0,1,2,3,4,5 };
        KEYANIMANAGER->addArrayFrameAnimation("bossRightAttack1", "BOSS ATTACK1", bossLeftAttack1Arr, 6, 6, false);
        int bossRightAttack1Arr[] = { 11,10,9,8,7,6 };
        KEYANIMANAGER->addArrayFrameAnimation("bossLeftAttack1", "BOSS ATTACK1", bossRightAttack1Arr, 6, 6, false);


        IMAGEMANAGER->addFrameImage("BOSS ATTACK2", "source/BOSS/BOSS ATTACK2.bmp", 2277, 600, 6, 2, true, MAGENTA);

        int bossLeftAttack2Arr[] = { 0,1,2,3,4,5 };
        KEYANIMANAGER->addArrayFrameAnimation("bossRightAttack2", "BOSS ATTACK2", bossLeftAttack2Arr, 6, 6, false);
        int bossRightAttack2Arr[] = { 11,10,9,8,7,6 };
        KEYANIMANAGER->addArrayFrameAnimation("bossLeftAttack2", "BOSS ATTACK2", bossRightAttack2Arr, 6, 6, false);

        IMAGEMANAGER->addFrameImage("BOSS ATTACK3", "source/BOSS/BOSS ATTACK3.bmp", 2277, 600, 6, 2, true, MAGENTA);

        int bossRightAttack3Arr[] = { 0,1,2,3,4,5 };
        KEYANIMANAGER->addArrayFrameAnimation("bossRightAttack3", "BOSS ATTACK3", bossRightAttack3Arr, 6, 6, false);
        int bossLeftAttack3Arr[] = { 11,10,9,8,7,6 };
        KEYANIMANAGER->addArrayFrameAnimation("bossLeftAttack3", "BOSS ATTACK3", bossLeftAttack3Arr, 6, 6, false);

        IMAGEMANAGER->addFrameImage("BOSS SPECIAL ATTACK", "source/BOSS/BOSS SPECIAL ATTACK.bmp", 10500, 780, 14, 2, true, MAGENTA);

        int bossRightSpecialAttackArr[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13 };
        KEYANIMANAGER->addArrayFrameAnimation("bossRightSpecialAttack", "BOSS SPECIAL ATTACK", bossRightSpecialAttackArr, 14, 10, false);
        int bossLeftSpecialAttackArr[] = { 27,26,25,24,23,22,21,20,19,18,17,16,15,14 };
        KEYANIMANAGER->addArrayFrameAnimation("bossLeftSpecialAttack", "BOSS SPECIAL ATTACK", bossLeftSpecialAttackArr, 14, 10, false);

        IMAGEMANAGER->addFrameImage("BOSS SECOND PHASE", "source/BOSS/BOSS 2STATE.bmp", 5692, 675, 15, 1, true, MAGENTA);

        int bossSecondPhaseArr[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
        KEYANIMANAGER->addArrayFrameAnimation("bossSecondPhase", "BOSS SECOND PHASE", bossSecondPhaseArr, 15, 10, false);

        IMAGEMANAGER->addFrameImage("BOSS HITTED", "source/BOSS/BOSS DAMAGE.bmp", 1897, 600, 5, 2, true, MAGENTA);

        int bossRightHittedArr[] = { 4,3,2,1,0 };
        KEYANIMANAGER->addArrayFrameAnimation("bossRightHitted", "BOSS HITTED", bossRightHittedArr, 5, 10, false);
        int bossLeftHittedArr[] = { 5,6,7,8,9 };
        KEYANIMANAGER->addArrayFrameAnimation("bossLeftHitted", "BOSS HITTED", bossLeftHittedArr, 5, 10, false);

        IMAGEMANAGER->addFrameImage("BOSS DEATH", "source/BOSS/BOSS DEATH.bmp", 4933, 300, 13, 1, true, MAGENTA);

        int bossDeathArr[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };
        KEYANIMANAGER->addArrayFrameAnimation("bossDeath", "BOSS DEATH", bossDeathArr, 13, 8, false);

        IMAGEMANAGER->addFrameImage("BOSS RUN", "source/BOSS/BOSS RUN.bmp", 3036, 600, 8, 2, true, MAGENTA);

        int bossRightRunArr[] = { 0,1,2,3,4,5,6,7 };
        KEYANIMANAGER->addArrayFrameAnimation("bossRightRun", "BOSS RUN", bossRightRunArr, 8, 8, true);

        int bossLeftRunArr[] = { 15,14,13,12,11,10,9,8 };
        KEYANIMANAGER->addArrayFrameAnimation("bossLeftRun", "BOSS RUN", bossLeftRunArr, 8, 8, true);

        IMAGEMANAGER->addFrameImage("BOSS DOWN", "source/BOSS/BOSS DOWN.bmp", 5313, 600, 14, 2, true, MAGENTA);

        int bossRightDownArr[] = { 27,26,25,24,23,22,21,20,19,18,17,16,15,14 };
        KEYANIMANAGER->addArrayFrameAnimation("bossRightDown", "BOSS DOWN", bossRightDownArr, 14, 8, false);
        int bossLeftDownArr[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13 };
        KEYANIMANAGER->addArrayFrameAnimation("bossLeftDown", "BOSS DOWN", bossLeftDownArr, 14, 8, false);

        IMAGEMANAGER->addFrameImage("BOSS UP", "source/BOSS/BOSS UP.bmp", 4174, 600, 11, 2, true, MAGENTA);

        int bossRightUpArr[] = { 0,1,2,3,4,5,6,7,8,9,10 };
        KEYANIMANAGER->addArrayFrameAnimation("bossRightUp", "BOSS UP", bossRightUpArr, 11, 8, false);
        int bossLeftUpArr[] = { 21,20,19,18,17,16,15,14,13,12,11 };
        KEYANIMANAGER->addArrayFrameAnimation("bossLeftUp", "BOSS UP", bossLeftUpArr, 11, 8, false);

        IMAGEMANAGER->addFrameImage("BOSS DOWN KICK", "source/BOSS/BOSS DOWNKICK.bmp", 1518, 600, 4, 2, true, MAGENTA);

        int bossRightDownKick[] = { 0,1,2,3 };
        KEYANIMANAGER->addArrayFrameAnimation("bossRightDownKick", "BOSS DOWN KICK", bossRightDownKick, 4, 8, false);
        int bossLeftDownKick[] = { 7,6,5,4 };
        KEYANIMANAGER->addArrayFrameAnimation("bossLeftDownKick", "BOSS DOWN KICK", bossLeftDownKick, 4, 8, false);


#pragma endregion

#pragma region Shop
        IMAGEMANAGER->addImage("SHOP_CAFE", "SHOP/SHOP_CAFE.bmp", 1600, 900, true, MAGENTA);
        IMAGEMANAGER->addImage("SHOP_CONVENIENT", "SHOP/SHOP_CONVENIENTSTORE.bmp", 1600, 900, true, MAGENTA);
        IMAGEMANAGER->addImage("SHOP_RESTAURANT", "SHOP/SHOP_RESTAURANT.bmp", 1600, 900, true, MAGENTA);
        IMAGEMANAGER->addImage("SHOP_SUSHI", "SHOP/SHOP_SUSHI.bmp", 1600, 900, true, MAGENTA);
        IMAGEMANAGER->addImage("shopsceneBox", "SHOP/shopsceneBox.bmp", 400, 200, true, MAGENTA);


#pragma endregion

#pragma region devilImage & animation

#pragma endregion

        loadingHelper->_currentCount++;
    }

    return 0;
}
