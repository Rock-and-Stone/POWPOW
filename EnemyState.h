#pragma once

class Enemy;

class EnemyState
{
protected:
	Enemy* _enemy;
public:
	EnemyState();
	~EnemyState();

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void SetEnemy(Enemy* enemy) = 0;
};

class EnemyInit : public EnemyState
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;

	virtual void SetEnemy(Enemy* enemy) override { _enemy = enemy; }
};


class EnemyIdle : public EnemyState
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;

	virtual void SetEnemy(Enemy* enemy) override { _enemy = enemy; }
};

class EnemyWander : public EnemyState
{
private:
	int rndX;
	int rndY;
public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;

	virtual void SetEnemy(Enemy* enemy) override { _enemy = enemy; }
};

class EnemyChase : public EnemyState
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;

	virtual void SetEnemy(Enemy* enemy) override { _enemy = enemy; }
};

class EnemyJump : public EnemyState
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;

	virtual void SetEnemy(Enemy* enemy) override { _enemy = enemy; }
};

class EnemyFall : public EnemyState
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;

	virtual void SetEnemy(Enemy* enemy) override { _enemy = enemy; }
};

class EnemyAttack : public EnemyState
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;

	virtual void SetEnemy(Enemy* enemy) override { _enemy = enemy; }
};


class EnemyDamaged : public EnemyState
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;

	virtual void SetEnemy(Enemy* enemy) override { _enemy = enemy; }
};

class EnemyDown : public EnemyState
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;

	virtual void SetEnemy(Enemy* enemy) override { _enemy = enemy; }
};

class EnemyGetUp : public EnemyState
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;

	virtual void SetEnemy(Enemy* enemy) override { _enemy = enemy; }
};



class EnemyGuard : public EnemyState
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;

	virtual void SetEnemy(Enemy* enemy) override { _enemy = enemy; }
};
