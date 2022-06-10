#include "pch.h"
#include "CUserData.h"


CUserData::CUserData()
{
	memset(&m_Data, 0, sizeof(USERDATA));
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
	CNode::read(fp);
	return fread(&m_Data, sizeof(USERDATA), 1, fp);
}

int CUserData::write(FILE* fp)
{
	CNode::write(fp);
	return fwrite(&m_Data, sizeof(USERDATA), 1, fp);
}

const char* CUserData::getKey() const
{
	return m_Data.szName;
}