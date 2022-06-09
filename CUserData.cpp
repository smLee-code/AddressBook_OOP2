#include "pch.h"
#include "CUserData.h"


CUserData::CUserData()
{
	memset(&m_Data, 0, sizeof(USERDATA));
	pNext = nullptr;
}

CUserData::~CUserData()
{

}



void CUserData::setName(const char* pszName)
{
	strcpy_s(m_Data.szName, pszName);
}


void CUserData::setPhone(const char* pszPhone)
{
	strcpy_s(m_Data.szPhone, pszPhone);
}

int CUserData::read(FILE* fp)
{
	int result = fread(&m_Data, sizeof(USERDATA), 1, fp);
	pNext = nullptr;

	return result;
}

int CUserData::write(FILE* fp)
{
	return fwrite(&m_Data, sizeof(USERDATA), 1, fp);
}