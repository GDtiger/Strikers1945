#include "Effect.h"
#include "framework.h"
#include "image.h"
#include "Project1945/UnitManager.h"
Effect::Effect(int id , UnitManager* um)
{
	instanceId = id;
	_UM = um;
	isDeactive = true;
}

Effect::~Effect()
{

}



HRESULT Effect::init(const char* imageName, RECT rectangle, int speed, EffectType _effectType)
{
	isDeactive = false;
	effectType = _effectType;
	_count = 0;
	_currentFrameX = 0;
	_currentFrameY = 0;
	animationSpeed = speed;


	_image = IMAGE->findImage(imageName);
	_rc = RectMakeCenter(rectangle.left + (rectangle.right - rectangle.left) / 2, rectangle.top + (rectangle.bottom - rectangle.top) / 2, _image->getFrameWidth(), _image->getFrameHeight());
    return S_OK;
}

void Effect::release()
{
}



void Effect::update()
{
	if (isDeactive) return;
	//if (_rc.bottom <= 300) OffsetRect(&_rc, 0, 2);
	animation();
}

void Effect::render(HDC hdc)
{
	if (isDeactive) return;
	_image->frameRender(hdc, _rc.left, _rc.top, _currentFrameX, _currentFrameY);

}



void Effect::animation()
{
	_count++;
	if (_count % animationSpeed == 0) {
		_image->setFrameX(_image->getFrameX() + 1);
		_currentFrameX++;

		if (_currentFrameX >= _image->getMaxFrameX()) {
			//_currentFrameX = 0;
			_UM->ReturnEffect(this);
		}
	}
}