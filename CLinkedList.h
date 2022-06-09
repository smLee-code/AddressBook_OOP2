#pragma once
#include "CUserData.h"

class CLinkedList
{
private:
	CUserData m_Head;

public:
	CLinkedList();
	~CLinkedList();

	const CUserData* getFirst();

	const CUserData* findNode(char* pszName);
	int addNewNode(char* pszName, char* pszPhone);
	int addNewNode(FILE* fp);
	int removeNode(char* pszName);
	void releaseList();
	int loadList();
	int saveList();
	const CUserData* moveNext(const CUserData* pCurNode);
};

