#include "UnitManager.h"
#include "Enemy1945.h"


Enemy1945::Enemy1945(){}

Enemy1945::~Enemy1945(){}

HRESULT Enemy1945::init()
{
	return S_OK;
}
//TODO::¾î¶²³ðµéÀÌ ½òÁö
HRESULT Enemy1945::init(const char* imageName, RECT rectangle, int pattern/* POINT position*/)
{
	enemyType = EnemyType::type1;
	_count = 0;
	_currentFrameX = 0;
	_currentFrameY = 0;
	_pattern = pattern;
	_fireCount = 0;
	_rndfireCount =1 /*RND->getFromIntTo(1, 1000)*/;

	_image = IMAGE->findImage(imageName);
	_rc = RectMakeCenter(rectangle.left, rectangle.top, _image->getFrameWidth(), _image->getFrameHeight());
	return S_OK;
}

void Enemy1945::release()
{
}
//TODO::¿¡³Ê¹Ì ¿òÁ÷ÀÌ´Â°÷
void Enemy1945::update()
{
	switch (_pattern)
	{
	case 1:

	 OffsetRect(&_rc, 0, 2);
		break;
	case 2:
		 OffsetRect(&_rc, 0, 5);
		break;
	case 3:
		OffsetRect(&_rc, 1, 5);
		break;
	default:
		break;
	}
	animation();
}

void Enemy1945::render()
{
	draw();
}

void Enemy1945::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void Enemy1945::animation()
{
	_count++;
	if (_count % 3 == 0) {
		_image->setFrameX(_image->getFrameX() + 1);
		_currentFrameX++;

		if (_currentFrameX >= _image->getMaxFrameX()) {
			_currentFrameX = 0;
		}
	}
}
//TODO::ÃÑ¾Ë ½î´Â ÁÖ±â
bool Enemy1945::bulletCountFire()
{
	_fireCount++;
	if (_rc.top >= 0) 
	{
		if (_fireCount % _rndfireCount == 0) 
		{
			_rndfireCount = 100; /*RND->getFromIntTo(1, 1000);*/
			_fireCount = 0;
			return true;
		}
	}
	return false;
}
