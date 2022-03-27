#pragma once
#include "../framework.h"
#include "../gameNode.h"
#include "Bullet1945.h"
class BulletBoss : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float maxSpeed = 0;


	int _chageShotMax;
	float _range;
public:
	BulletBoss();
	~BulletBoss();

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y);
	void move();

	void removePlayerChageShot(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

};