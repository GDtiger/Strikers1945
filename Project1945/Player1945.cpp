#include "Player1945.h"
#include "../Effect.h"

Player1945::Player1945() {}

Player1945::~Player1945() {}

HRESULT Player1945::init()
{
	_player = IMAGE->addImage("player", "images/player.bmp", WINSIZEX / 2, WINSIZEY - 200, 42, 80, true, RGB(255, 0, 255));
	//_player = IMAGE->addFrameImage("player", "images/player.bmp", 42, 80, 7, 1, true, RGB(255, 0, 255));
	rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY -200, _player->getWidth() - 30, _player->getHeight() - 40);




	_shot = new PlayerShot;
	_shot->init(50, WINSIZEY);
	_shot2 = new PlayerShot2;
	_shot2->init(50, WINSIZEY);
	_shot3 = new PlayerShot3;
	_shot3->init(50, WINSIZEY);
	_chageShot = new PlayerChageShot;
	_chageShot->init(1, WINSIZEY);
	//_nuclear = new PlayerNuclear;
	//_nuclear->init(1, 1000);

	_currentLevel = 1;
	_maxHp = _currentHp = 100;
	_hpBar = new progressBar;
	_hpBar->init("images/progressBarFront.bmp", "images/progressBarBack.bmp", 0, 0, 50, 10);
	//IMAGE->addFrameImage("bossDead", "images/bossExplosions.bmp", 4000, 200, 20, 1, true, RGB(255, 0, 255));

	_hpBar->setGauge(_currentHp, _maxHp);
	isAlive = true;
	return S_OK;

}

void Player1945::release()
{
	SAFE_DELETE(_shot);
	SAFE_DELETE(_shot2);
	SAFE_DELETE(_shot3);
	SAFE_DELETE(_chageShot);
	SAFE_DELETE(_hpBar);
}

void Player1945::update()
{
	if (isAlive) {
		if (InputManager->isStayKeyDown(VK_LEFT) && rc.left > 0) {
			OffsetRect(&rc, -5, 0);
		}
		if (InputManager->isStayKeyDown(VK_RIGHT) && rc.right < WINSIZEX) {
			OffsetRect(&rc, 5, 0);
		}
		if (InputManager->isStayKeyDown(VK_DOWN) && rc.bottom < WINSIZEY) {
			OffsetRect(&rc, 0, 5);
		}
		if (InputManager->isStayKeyDown(VK_UP) && rc.top > 0) {
			OffsetRect(&rc, 0, -5);
		}

		if (InputManager->isStayKeyDown(VK_SPACE))
		{
			burstTime++;

			if (_currentLevel == 1)
			{
				if ((int)burstTime % 7 == 0) {
					_shot->fire(rc.right - (rc.right - rc.left) / 2, rc.top - 50);
				}
			}
			else if (_currentLevel == 3) {
				if ((int)burstTime % 6 == 0) {
					_shot2->fire(rc.right - (rc.right - rc.left) / 2, rc.top - 50);
				}
			}
			else {
				if ((int)burstTime % 5 == 0) {
					_shot3->fire(rc.right - (rc.right - rc.left) / 2, rc.top - 50);
				}

			}
		}
		if (InputManager->isOnceKeyUp(VK_SPACE)) {
			if (burstTime < 40)burstTime = 0;
			else if (burstTime >= 40) {

				_chageShot->fire(rc.right - (rc.right - rc.left) / 2, rc.top - 50);
				burstTime = 0;
			}
		}

		if (InputManager->isOnceKeyDown('S'))
		{
			_currentLevel++;
		}
		if (InputManager->isOnceKeyDown('D'))
		{
			_currentLevel++;
		}
		if (InputManager->isOnceKeyDown('F'))
		{
			_currentHp = _maxHp;
		}
	}

	_shot->update();
	_shot2->update();
	_shot3->update();
	_chageShot->update();
	collision();

	_hpBar->setX(rc.left - 20);
	_hpBar->setY(rc.top - 30);
	_hpBar->setGauge(_currentHp, _maxHp);
	_hpBar->update();

	if (_currentHp < 1 && isAlive) {
		Effect* tempEffect = _um->CallEffect();
		tempEffect->init("playerDead", rc, 3, EffectType::one);
		isAlive = false;
	}

	if (_um->getBoss() != nullptr)
	{
		if (_um->getBoss()->HP <1) {
			Effect* tempEffect = _um->CallEffect();
			tempEffect->init("bossDead", _um->getBoss()->getRect(), 5, EffectType::one);

		}
	}
}

void Player1945::render()
{
	if (isAlive) {
		_player->render(getMemDC(), rc.left - 15, rc.top - 20);
	}
	//Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	_shot->render();
	_shot2->render();
	_shot3->render();
	_chageShot->render();
	_hpBar->render();
}

void Player1945::removeShot(int arrNum)
{
	_shot->removePlayerShot(arrNum);
	_shot2->removePlayerShot(arrNum);
	_shot3->removePlayerShot(arrNum);
	_chageShot->removePlayerChageShot(arrNum);
}

