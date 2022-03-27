#include "BulletBoss.h"

//TODO:: ÇÃ·¹ÀÌ¾î Â÷Áö¼¦
BulletBoss::BulletBoss() {}
BulletBoss::~BulletBoss() {}

HRESULT BulletBoss::init(int bulletMax, float range)
{
	_chageShotMax = bulletMax;
	_range = range;

	return S_OK;
}

void BulletBoss::release()
{
}

void BulletBoss::update()
{
	move();
}

void BulletBoss::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;

		if (_viBullet->count % 4 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);//ÃÑ¾Ë ÀÌ¹ÌÁö ¸ØÃß´Â°÷
			}
			_viBullet->count = 10;
		}
	}
}

void BulletBoss::fire(float x, float y)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage->init("images/missile1.bmp", 0, 0, 416, 64, 13, 1, true, RGB(255, 0, 255));
	bullet.speed = 6.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	//bullet.size = 1;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());
	_vBullet.push_back(bullet);
}

void BulletBoss::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(), _viBullet->bulletImage->getFrameHeight());


		if (_range < UTIL::getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void BulletBoss::removePlayerChageShot(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}