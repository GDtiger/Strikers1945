#include"framework.h"
#include "airHockey.h"

airHockey::airHockey()
{
}

airHockey::~airHockey()
{
}

HRESULT airHockey::init()
{
	_coat[0] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + (WINSIZEY / 2 / 2), WINSIZEX, WINSIZEY / 2);
	_coat[1] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2/2, WINSIZEX, WINSIZEY / 2);
	_goal[0] = RectMakeCenter(WINSIZEX / 2, WINSIZEY, WINSIZEX / 3, 10);
	_goal[1] = RectMakeCenter(WINSIZEX / 2, 0, WINSIZEX / 3, 10);

	_ball.speed = 0.0f;
	_ball.smash = false;
	_ball.radius = WINSIZEX / 20;
	_ball.x = WINSIZEX / 2;
	_ball.y = WINSIZEY / 2;
	_ball.rc = RectMakeCenter(_ball.x, _ball.y, _ball.radius * 2, _ball.radius * 2);

	_racket[0].radius = WINSIZEX / 15;
	_racket[0].x = WINSIZEX / 2;
	_racket[0].y = WINSIZEY / 2+(WINSIZEY/2/2);
	_racket[0].rc = RectMakeCenter(_racket[0].x, _racket[0].y, _racket[0].radius * 2, _racket[0].radius * 2);



	_racket[1].radius = WINSIZEX / 15;
	_racket[1].x = WINSIZEX / 2;
	_racket[1].y = WINSIZEY /2 /2;
	_racket[1].rc = RectMakeCenter(_racket[1].x, _racket[1].y, _racket[1].radius * 2, _racket[1].radius * 2);


	return S_OK;
}

void airHockey::release()
{
}

void airHockey::update()
{
	if (InputManager->isStayKeyDown(VK_RIGHT))_racket[0].x += RACKET_SPEED;
	if (InputManager->isStayKeyDown(VK_LEFT))_racket[0].x -= RACKET_SPEED;
	if (InputManager->isStayKeyDown(VK_UP))_racket[0].y -= RACKET_SPEED;
	if (InputManager->isStayKeyDown(VK_DOWN))_racket[0].y+= RACKET_SPEED;


	if (InputManager->isStayKeyDown('D'))_racket[1].x += RACKET_SPEED;
	if (InputManager->isStayKeyDown('A'))_racket[1].x -= RACKET_SPEED;
	if (InputManager->isStayKeyDown('W'))_racket[1].y -= RACKET_SPEED;
	if (InputManager->isStayKeyDown('S'))_racket[1].y += RACKET_SPEED;



	for (size_t i = 0; i < 2; i++)
	{
		//외니쪽
		if (_racket[i].x - _racket[i].radius < 0)
		{
			_racket[i].x = _racket[i].radius;
		}  
		//오른쪽
		else if (_racket[i].x + _racket[i].radius > WINSIZEX)
		{
			_racket[i].x = WINSIZEX-_racket[i].radius;
		}

		//위
		if (_racket[i].y - _racket[i].radius < _coat[i].top)
		{
			_racket[i].y = _coat[i].top + _racket[i].radius;
			_racket[i].angle = PI2 - _racket[i].angle;
		}
		//아래
		else if (_racket[i].y + _racket[i].radius > _coat[i].bottom)
		{
			_racket[i].y = _coat[i].bottom - _racket[i].radius;
			_racket[i].angle = PI2 - _racket[i].angle;
		}
	}

	ballMove();
	smash();


	if (_goal[0].top <= _ball.y + _ball.radius && _goal[1].left <= _ball.x && _ball.x <= _goal[1].right)
	{
		score[1]++;
		_ball.x = WINSIZEX / 2;
		_ball.y = WINSIZEY / 2;
		_racket[0].x = WINSIZEX / 2;
		_racket[0].y = WINSIZEY / 2 + (WINSIZEY / 2 / 2);
		_racket[1].x = WINSIZEX / 2;
		_racket[1].y = WINSIZEY / 2 / 2;
		_ball.smash = false;
	}

	if (_goal[1].bottom >= _ball.y - _ball.radius && _goal[1].left <= _ball.x && _ball.x <= _goal[1].right)
	{
		score[0]++;
		_ball.x = WINSIZEX / 2;
		_ball.y = WINSIZEY / 2;
		_racket[0].x = WINSIZEX / 2;
		_racket[0].y = WINSIZEY / 2 + (WINSIZEY / 2 / 2);
		_racket[1].x = WINSIZEX / 2;
		_racket[1].y = WINSIZEY / 2 / 2;
		_ball.smash = false;
	}




}

void airHockey::render(HDC hdc)
{
	for (size_t i = 0; i < 2; i++)
	{
		Rectangle(hdc, _coat[i].left, _coat[i].top, _coat[i].right, _coat[i].bottom);
		Rectangle(hdc, _goal[i].left, _goal[i].top, _goal[i].right, _goal[i].bottom);
	}
	for (size_t i = 0; i < 2; i++)
	{
		ElllipseMakeCenter(hdc, _racket[i].x, _racket[i].y, _racket[i].radius*2, _racket[i].radius * 2);
	}
	ElllipseMakeCenter(hdc, _ball.x, _ball.y,_ball.radius*2, _ball.radius * 2);

	sprintf_s(score1, "1P 점수 : %d", score[0]);
	TextOut(hdc, 20, WINSIZEY - 40, score1, strlen(score1));
	sprintf_s(score2, "2P 점수 : %d", score[1]);
	TextOut(hdc, 20,20, score2, strlen(score2));
}

void airHockey::ballMove()
{
	for (size_t i = 0; i < 2; i++)
	{
		float length = sqrtf((_racket[i].x - _ball.x) *
			(_racket[i].x - _ball.x) +
			(_racket[i].y - _ball.y) *
			(_racket[i].y - _ball.y));

		if (_racket[i].radius + _ball.radius < length)continue;

		_ball.angle = UTIL::getAngle(_racket[i].x, _racket[i].y, _ball.x, _ball.y);
		_ball.speed = 10;
		_ball.smash = true;
	}
}

void airHockey::smash()
{
	if (_ball.smash)
	{
		_ball.x += cosf(_ball.angle) * _ball.speed;
		_ball.y += -sinf(_ball.angle) * _ball.speed;
		_ball.rc = RectMakeCenter(_ball.x, _ball.y, _ball.radius * 2, _ball.radius * 2);
		_ball.speed -= 0.02f;

		if (_ball.x - _ball.radius < 0)
		{
			_ball.x = _ball.radius;
			_ball.angle = PI - _ball.angle;
		}
		else if (_ball.x + _ball.radius > WINSIZEX)
		{
			_ball.x = WINSIZEX - _ball.radius;
			_ball.angle = PI - _ball.angle;
		}
		else if (_ball.y - _ball.radius < 0)
		{
			_ball.y = _ball.radius;
			_ball.angle = PI2 - _ball.angle;
		}
		else if (_ball.y+ _ball.radius > WINSIZEY)
		{
			_ball.y = WINSIZEY-_ball.radius;
			_ball.angle = PI2 - _ball.angle;
		}
		if (_ball.speed <= 0)_ball.smash = false;

	}
}
