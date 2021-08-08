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

	HRESULT init(int mapSizeX, float mapSizeY); //��ü �� ������ ( ���� ����, ���� ũ�� )
	virtual void release();
	virtual void update(int playerX, int playerY); //���� �÷��̾� ��ǥ( PosX �� PosY )

	void CameraWork(int playerX, int playerY);
	void CameraClamp();

	int getRenderPosX() { return _renderPosX; } // �� ���� ���ο��� �޾Ƽ� ���� ���ݴϴ�.
	int getRenderPosY() { return _renderPosY; } 

	int getCamX() { return _rc.left; } // ��濡 ����� ī�޶� ��ǥ
	int getCamY() { return _rc.top; }

};

