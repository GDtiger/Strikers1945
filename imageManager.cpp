#include"framework.h"
#include "imageManager.h"

imageManager::imageManager()
{
}

imageManager::~imageManager()
{
}

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	deleteAll();
}

image* imageManager::addImage(string strKey, const int width, const int height)
{
	//�߰��Ϸ��� Ű������ �̹��� �����ϴ��� Ȯ��
	image* img = findImage(strKey);
	//�߰��Ϸ��� �̹����� �̹� ������ ����
	if (img)return img;

	img = new image;

	//�̹����� �ʱ�ȭ���� ������
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ��߰��Ѵ�.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName, const int width, const int height, bool trans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹��� �����ϴ��� Ȯ��
	image* img = findImage(strKey);
	//�߰��Ϸ��� �̹����� �̹� ������ ����
	if (img)return img;

	img = new image;

	//�̹����� �ʱ�ȭ���� ������
	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ��߰��Ѵ�.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName, const float x, const float y, const int const width, const int height, bool trans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹��� �����ϴ��� Ȯ��
	image* img = findImage(strKey);
	//�߰��Ϸ��� �̹����� �̹� ������ ����
	if (img)return img;

	img = new image;

	//�̹����� �ʱ�ȭ���� ������
	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ��߰��Ѵ�.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName, const int width, const int height, const int frameX, const int frameY, bool trans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹��� �����ϴ��� Ȯ��
	image* img = findImage(strKey);
	//�߰��Ϸ��� �̹����� �̹� ������ ����
	if (img)return img;

	img = new image;

	//�̹����� �ʱ�ȭ���� ������
	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ��߰��Ѵ�.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName, const float x, const float y, const int width, const int height, const int frameX, const int frameY, bool trans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹��� �����ϴ��� Ȯ��
	image* img = findImage(strKey);
	//�߰��Ϸ��� �̹����� �̹� ������ ����
	if (img)return img;

	img = new image;

	//�̹����� �ʱ�ȭ���� ������
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ��߰��Ѵ�.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::findImage(string strKey)
{
	//�ش�Ű �˻�
	mapImageListIter key = _mImageList.find(strKey);

	//Ű�� ã����
	if (key != _mImageList.end())
	{
		return key->second;
	}
	return NULL;
}

bool imageManager::deleteImage(string strKey)
{
	mapImageListIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);
		return true;
	}
	return false;
}

bool imageManager::deleteAll()
{
	//�� ��ü�� ���鼭 �����Ѵ�.
	mapImageListIter iter = _mImageList.begin();

	for (iter; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}
	_mImageList.clear();
	return true;
}

void imageManager::render(string strKey, HDC hdc)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, const int destX, const int destY)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourHeight)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::frameRender(string strKey, HDC hdc, const int destX, const int destY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea,int offSetX, int offSetY)
{
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offSetX, offSetY);
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offSetX, offSetY, alpha);
}
