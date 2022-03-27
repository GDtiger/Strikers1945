#pragma once
#include "../framework.h"
#include "Enemy.h"

class Item1945 : public Enemy
{
public:
	Item1945() {}
	~Item1945() {}
	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, RECT rectangle);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void draw();
	virtual void animation();
	virtual RECT getRect() { return _rc; }
};

