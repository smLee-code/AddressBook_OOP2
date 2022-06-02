#pragma once

class CLinkedList
{
public:
	struct USERDATA
	{
		char szName[32];
		char szPhone[32];

		struct USERDATA* pNext;
	};

private:
	USERDATA m_Head = { 0 };

public:
	CLinkedList();
	~CLinkedList();

	USERDATA* getFirst();

	USERDATA* findNode(char* pszName);
	int addNewNode(char* pszName, char* pszPhone);
	int removeNode(char* pszName);
	void releaseList();
	int loadList();
	int saveList();
	
};

