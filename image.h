#pragma once
class image
{
public:

	enum class IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//리소스 로딩
		LOAD_FILE,			//파일로딩
		LOAD_EMPTY,
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD resID;			//리소스 ID
		HDC hMemDC;				//메모리 DC
		HBITMAP hBit;			//비트맵(새로운 비트맵 핸들)
		HBITMAP hOBit;			//올드 비트맵(기존 비트맵 핸들)
		int width;				//이미지 가로크기
		int height;				//이미지 세로크기
		BYTE loadType;
		float x;				//이미지X 좌표
		float y;				//이미지Y 좌표
		int currentFrameX;		//현재 프레임 X
		int currentFrameY;		//현재 프레임 Y
		int maxFrameX;			//최대 X프레임 갯수
		int maxFrameY;			//최대 Y프레임 갯수
		int frameWidth;			//1프레임  가로길이
		int frameHeight;		//1프레임  세로길이
		
		tagImage()
		{
			resID = 0;
			hMemDC = NULL,
			hBit = NULL,
			hOBit = NULL,
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX=0;
			currentFrameY=0;
			maxFrameX  =0;
			maxFrameY	  =0;
			frameWidth	  =0;
			frameHeight  =0;
			loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_RESOURCE);
		}
	} IMAGE_INFO, *LPIMAGE_INFO;

	image();
	~image();

private:
	LPIMAGE_INFO	_imageInfo;			//이미지 정보
	char*			_fileName;			//이미지 이름
	bool			_isTrans;			//배경색 날릴꺼냐?
	COLORREF		_transColor;		//배경색 날릴 RGB



	//알파용
	BLENDFUNCTION	_blendFunc;			//알파블렌드를 위한 정보
	LPIMAGE_INFO	_blendImage;		//알파블렌드를 사용하기 위한 이미지 정보



public:

	//비트맵 초기화
	HRESULT init(const int width, const int height);
	HRESULT init(const char* fileName, const int width, const int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, const float x, const float y, const int width, const int height, bool  isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	//프레임 이미지 초기화
	HRESULT init(const char* fileName, const int width, const int height, const int frameX, const int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, const int x,const int y,const int width, const int height, const int frameX, const int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));



	//투명값 셋팅
	void setTransColor(bool isTrans, COLORREF transColor);

	void release();

	//렌더
	void render(HDC hdc);
	void render(HDC hdc, const int  destX, const int destY);
	void render(HDC hdc, const int  destX, const int destY,const int sourX, const int sourY, const int sourWidth, const int sourheight);


	//프레임 렌더
	void frameRender(HDC hdc, const int destX, const int destY);
	void frameRender(HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY);
	void frameRender(HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY, float size);

	//루프렌더
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);


	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc,const int destX, const int destY, BYTE alpha);
	void alphaRender(HDC hdc,const int destX, const int destY,const int sourX, const int sourY, const int sourWidth, const int sourHeight, BYTE alpha);

	//DC를 가져와라
	inline HDC getMemDC()const { return _imageInfo->hMemDC; }


	//========이미지 조작질을 쉽게 하기 위한 녀석들==============//

	//이미지 X좌표
	inline float getX()const { return _imageInfo->x; }
	inline float  setX(const float x) { return _imageInfo->x= x; }
	//이미지 Y좌표
	inline float getY()const { return _imageInfo->y; }
	inline float  setY(const float y) { return _imageInfo->y = y; }

	//이미지 센터 좌표셋팅
	inline void setCenter(const float x, const float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}
	//가로세로 크기 얻기
	inline int getWidth()const { return _imageInfo->width; }
	inline int getHeight()const { return _imageInfo->height; }

	//바운딩 박스(충돌용)
	inline RECT getBoundingBox()
	{
		RECT rc = RectMakeCenter(_imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height);
		return rc;
	}

	//프레임 X셋팅
	inline  int getFrameX()const { return _imageInfo->currentFrameX; }
	inline  void setFrameX(const int frameX) 
	{
		_imageInfo->currentFrameX = frameX;

		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//프레임 Y셋팅
	inline  int getFrameY()const { return _imageInfo->currentFrameY; }
	inline  void setFrameY(const int frameY)
	{
		_imageInfo->currentFrameY = frameY;

		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//1프레임 가로세크로기 얻기
	inline int getFrameWidth()const { return _imageInfo->frameWidth; }
	inline int getFrameHeight()const { return _imageInfo->frameHeight; }



	//맥스프레임 가로세로크기 얻기
	inline int getMaxFrameX()const { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY()const { return _imageInfo->maxFrameY; }
};

