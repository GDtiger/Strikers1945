#include "../gameNode.h"
#pragma once

class Enemy : public gameNode
{
protected:
	image* _image;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;
	int _count;

	float speedX, speedY;
	float x, y;
	bool move1;
	int _fireCount;
	int _rndfireCount;
public:


		EnemyType enemyType;

	Enemy();
	~Enemy();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, RECT rectangle/* POINT position*/);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void draw();
	virtual void animation();
	virtual bool bulletCountFire();
	virtual RECT getRect() { return _rc; }
};

