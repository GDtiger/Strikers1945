// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#include<vector>
#include<map>
#include<string>

//==========================================
//					STL
//==========================================


//==========================================
//				 내가만든 헤더파일
//==========================================
#include"commonMacroFunction.h"
#include"Input.h"
#include"imageManager.h"
#include"timeManager.h"
#include"randomFunction.h"
#include"utils.h"
#include"txtData.h"

//======================================
//##			매니저들			  ##
//======================================
#define InputManager	Input::getSingleton()
#define RND				RandomFunction::getSingleton()
#define IMAGE			imageManager::getSingleton()
#define TIME			timeManager::getSingleton()
#define TXT				txtData::getSingleton()
#define TXT				txtData::getSingleton()
//==========================================
//				 매크로 설정
//==========================================
#define WINNAME			(LPTSTR)(TEXT("스트라이커즈"))
#define WINSTARTX		100
#define WINSTARTY		100
#define WINSIZEX		600
#define WINSIZEY		800
#define	WINSTYLE		WS_CAPTION | WS_SYSMENU


//==========================================
//			메인게임 릴리즈에서 사용
//==========================================

#define SAFE_DELETE(p) {if(p) {delete(p);(p) = nullptr;}}

enum class EnemyType {
	type1,
	type2,
	Boss


};

enum class EffectType {
	one,
	two,
	three

};

//========================================================
//		전역변수 아이들(인스턴스,윈도우 핸들, 마우스 좌표)
//========================================================

extern HINSTANCE m_hInstance;
extern HWND m_hWnd;
extern POINT m_ptMouse;

