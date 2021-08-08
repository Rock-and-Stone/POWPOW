#pragma once
#include "gameNode.h"

class CameraManager : public gameNode
{
private:
	int _posX;
	int _posY;

	int _renderPosX;
	int _renderPosY;

	int _mapSizeX;
	float _mapSizeY;

	RECT _rc;

public:
	CameraManager();
	~CameraManager();

	HRESULT init(int mapSizeX, float mapSizeY); //전체 맵 사이즈 ( 파일 가로, 세로 크기 )
	virtual void release();
	virtual void update(int playerX, int playerY); //현재 플레이어 좌표( PosX 랑 PosY )

	void CameraWork(int playerX, int playerY);
	void CameraClamp();

	int getRenderPosX() { return _renderPosX; } // 이 값을 메인에서 받아서 렌더 해줍니다.
	int getRenderPosY() { return _renderPosY; } 

	int getCamX() { return _rc.left; } // 배경에 적용될 카메라 좌표
	int getCamY() { return _rc.top; }

};

