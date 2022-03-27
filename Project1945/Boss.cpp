#include "Boss.h"
#include "../Effect.h"
#include "UnitManager.h"

Boss::Boss()
{
	HP = 1000;
}

Boss::~Boss()
{
}

HRESULT Boss::init()
{
	return S_OK;
}

HRESULT Boss::init(const char* imageName, RECT rectangle)
{
	enemyType = EnemyType::Boss; 
	_count = 0;
	_currentFrameX = 0;
	_currentFrameY = 0;

	_bossCount[0] = 0;
	_bossCount[1] = 0;
	_bossCount[2] = 0;
	_bossfireCount[0] = 1;
	_bossfireCount[1] = 1;
	_bossfireCount[2] = 1;
	
	isAlive = true;
	_currentFrameX = 4;
	_image = IMAGE->findImage(imageName);
	_rc = RectMakeCenter(rectangle.left, rectangle.top, _image->getFrameWidth()-20, _image->getFrameHeight()-200);
	return S_OK;
}

void Boss::release()
{
}

void Boss::update()
{
	if (_rc.bottom <= 150) OffsetRect(&_rc, 0, 2);
	if (HP < 0) {
		isAlive = false;
		_rc = RectMake(-100, -100, -100, -100);
	}

	animation();



}

void Boss::render()
{
	draw();
}

void Boss::draw()
{

	if (isAlive) {
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}


}

void Boss::animation()
{
	if (HP > 800)
	{
		_currentFrameX = 4;
	}
	else if (HP > 600)
	{
		_currentFrameX = 2;
	}
	else if (HP > 300)
	{
		_currentFrameX = 1;
	}
	else if (HP > 100)
	{
		_currentFrameX = 0;
	}
	else if (HP < 0) {
	}
}

bool Boss::bulletCountFire1()
{
	_bossCount[0]++;
	if (_rc.top >= 0) {
		if (_bossCount[0] % _bossfireCount[0] == 0) {
			_bossfireCount[0] = 50; /*RND->getFromIntTo(1, 1000);*/
			_bossCount[0] = 0;
			return true;
		}
	}
	return false;
}

bool Boss::bulletCountFire2()
{
	_bossCount[1]++;
	if (_rc.top >= 0) {
		if (_bossCount[1] % _bossfireCount[1] == 0) {
			_bossfireCount[1] = 5; /*RND->getFromIntTo(1, 1000);*/
			_bossCount[1] = 0;
			return true;
		}
	}
	return false;
}

bool Boss::bulletCountFire3()
{
	_bossCount[2]++;
	if (_rc.top >= 0) {
		if (_bossCount[2] % _bossfireCount[2] == 0) {
			_bossfireCount[2] = 10; /*RND->getFromIntTo(1, 1000);*/
			_bossCount[2] = 0;
			return true;
		}
	}
	return false;
}
