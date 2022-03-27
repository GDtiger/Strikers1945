#include "../framework.h"
#include "Enemy.h"
#pragma once
class Enemy1945_2 : public Enemy
{
private:
	int _pattern;
public:
	Enemy1945_2();
	~Enemy1945_2();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, RECT rectangle, int pattern);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual  void draw();
	virtual  void animation();
	virtual bool bulletCountFire();
	virtual RECT getRect() { return _rc; }

};

