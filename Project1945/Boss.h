#include "../framework.h"
#include "Enemy.h"
#pragma once
class UnitManager;
class Boss : public Enemy
{
private:
	int _bossCount[3];
	int _bossfireCount[3];
	UnitManager* _um;

public:
	Boss();
	~Boss();

	bool isAlive;
	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, RECT rectangle/* POINT position*/);
	virtual void release();
	virtual void update();
	virtual void render();


	virtual  void draw();
	virtual  void animation();
	float HP;

	virtual bool bulletCountFire1();
	virtual bool bulletCountFire2();
	virtual bool bulletCountFire3();
	virtual RECT getRect() { return _rc; }
	bool getAlive() { return isAlive; }
};

