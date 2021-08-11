#pragma once

class gameData
{
private:
	int _BGMVolume;
	int _SFXVolume;

	int _playerHP = getPlayerSaveHP();
	int _playerGP = getPlayerSaveGP();
	int _coin = getSaveCoin();

public:
	float getBGMVolume();
	void setBGMVolume(float volume);

	float getSFXVolume();
	void setSFXVolume(float volume);

	int getPlayerSaveHP();
	void SavePlayerHP(int hp);

	int getPlayerSaveGP();
	void SavePlayerGP(int gp);

	int getSaveCoin();
	void SaveCoin(int coin);

	int getPlayerHP() { return _playerHP; }
	void setPlayerHP(int hp) { _playerHP = hp; }

	int getPlayerGP() { return _playerGP; }
	void setPlayerGP(int gp) { _playerGP = gp; }

	int getCoin() { return _coin; }
	void setCoin(int coin) { _coin = coin; }

	void SaveData() { SavePlayerGP(_playerGP); SavePlayerHP(_playerHP); SaveCoin(_coin); }
};

