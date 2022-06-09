#pragma once

class CUserData
{
	friend class CLinkedList;

public:
	struct USERDATA
	{
		char szName[32];
		char szPhone[32];
	};

private:
	CUserData* pNext;
	USERDATA m_Data;

public:
	CUserData();
	~CUserData();

	const char* getName() const { return m_Data.szName; }
	const char* getPhone() const { return m_Data.szPhone; }
	const CUserData* getNext() const { return pNext; }
	void setName(const char* pszName);
	void setPhone(const char* pszPhone);

	int read(FILE* fp);
	int write(FILE* fp);
};

