#pragma once

#define LEFTKEYDOWN KEYMANAGER->isOnceKeyDown(VK_LEFT)
#define RIGHTKEYDOWN KEYMANAGER->isOnceKeyDown(VK_RIGHT)
#define UPKEYDOWN KEYMANAGER->isOnceKeyDown(VK_UP)
#define DOWNKEYDOWN KEYMANAGER->isOnceKeyDown(VK_DOWN)

#define LEFTKEYUP KEYMANAGER->isOnceKeyUp(VK_LEFT)
#define RIGHTKEYUP KEYMANAGER->isOnceKeyUp(VK_RIGHT)
#define UPKEYUP KEYMANAGER->isOnceKeyUp(VK_UP)
#define DOWNKEYUP KEYMANAGER->isOnceKeyUp(VK_DOWN)


class player;

class State
{
protected:
	player* _player;
public:
	State();
	~State();

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render(HDC hdc) = 0;
	virtual void setPlayer(player* player) = 0;
};

class Idle : public State
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;
	virtual void Input();
	virtual void Trigger();

	virtual void setPlayer(player* player) override { _player = player; }
};

class Walk : public State
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;
	virtual void Input();
	virtual void Trigger();

	virtual void setPlayer(player* player) override { _player = player; }
};


class Jump : public State
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;
	virtual void Input();
	virtual void Trigger();

	virtual void setPlayer(player* player) override { _player = player; }
};

class Fall : public State
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;
	virtual void Input();
	virtual void Trigger();

	virtual void setPlayer(player* player) override { _player = player; }
};