#include "pch.h"
#include "CUserInterface.h"
#include "CLinkedList.h"
#include <conio.h>

CUserInterface::CUserInterface(CLinkedList& db) : m_list(db)
{

}

CUserInterface::~CUserInterface()
{

}



void CUserInterface::flush_stdin()
{
	while (getchar() != '\n');
}


void CUserInterface::add()
{
	char szName[32] = { 0 };
	char szPhone[32] = { 0 };

	printf("Input name : ");
	flush_stdin();
	gets_s(szName, sizeof(szName));

	printf("Input phone number : ");
	gets_s(szPhone, sizeof(szPhone));

	m_list.addNewNode(szName, szPhone);
}


void CUserInterface::search()
{
	char szName[32] = { 0 };
	CLinkedList::USERDATA* pNode = nullptr;

	printf("Input name : ");
	flush_stdin();
	gets_s(szName, sizeof(szName));

	pNode = m_list.findNode(szName);
	if (pNode != nullptr)
	{
		printf("[%p] %s\t%s [%p]\n", pNode, pNode->szName, pNode->szPhone, pNode->pNext);
	}
	else
	{
		// puts("ERROR: 데이터를 찾을 수 없습니다.");
	}

	_getch();
}


void CUserInterface::printAll()
{
	CLinkedList::USERDATA* pTmp = m_list.getFirst();
	while (pTmp != nullptr)
	{
		printf("[%p] %s\t%s [%p]\n", pTmp, pTmp->szName, pTmp->szPhone, pTmp->pNext);

		pTmp = pTmp->pNext;
	}

	_getch();
}


void CUserInterface::remove()
{
	char szName[32] = { 0 };

	printf("Input name : ");
	flush_stdin();
	gets_s(szName, sizeof(szName));

	m_list.removeNode(szName);
}


int CUserInterface::printUI()
{
	int nInput = 0;

	system("cls");
	printf("[1] Add\t [2] Search\t [3] Print all\t [4] Remove\t [0] Exit\n:");

	scanf_s("%d", &nInput);

	return nInput;
}


void CUserInterface::run()
{
	int nMenu = 0;
	while ((nMenu = printUI()) != 0)
	{
		switch (nMenu) {
		case 1:
			add();
			break;
		case 2:
			search();
			break;
		case 3:
			printAll();
			break;
		case 4:
			remove();
			break;
		}
	}
}
