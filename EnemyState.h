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

class EnemyIdle : public EnemyState
{
private:

public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;

	virtual void SetEnemy(Enemy* enemy) override { _enemy = enemy; }
};

class EnemyWalk : public EnemyState
{
private:
	int _count;
public:
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;

	virtual void SetEnemy(Enemy* enemy) override { _enemy = enemy; }
};

class EnemyRun : public EnemyState
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
