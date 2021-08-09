#pragma once
#define PLAYERHPMAX 150
#define PLAYERGPMAX 150

class gameData
{
private:
	float _BGMVolume = 0.0f;
	float _SFXVolume = 0.5f;

	int _playerHP = PLAYERHPMAX;
	int _playerGP = PLAYERGPMAX;
	int _coin = 0;

public:
	float getBGMVolume() { return _BGMVolume; }
	void setBGMVolutme(float volume) { _BGMVolume = volume; }

	float getSFXVolume() { return _SFXVolume; }
	void setSFXVolume(float volume) { _SFXVolume = volume; }

	int getPlayerHP() { return _playerHP; }
	void setPlayerHP(int hp) { _playerHP = hp; }

	int getPlayerGP() { return _playerGP; }
	void setPlayerGP(int gp) { _playerGP = gp; }

	int getCoin() { return _coin; }
	void setCoin(int coin) { _coin = coin; }
};

