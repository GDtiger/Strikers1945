#include "../framework.h"
#include "UnitManager.h"
#include "Player1945.h"
#include "../Effect.h"
UnitManager::UnitManager() {
	boss = nullptr;
}
UnitManager::~UnitManager() {}

HRESULT UnitManager::init()
{
	_bullet = new Bullet1945;
	_bullet->init("bullet", 10, 700);
	wave1 = true;
	wave2 = true;
	countVec.push_back(0);
	countVec.push_back(0);
	return S_OK;
}

void UnitManager::release()
{
	SAFE_DELETE(_bullet);
}

void UnitManager::update()
{
	if ((int)TIME->getWorldTime() == 1) {
		setBoss();
		wave1 = false;
		wave2 = false;
	}
	if (countVec[(int)EnemyType::type1] < 1) {
		if ((int)TIME->getWorldTime() % 4 == 3) {
			if (wave1) {
				setMinion1(5, 100, 0, 100, 0, 2);
				wave1 = false;
			}
		}
	}
	else wave1 = true;

	if (countVec[(int)EnemyType::type2] < 2) {
		if ((int)TIME->getWorldTime() % 5 == 4) {
			if (wave2) {
				pos = RND->getInt(2);
				switch (pos)
				{
				case 0:
					setMinion2(5, WINSIZEX, 0, 100, -100, 1);
					break;
				case 1:
					setMinion2(5, 0, 0, -100, -100, 2);
					break;

				default:
					break;
				}
				wave2 = false;
			}
		}
	}
	else wave2 = true;

	if (InputManager->isOnceKeyDown('A')) {
		setItem(WINSIZEX/2, 100);
	}


	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}

	_viItem = _vItem.begin();
	for (_viItem;_viItem != _vItem.end();++_viItem)
	{
		(*_viItem)->update();

	}
	//총알
	_bullet->update();
	collision();

	if (boss != nullptr)
	{
		boss->update();
	}

	coolTime[0]++;
	coolTime[1]++;

	if (coolTime[0] % 401 <= 100) {
		this->bossBulletFire2();
	}

	//if (coolTime[1] % 300 <= 50) {
	//	this->bossBulletFire3();
	//}

	for (size_t i = 0; i < effectVec.size(); i++)
	{
		effectVec[i]->update();
	}

	for (size_t i = 0; i < effectErase.size(); i++)
	{
		for (size_t j = 0; j < effectVec.size(); j++)
		{

			if (effectErase[i] == effectVec[j]->getId())
			{
				effectHolder.push_back(effectVec[j]);
				effectVec.erase(effectVec.begin() + j);
				break;
			}
		}
	}

	effectErase.clear();

	this->minionBulletFire();
	this->bossBulletFire1();
}

void UnitManager::render()
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	_viItem = _vItem.begin();
	for (_viItem;_viItem != _vItem.end();++_viItem)
	{
		(*_viItem)->render();
	}

	_bullet->render();

	if (boss != nullptr)
	{
		boss->render();
	}
}

Effect* UnitManager::CallEffect() {

	if (effectHolder.size() > 0)
	{
		Effect* effect = effectHolder.back();
		effectHolder.pop_back();
		effectVec.push_back(effect);
		return effect;
	}
	else {
		Effect* effect = new Effect(instanceId++, this);
		effectVec.push_back(effect);
		return effect;
	}
}

void UnitManager::ReturnEffect(Effect* effect) {

	effectErase.push_back(effect->getId());
}

void UnitManager::renderEffect(HDC hdc)
{
	for (size_t i = 0; i < effectVec.size(); i++)
	{
		effectVec[i]->render(hdc);
	}
}
//TODO::에너미 수 설정
void UnitManager::setMinion1(int setenemy, int x, int y, int distanceX, int distanceY, int pattern)
{
	for (int i = 0; i < setenemy; i++)
	{
		Enemy1945* enemy1;
		enemy1 = new Enemy1945;
		enemy1->init("에너미1", RectMakeCenter(x + enemy1->getRect().left + i * distanceX,
			y + enemy1->getRect().top + (i * distanceY),
			enemy1->getRect().right, enemy1->getRect().bottom), pattern);
		countVec[(int)EnemyType::type1]++;
		_vMinion.push_back(enemy1);
	}
}

void UnitManager::setMinion2(int setenemy, int x, int y, int distanceX, int distanceY, int pattern)
{
	for (int i = 0; i < setenemy; i++)
	{
		Enemy1945_2* enemy2 = new Enemy1945_2;
		enemy2->init("에너미2", RectMakeCenter(x + enemy2->getRect().left + i * distanceX,
			y + enemy2->getRect().top + i * distanceY,
			enemy2->getRect().right, enemy2->getRect().bottom), pattern);
		countVec[(int)EnemyType::type2]++;
		_vMinion.push_back(enemy2);
	}
}

