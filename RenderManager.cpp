#include "pch.h"
#include "RenderManager.h"
#include "gameNode.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

HRESULT RenderManager::init()
{

	return S_OK;
}

void RenderManager::release()
{
	_vRender.clear();
}

void RenderManager::update()
{
	selectionSort();
	for (int i = 0; i < _vRender.size(); i++)
	{
		if (_vRender[i]->getReleased()) removeRender(i);
	}
	//bubbleSort();
}

void RenderManager::render(HDC hdc)
{
	char str[128];
	int i = 0;

	/*
	SetTextColor(hdc, RGB(255, 255, 255));
	char str[128];
	for (int i = 0; i < ARRSIZE; i++)
	{
		sprintf_s(str, "%d", _arr[i]);
		TextOut(hdc, 100 + 50 * i, 90, str, strlen(str));
	}*/

	for (_viRender = _vRender.begin(); _viRender != _vRender.end(); _viRender++)
	{
		(*_viRender)->render();
	}
}


void RenderManager::selectionSort()
{
	int minIndex;
	int i, j;
	for (i = 0; i < ARRSIZE - 1; i++) 
	{
		minIndex = i;
		for (j = i + 1; j < 10; j++)
			if (_arr[j] < _arr[minIndex])
				minIndex = j;

		swap(&_arr[i], &_arr[minIndex]);
	}

	for (i = 0; i < _vRender.size() - 1; i++)
	{
		minIndex = i;
		for (j = i+1; j < _vRender.size(); j++)
			if (_vRender[j]->getRenderPosY() < _vRender[minIndex]->getRenderPosY()) //렌더의 Y값을 가져와서 비교하여 스왑.
				minIndex = j;
		

		swap(&_vRender[i], &_vRender[minIndex]);
	}
}

void RenderManager::bubbleSort()
{
	int i, j;
	for (i = ARRSIZE - 1; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (_arr[j] > _arr[j + 1])
				swap(&_arr[j], &_arr[j + 1]);
		}
	}
}

void RenderManager::addRender(gameNode* obj)
{

	_vRender.push_back(obj);

}

void RenderManager::removeRender(int arrNum)
{
	_vRender.erase(_vRender.begin() + arrNum);
}

void RenderManager::swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void RenderManager::swap(gameNode** a, gameNode** b)
{
	gameNode* temp = *a;
	*a = *b;
	*b = temp;
}
