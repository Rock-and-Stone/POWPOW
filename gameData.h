#pragma once
class gameData
{
private:
	float _BGMVolume = 0.5f;
	float _SFXVolume = 0.5f;
public:
	float getBGMVolume() { return _BGMVolume; }
	void setBGMVolutme(float volume) { _BGMVolume = volume; }

	float getSFXVolume() { return _SFXVolume; }
	void setSFXVolume(float volume) { _SFXVolume = volume; }
};