void UnitManager::setItem(int x, int y)
{
	for (int i = 0; i < 1; i++)
	{
		Item1945* item = new Item1945;
		item->init("LevelUp", RectMakeCenter(x + item->getRect().left, y + item->getRect().top,
			item->getRect().right, item->getRect().bottom));
		_vItem.push_back(item);
	}
}

void UnitManager::setBoss()
{
	boss = new Boss;
	boss->init("보스", RectMakeCenter(WINSIZEX / 2, -250, boss->getRect().right, boss->getRect().bottom));
}

void UnitManager::minionBulletFire()
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			if (_player->getAlive()) {
				switch ((*_viMinion)->enemyType)
				{
				case  EnemyType::type1:
				{
					angle += 0.3;
					if (*_viMinion == nullptr)continue;
					RECT rc = (*_viMinion)->getRect();
					_bullet->fire(rc.left + (rc.right - rc.left) / 2, 
						rc.bottom + (rc.top - rc.bottom) / 2,
						/*(i + angle) * 0.21 + */UTIL::getAngle(rc.left + (rc.right - rc.left) / 2,
							rc.bottom + (rc.top - rc.bottom) / 2,
							_player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2,
							_player->getRect().top), 5.0f);
				}
				break;
				case  EnemyType::type2:
				{
					if (*_viMinion == nullptr)continue;
					RECT rc = (*_viMinion)->getRect();
					for (size_t i = 0; i < 3; i++)
					{
						_bullet->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2,
							i * 0.3 + UTIL::getAngle(rc.left + (rc.right - rc.left) / 2,
								rc.bottom + (rc.top - rc.bottom) / 2,
								_player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2,
								_player->getRect().top), 4.0f);
					}
				}
				break;
				default:
					break;
				}
			}
		}
	}
}

void UnitManager::bossBulletFire1()
{
	if (boss != nullptr)
	{
		if (_player->getAlive()) {
			if (boss->bulletCountFire1())
			{
				RECT rc = boss->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2 + 10, rc.bottom + (rc.top - rc.bottom) / 2 + 100,
					/*(i + angle) * 0.21 + */UTIL::getAngle(rc.left + (rc.right - rc.left) / 2,
						rc.bottom + (rc.top - rc.bottom) / 2,
						_player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2,
						_player->getRect().top), 8.0f);
			}
		}
	}
}

void UnitManager::bossBulletFire2()
{
	if (boss != nullptr)
	{
		if (_player->getAlive()) {
			if (boss->bulletCountFire2())
			{
				float a = TIME->getWorldTime();
				angle += 0.4;
				RECT rc = boss->getRect();
				for (size_t i = 0; i < 1; i++) {
					int count = 10;
					float tempAngle = 2 / (float)count;
					for (size_t j = 0; j < count; j++) {
						_bullet->fire(rc.left + (rc.right - rc.left) / 2 + 10, rc.bottom + (rc.top - rc.bottom) / 2 + 100,
							(i * 0.2) + PI * tempAngle * j + angle * sinf(a * 0.5), 3.0f);
						_bullet->fire(rc.left + (rc.right - rc.left) / 2 + 10, rc.bottom + (rc.top - rc.bottom) / 2 + 100,
							(i * 0.2) + PI * tempAngle * j - angle * sinf(a * 0.5), 3.0f);
					}
				}
			}
		}
	}
}

void UnitManager::bossBulletFire3()
{
	if (boss != nullptr)
	{
		if (_player->getAlive()) {
			if (boss->bulletCountFire3())
			{
				angle += 0.5;
				for (size_t i = 0; i < 15; i++)
				{
					RECT rc = boss->getRect();
					_bullet->fire(rc.left + (rc.right - rc.left) / 2 + 10, rc.bottom + (rc.top - rc.bottom) / 2 + 100,
						(i + angle) * 0.42, 4.0f);
				}
			}
		}
	}
}


void UnitManager::removeMinion(int arrNum)
{
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void UnitManager::removeItem(int arrNum)
{
	_vItem.erase(_vItem.begin() + arrNum);
}



void UnitManager::removeBoss(int arrNum)
{

}

void UnitManager::collision()
{

	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_bullet->getVBullet()[i].rc, &_player->getRect()))
		{
			_bullet->removeBullet(i);
			_player->hitDamage(5);
		}
	}



	for (int i = 0; i < getVMinion().size(); i++) {
		RECT rc;
		if (getVMinion()[i]->getRect().left > WINSIZEX + 1000 || getVMinion()[i]->getRect().right < -1000 ||
			getVMinion()[i]->getRect().top<-1000 || getVMinion()[i]->getRect().bottom>WINSIZEY + 100)
		{
			countVec[(int)getVMinion()[i]->enemyType]--;
			removeMinion(i);
		}
	}

}




