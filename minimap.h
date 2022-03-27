#pragma once
#include"gameNode.h"
#define PLAYERSPEED 5
#define CAMERASPEED 5
class minimap:public gameNode
{

private:

	image* m_rockman;
	int m_index;
	int m_count;
	int m_camera;
	bool isLeft;

	RECT mini_rc;

public:
	minimap();
	~minimap();
	HRESULT init();
	void release();
	void update();
	void render();
};

