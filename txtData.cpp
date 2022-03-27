#include "framework.h"
#include "txtData.h"

txtData::txtData()
{
}

txtData::~txtData()
{
}

HRESULT txtData::init()
{
	return S_OK;
}

void txtData::txtSave(char* saveFileName, vector<string> vStr)
{
	HANDLE file;
	char str[128];
	DWORD write;


	strncpy_s(str, 128, vectorArrayCombine(vStr), 128);

	file = CreateFile(
		saveFileName,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);


	WriteFile(file, str, 128, &write, NULL);
	CloseHandle(file);
}

char* txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[128];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, 128, vArray[i].c_str(), 128);

		if ((i + 1) < vArray.size())
		{
			strcat(str, ",");
		}
	}
	return str;
}

vector<string> txtData::txtLoad(char* loadFileName)
{
	HANDLE file;
	char str[128];
	DWORD read;

	ZeroMemory(str, sizeof(str));

	file = CreateFile(
		loadFileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);


	ReadFile(file, str, 128, &read, NULL);
	CloseHandle(file);

	return charArraySeperation(str);
}

vector<string> txtData::charArraySeperation(char charArray[])
{

	vector<string> vArray;
	char* seperator = ",";
	char* token;
	token = strtok(charArray, seperator);
	vArray.push_back(token);


	while (NULL!=(token = strtok(NULL,seperator)))
	{
		vArray.push_back(token);
	}


	return vArray;
}
