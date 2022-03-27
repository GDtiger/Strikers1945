#include"framework.h"
#include "mainGame.h"
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init(true);
	IMAGE->addImage("배경화면", "images/backGround.bmp", WINSIZEX, 4288, true, RGB(255, 0, 255));
	//IMAGE->addImage("bullet", "images/bullet.bmp", 21 * 0.4, 21 * 0.4, true, RGB(255, 0, 255));
	//IMAGE->addImage("bullet", "images/enemyBullet.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGE->addImage("bullet", "images/enemyJuneBossBullet.bmp", 16 * 0.5, 16 * 0.5, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("enemyDead", "images/deathExplosions.bmp", 800, 94, 12, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("bossDead", "images/bossExplosions.bmp", 4000, 200, 20, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("playerDead", "images/playerBomb.bmp", 3584, 320, 16, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("LevelUp", "images/attackItem.bmp", 260, 30, 6, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("에너미1", "images/enemy.bmp", 78, 64, 1, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("에너미2", "images/enemy1.bmp", 50, 70, 1, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("에너미3", "images/enemy5.bmp", 19, 32, 1, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("보스", "images/boss1.bmp", 2000, 263, 5, 1, true, RGB(255, 0, 255));
	_player = new Player1945;
	_player->init();
	_unitManager = new UnitManager;
	_unitManager->init();
	_screen = IMAGE->addImage("screen", "images/blackScreen.bmp", WINSIZEX, WINSIZEY, false, 0);


	_player->setEnemyMemoryLink(_unitManager);
	_unitManager->setRocketMemoryLink(_player);
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	SAFE_DELETE(_player);
	SAFE_DELETE(_unitManager);
}

void mainGame::update()
{

	gameNode::update();
	_player->update();
	_unitManager->update();
	//m_loopX -= 0.5;
	m_loopY -= 1;

}

void mainGame::render(/*HDC hdc*/)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================
	//if (!_player->getAlive()) {
	//	IMAGE->deleteImage("player");
	//}
	IMAGE->loopRender("배경화면", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), m_loopX, m_loopY);
	_player->render();
	_unitManager->render();
	_unitManager->renderEffect(getMemDC());
	if (!_player->getAlive()) {
		if (screenCount < 254) {
			screenCount++;
			_screen->alphaRender(getMemDC(), screenCount);
		}
		else {
			_screen->render(getMemDC());
		}
	}
	//==============================================
	TIME->render(getMemDC());
	//백버퍼의 내용을 HDC그린다.(건드리지 말것.)
	this->getBackBuffer()->render(getHDC(), 0, 0);


}

 