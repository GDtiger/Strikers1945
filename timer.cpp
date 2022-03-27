#include "framework.h"
#include "timer.h"
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
//timeGetTime
timer::timer()
{
}

timer::~timer()
{
}

HRESULT timer::init()
{

	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		//초당 시간 계산 범위
		_timeScale = 1.0f / _periodFrequency;
	}
	else 
	{
		_isHardware = false;
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}
	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPStimeElapsed  = 0.0f;
	_worldTime = 0.0f;

	return S_OK;
}

void timer::tick(float lockFPS)
{
	//고성능 타이머를 지원하면
	if (_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else {
		_curTime = timeGetTime();
	}

	_timeElapsed = (_curTime - _lastTime) * _timeScale;


	if (lockFPS > 0.0f)
	{
		while (_timeElapsed <(1.0f/lockFPS))
		{
			if(_isHardware)QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;					//마지막 시간 기록
	_FPSFrameCount++;						//자동으로 프레임 카운트 증가
	_FPStimeElapsed += _timeElapsed;		//초당 프레임 시간 경과량 증가
	_worldTime += _timeElapsed;				//전체 시간 경과량 증가


	if (_FPStimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPStimeElapsed = 0.0f;
	}



}

unsigned long timer::getFrameRate(char* str) const
{

	if (str != NULL)
	{
		wsprintf(str, "FPS : %d", _frameRate);
	}

	return _frameRate;
}
