#include "Item1945.h"

HRESULT Item1945::init()
{
    return S_OK;
}

HRESULT Item1945::init(const char* imageName, RECT rectangle)
{
    _count = 0;
    _currentFrameX = 5;
    _currentFrameY = 0;
    _image = IMAGE->findImage(imageName);
    _rc = RectMakeCenter(rectangle.left, rectangle.top, _image->getFrameWidth(), _image->getFrameHeight());
    x = 100;
    y = 100;
    return S_OK;
}

void Item1945::release()
{
}

void Item1945::update()
{
    OffsetRect(&_rc, 0, 2);
    animation();
}

void Item1945::render()
{
    draw();
}

void Item1945::draw()
{
    _image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);

}

void Item1945::animation()
{
    _count++;
    if (_count % 5 == 0) {
        _image->setFrameX(_image->getFrameX() + 1);
        _currentFrameX++;

        if (_currentFrameX >= _image->getMaxFrameX()) {
            _currentFrameX = 0;
        }
    }
}
