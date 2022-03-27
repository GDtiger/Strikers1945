#pragma once
#include "../framework.h"
#include "../gameNode.h"
#include "../progressBar.h"
#include "Bullet1945.h"
#include "UnitManager.h"


class UnitManager;
class Player1945 : public gameNode
{
private:
	image* _player;

	PlayerShot* _shot;
	PlayerShot2* _shot2;
	PlayerShot3* _shot3;
	PlayerChageShot* _chageShot;
	Bullet1945* _bullet;
	RECT rc;


	//피통
	progressBar* _hpBar;
	float _maxHp;
	float _currentHp;
	int _currentFrameX, _currentFrameY;
	UnitManager* _um;

	int isItem;
	int _currentLevel;
	float burstTime;
	bool isAlive;
public:

	Player1945();
	~Player1945();

	HRESULT init();
	void release();
	void update();
	void render();

	//총알 삭제
	void removeShot(int arrNum);
	//충돌함수
	void collision();
	//피깎는 함수
	void hitDamage(float damage);

	//총알  가져오기
	PlayerShot* getPlayerShot() { return _shot; }
	//플레이어 이미지 가져오기
	image* getPlayerImage() { return _player; }

	bool getAlive() { return isAlive; }
	bool getItem() { return _currentLevel+=1; }
	void setEnemyMemoryLink(UnitManager* um) { _um = um; }

	RECT getRect() { return rc; }
};

