#pragma once
#include "../gameNode.h"
#include "Bullet1945.h"
#include "Enemy1945.h"
#include "Enemy.h"
#include "Enemy1945_2.h"
#include "Enemy1945_3.h"
#include "Boss.h"
#include "Item1945.h"
#include "../singleton.h"
class Player1945;
class UnitManager:public gameNode
{
private:
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

	typedef vector<Item1945*> vItem;
	typedef vector<Item1945*>::iterator viItem;

	Enemy1945* enemy1;
	Enemy1945_2* enemy2;
	Enemy1945_3* enemy3;

	Item1945* item;

	Boss* boss;

	int instanceId;
	vector<class Effect*> effectVec;
	vector<class Effect*> effectHolder;
	vector<int> effectErase;

	Player1945* _player;
	float angle;
	int coolTime[8];
	bool go;

	bool wave1;
	bool wave2;
	bool wave3;

	int pos;
	
private:
	vEnemy			_vMinion;
	viEnemy			_viMinion;

	vItem			_vItem;
	viItem			_viItem;

	Bullet1945* _bullet;
public:
	vector<int> countVec;

	UnitManager();
	~UnitManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void renderEffect(HDC hdc);


	void setMinion1(int setenemy, int x, int y, int distanceX, int distanceY, int pattern);
	void setMinion2(int setenemy, int x, int y, int distanceX, int distanceY, int pattern);
	void setMinion3(int setenemy, int x, int y, int distanceX, int distanceY, int pattern);
	void setItem(int x, int y);
	void setBoss();
	Boss* getBoss() { return boss; };
	void minionBulletFire();
	void bossBulletFire1();
	void bossBulletFire2();
	void bossBulletFire3();

	class Effect* CallEffect();
	void ReturnEffect(class Effect* effect);

	vEnemy			getVMinion() { return _vMinion; }
	viEnemy			getViMinion() { return _viMinion; }

	vItem			getVItem() { return _vItem; }
	viItem			getViItem() { return _viItem; }

	void removeMinion(int arrNum);
	void removeItem(int arrNum);
	void removeBoss(int arrNum);

	void collision();

	void setRocketMemoryLink(Player1945* player) { _player = player; }
	bool isBoss();
};

