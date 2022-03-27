#pragma once
#include"gameNode.h"
#include "Project1945/UIManager.h"
#include "Project1945/UnitManager.h"
#include "Project1945/Player1945.h"
class mainGame : public gameNode
{
private:
	
	image* _screen;
	Player1945* _player;
	UnitManager* _unitManager;

	int screenCount;
	float m_loopX;
	float m_loopY;
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);


	
	
};