void Player1945::collision()
{
	isItem = RND->getInt(10);
	if (_um->getBoss() != nullptr)
	{
		for (int i = 0; i < _shot->getVBullet().size(); i++) {
			RECT rc;
			if (IntersectRect(&rc, &_shot->getVBullet()[i].rc, &_um->getBoss()->getRect())) {
				_shot->removePlayerShot(i);
				_um->getBoss()->HP -= 3;
				return;
			}
		}
		for (int i = 0; i < _shot2->getVBullet().size(); i++) {
			RECT rc;
			if (IntersectRect(&rc, &_shot2->getVBullet()[i].rc, &_um->getBoss()->getRect())) {
				_shot2->removePlayerShot(i);
				_um->getBoss()->HP -= 4;
				return;
			}
		}
		for (int i = 0; i < _shot3->getVBullet().size(); i++) {
			RECT rc;
			if (IntersectRect(&rc, &_shot3->getVBullet()[i].rc, &_um->getBoss()->getRect())) {
				_shot3->removePlayerShot(i);
				_um->getBoss()->HP -= 5;
				return;
			}
		}
		for (int i = 0; i < _chageShot->getVBullet().size(); i++) {
			RECT rc;
			if (IntersectRect(&rc, &_chageShot->getVBullet()[i].rc, &_um->getBoss()->getRect())) {
				_um->getBoss()->HP -= 1;
				return;
			}

		}
	}

	for (int j = 0;j < _um->getVMinion().size(); j++) {
		for (int i = 0; i < _shot->getVBullet().size(); i++) {
			RECT rc;
			if (IntersectRect(&rc, &_shot->getVBullet()[i].rc, &_um->getVMinion()[j]->getRect())) {
				_um->countVec[(int)_um->getVMinion()[j]->enemyType]--;
				Effect* tempEffect = _um->CallEffect();
				tempEffect->init("enemyDead", _um->getVMinion()[j]->getRect(), 3, EffectType::one);
				_shot->removePlayerShot(i);
				if (isItem == 0) {
					_um->setItem(_um->getVMinion()[j]->getRect().left, _um->getVMinion()[j]->getRect().top);
				}
				_um->removeMinion(j);
				return;
			}
		}

		for (int i = 0; i < _shot2->getVBullet().size(); i++) {
			RECT rc;
			if (IntersectRect(&rc, &_shot2->getVBullet()[i].rc, &_um->getVMinion()[j]->getRect())) {
				_um->countVec[(int)_um->getVMinion()[j]->enemyType]--;
				Effect* tempEffect = _um->CallEffect();
				tempEffect->init("enemyDead", _um->getVMinion()[j]->getRect(), 3, EffectType::one);
				_shot2->removePlayerShot(i);
				if (isItem == 0) {
					_um->setItem(_um->getVMinion()[j]->getRect().left, _um->getVMinion()[j]->getRect().top);
				}
				_um->removeMinion(j);
				return;
			}
		}
		for (int i = 0; i < _shot3->getVBullet().size(); i++) {
			RECT rc;
			if (IntersectRect(&rc, &_shot3->getVBullet()[i].rc, &_um->getVMinion()[j]->getRect())) {
				_um->countVec[(int)_um->getVMinion()[j]->enemyType]--;
				Effect* tempEffect = _um->CallEffect();
				tempEffect->init("enemyDead", _um->getVMinion()[j]->getRect(), 3, EffectType::one);
				_shot3->removePlayerShot(i);
				if (isItem == 0) {
					_um->setItem(_um->getVMinion()[j]->getRect().left, _um->getVMinion()[j]->getRect().top);
				}
				_um->removeMinion(j);
				return;
			}
		}

		for (int i = 0; i < _chageShot->getVBullet().size(); i++) {
			RECT rc;
			if (IntersectRect(&rc, &_chageShot->getVBullet()[i].rc, &_um->getVMinion()[j]->getRect()))
			{
				Effect* tempEffect = _um->CallEffect();
				tempEffect->init("enemyDead", _um->getVMinion()[j]->getRect(), 3, EffectType::one);
				_um->countVec[(int)_um->getVMinion()[j]->enemyType]--;
				//_chageShot->removePlayerChageShot(i);
				if (isItem == 0) {
					_um->setItem(_um->getVMinion()[j]->getRect().left, _um->getVMinion()[j]->getRect().top);
				}
				_um->removeMinion(j);
				break;
			}
		}

		for (int j = 0;j < _um->getVItem().size(); j++) {
			for (int i = 0; i < _um->getVItem().size(); i++) {
				RECT rc1;
				if (IntersectRect(&rc1, &rc, &_um->getVItem()[j]->getRect()))
				{
					getItem();
					_um->removeItem(j);
					break;
				}
			}
		}
	}
}

void Player1945::hitDamage(float damage)
{
	_currentHp -= damage;
}
