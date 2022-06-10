#pragma once
#include "CNode.h"

class CUserData : public CNode
{
	friend class CLinkedList;

public:
	struct USERDATA
	{
		char szName[32];
		char szPhone[32];
	};

private:
	USERDATA m_Data;

public:
	CUserData();
	~CUserData();

	const char* getName() const { return m_Data.szName; }
	const char* getPhone() const { return m_Data.szPhone; }
	void setName(const char* pszName);
	void setPhone(const char* pszPhone);

	virtual int read(FILE* fp);
	virtual int write(FILE* fp);
	virtual const char* getKey() const;
};

