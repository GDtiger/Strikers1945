#include "Enemy1945_2.h"
#include "UnitManager.h"

Enemy1945_2::Enemy1945_2()
{
}

Enemy1945_2::~Enemy1945_2()
{
}

HRESULT Enemy1945_2::init()
{
	return S_OK;
}
//TODO::¾î¶²³ðµéÀÌ ½òÁö
HRESULT Enemy1945_2::init(const char* imageName, RECT rectangle, int pattern)
{
	enemyType = EnemyType::type2;
	_count = 0;
	_currentFrameX = 0;
	_currentFrameY = 0;
	_pattern = pattern;
	_fireCount = 0;
	_rndfireCount = RND->getFromIntTo(1, 500);

	_image = IMAGE->findImage(imageName);
	_rc = RectMakeCenter(rectangle.left, rectangle.top, _image->getFrameWidth(), _image->getFrameHeight());
	return S_OK;
}

void Enemy1945_2::release()
{
}
//TODO::¿¡³Ê¹Ì ¿òÁ÷ÀÌ´Â°÷
void Enemy1945_2::update()
{
	switch (_pattern)
	{
	case 1:
			OffsetRect(&_rc, -2, 2);
		break;
	case 2:
			OffsetRect(&_rc, 2, 2);
		break;
	default:
		break;
	}
	animation();
}

void Enemy1945_2::render()
{
	draw();
}

void Enemy1945_2::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void Enemy1945_2::animation()
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
bool Enemy1945_2::bulletCountFire()
{
	_fireCount++;
	if (_rc.top >= 0 && _rc.right <= WINSIZEX&&_rc.left >=0) {
		if (_fireCount % _rndfireCount == 0) {
			_rndfireCount = 100; /*RND->getFromIntTo(1, 1000);*/
			_fireCount = 0;
			return true;
		}
	}
	return false;
}
