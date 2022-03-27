#pragma once
#include"singleton.h"
#include"image.h"
class imageManager : public Singleton<imageManager>
{
private:
	//맵으로 만든 이미지 목록
	typedef map<string, image*> mapImageList;
	typedef map<string, image*>::iterator mapImageListIter;


	mapImageList _mImageList;

public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	//키값으로 빈 비트맵 초기화
	image* addImage(string strKey, const int width, const int height);
	image* addImage(string strKey, const char* fileName, const int width, const int height, bool trans, COLORREF transColor);
	image* addImage(string strKey, const char* fileName, const float x, const float y, const int const width, const int height, bool trans, COLORREF transColor);


	//키값으로 프레임 이미지 초기화
	image* addFrameImage(string strKey, const char* fileName, const int width, const int height, const int frameX, const int frameY, bool trans, COLORREF transColor);
	image* addFrameImage(string strKey, const char* fileName, const float x, const float y, const int width, const int height, const int frameX, const int frameY, bool trans, COLORREF transColor);

	//이미지를 찾아라
	image* findImage(string strKey);
	//이미지 키값으로 삭제
	bool deleteImage(string strKey);

	//이미지 전체삭제
	bool deleteAll();

	//렌더
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, const int destX, const int destY);
	void render(string strKey, HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourHeight);

	//프레임
	void frameRender(string strKey, HDC hdc, const int destX, const int destY);
	void frameRender(string strKey, HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY);

	//루프
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);

};

