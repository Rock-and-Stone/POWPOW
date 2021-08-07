#include "pch.h"
#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::init()
{

	return S_OK;
}

void EnemyManager::release()
{
}

void EnemyManager::update()
{
    //·çÅ© º¤ÅÍ ¾÷µ«
    for (_viLuke = _vLuke.begin(); _viLuke != _vLuke.end(); ++_viLuke)
    {
        (*_viLuke)->update();
    }
    //¸¶ÀÌÅ© º¤ÅÍ ¾÷µ«
    for (_viMike = _vMike.begin(); _viMike != _vMike.end(); ++_viMike)
    {
        (*_viMike)->update();
    }
    //¸»ÄÞ º¤ÅÍ ¾÷µ«
    for (_viMalcolm = _vMalcolm.begin(); _viMalcolm != _vMalcolm.end(); ++_viMalcolm)
    {
        (*_viMalcolm)->update();
    }

    KEYANIMANAGER->update();
    
}

void EnemyManager::render()
{
    for (_viLuke = _vLuke.begin(); _viLuke != _vLuke.end(); ++_viLuke)
    {
        RECT temp = (*_viLuke)->GetRect();
        (*_viLuke)->render();
    }
    for (_viMike = _vMike.begin(); _viMike != _vMike.end(); ++_viMike)
    {
        RECT temp = (*_viLuke)->GetRect();
        (*_viMike)->render();
    }
    for (_viMalcolm = _vMalcolm.begin(); _viMalcolm != _vMalcolm.end(); ++_viMalcolm)
    {
        RECT temp = (*_viMalcolm)->GetRect();
        (*_viMalcolm)->render();
    }

}

void EnemyManager::EnemyImageStorage()
{

}

void EnemyManager::SetLuke()
{
    for (int i = 0; i < 10; i++)
    {
        Enemy* luke;
        luke = new Luke;
        luke->SetCamera(_cm);
        luke->init("LUKE_IDLE", "LUKEleftIdle" , PointMake(800 * i + 800, 700));
        luke->SetPlayerLink(_player);
        _vLuke.push_back(luke);
    }
}

void EnemyManager::SetMike()
{
    for (int i = 0; i < 10; i++)
    {
        Enemy* mike;
        mike = new Mike;
        mike->SetCamera(_cm);
        mike->init("MIKE_IDLE", "MIKEleftIdle", PointMake(800 * i + 1000, 500));
        mike->SetPlayerLink(_player);
        _vLuke.push_back(mike);
    }
}

void EnemyManager::SetMalcolm()
{
    for (int i = 0; i < 10; i++)
    {
        Enemy* malcolm;
        malcolm = new Malcolm;
        malcolm->SetCamera(_cm);
        malcolm->init("MALCOLM_IDLE", "MALCOLMleftIdle", PointMake(800 * i + 1200, 900));
        malcolm->SetPlayerLink(_player);
        _vLuke.push_back(malcolm);
    }
}



