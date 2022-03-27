#include "Bullet1945.h"

Bullet1945::Bullet1945() {}
Bullet1945::~Bullet1945() {}

HRESULT Bullet1945::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;



	return S_OK;
}

void Bullet1945::release()
{

}

void Bullet1945::update()
{
	move();
}

void Bullet1945::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end();++_viBullet)
	{
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void Bullet1945::fire(float x, float y, float angle, float speed)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage = IMAGE->findImage(_imageName);
	bullet.angle = angle;
	bullet.speed = speed;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.bulletImage->getWidth(), bullet.bulletImage->getHeight());
	_vBullet.push_back(bullet);
}

void Bullet1945::move()
{
	for (_viBullet = _vBullet.begin();_viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->bulletImage->getWidth(), _viBullet->bulletImage->getHeight());
		if (_range < UTIL::getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY)) {
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void Bullet1945::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

//TODO:: 플레이어 샷
PlayerShot::PlayerShot() {}
PlayerShot::~PlayerShot() {}

HRESULT PlayerShot::init(int bulletMax, float range)
{
	_shotMax = bulletMax;
	_range = range;

	return S_OK;
}

void PlayerShot::release()
{
}

void PlayerShot::update()
{
	move();
}

void PlayerShot::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;

		if (_viBullet->count % 10 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);


			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void PlayerShot::fire(float x, float y)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage->init("images/playerAttack-1.bmp", 0, 0, 108, 56, 6, 1, true, RGB(255, 0, 255));
	bullet.speed = 15.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth() - 20,
		bullet.bulletImage->getFrameHeight() - 20);
	_vBullet.push_back(bullet);
}

void PlayerShot::move()
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

void PlayerShot::removePlayerShot(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

PlayerShot2::PlayerShot2(){}

PlayerShot2::~PlayerShot2(){}

HRESULT PlayerShot2::init(int bulletMax, float range)
{
	_shotMax = bulletMax;
	_range = range;

	return S_OK;
}

void PlayerShot2::release()
{
}

void PlayerShot2::update()
{
	move();

}

void PlayerShot2::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;

		if (_viBullet->count % 10 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);


			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void PlayerShot2::fire(float x, float y)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage->init("images/playerAttack-2.bmp", 0, 0, 228, 71, 6, 1, true, RGB(255, 0, 255));
	bullet.speed = 16.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth() - 20,
		bullet.bulletImage->getFrameHeight() - 20);
	_vBullet.push_back(bullet);
}

void PlayerShot2::move()
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

void PlayerShot2::removePlayerShot(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);

}

PlayerShot3::PlayerShot3(){}

PlayerShot3::~PlayerShot3(){}

HRESULT PlayerShot3::init(int bulletMax, float range)
{
	_shotMax = bulletMax;
	_range = range;

	return S_OK;
}

void PlayerShot3::release()
{
}

void PlayerShot3::update()
{
	move();

}

void PlayerShot3::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;

		if (_viBullet->count % 10 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);


			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void PlayerShot3::fire(float x, float y)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage->init("images/playerAttack-3.bmp", 0, 0, 360, 114, 6, 1, true, RGB(255, 0, 255));
	bullet.speed = 17.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth() - 20,
		bullet.bulletImage->getFrameHeight() - 20);
	_vBullet.push_back(bullet);
}

void PlayerShot3::move()
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

void PlayerShot3::removePlayerShot(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);

}


//TODO:: 플레이어 차지샷
PlayerChageShot::PlayerChageShot() {}
PlayerChageShot::~PlayerChageShot() {}

HRESULT PlayerChageShot::init(int bulletMax, float range)
{
	_chageShotMax = bulletMax;
	_range = range;
	return S_OK;
}

void PlayerChageShot::release()
{
}


void PlayerChageShot::update()
{
	move();
}

void PlayerChageShot::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		/*_viBullet->bulletImage->frameRender(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0);*/
		_viBullet->bulletImage->frameRender(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0 /*_viBullet->size*/);
		//_viBullet->size += 0.01;
		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);

			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(8);
			}
			_viBullet->count = 0;
		}
	}
}

void PlayerChageShot::fire(float x, float y)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage->init("images/ulti2.bmp", 0, 0, 1380, 245, 8, 1, true, RGB(255, 0, 255));
	bullet.speed = 12.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());
	_vBullet.push_back(bullet);
}

void PlayerChageShot::move()
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

void PlayerChageShot::removePlayerChageShot(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

