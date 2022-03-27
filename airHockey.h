#pragma once
#include"gameNode.h"
#define RACKET_SPEED 5
struct tagBall
{
	RECT rc;
	float x, y;
	float angle;
	float speed;
	float radius;
	bool smash;
};
struct tagRacket
{
	RECT rc;
	float x, y;
	float angle;
	float radius;
};
class airHockey : public gameNode
{
private:
	tagBall _ball;
	tagRacket _racket[2];
	RECT _coat[2];
	RECT _goal[2];
	int score[2];
	char score1[64];
	char score2[64];


public:
	airHockey();
	~airHockey();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void ballMove();
	void smash();
};

