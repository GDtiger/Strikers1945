#pragma once



#include "framework.h"
class Effect 
{
protected:
	RECT _rc;

	bool isDeactive;

	int instanceId;

	class image* _image;
	int _currentFrameX;
	int _currentFrameY;
	int _count;
	int animationSpeed;
	float speedX, speedY;
	float x, y;
	bool move1;

	EffectType effectType;
public:
	class UnitManager* _UM;

	Effect(int id, class UnitManager* um);
	~Effect();

	int getId() { return instanceId; }
	virtual HRESULT init(const char* imageName,  RECT rectangle, int speed, EffectType effectType);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void animation();
	virtual RECT getRect() { return _rc; }
};

