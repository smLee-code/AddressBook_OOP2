#pragma once
#include "CNode.h"
#include "CUserData.h"

class CLinkedList
{
private:
	CNode m_Head;

public:
	CLinkedList();
	~CLinkedList();

	const CNode* getFirst();

	const CNode* findNode(const char* pszKey);
	int addNewNode(CNode* pNewNode);
	int addNewNode(FILE* fp);
	int removeNode(char* pszKey);

	void releaseList();
	int loadList();
	int saveList();

	const CNode* moveNext(const CNode* pCurNode);
};

