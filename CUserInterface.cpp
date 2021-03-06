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

	CUserData* pNewData = new CUserData();
	pNewData->setName(szName);
	pNewData->setPhone(szPhone);

	if (m_list.addNewNode(pNewData) == 0)
	{
		puts("ERROR: 이름이 같은 데이터가 이미 존재합니다.");
		_getch();
		delete pNewData;
	}
}


void CUserInterface::search()
{
	char szName[32] = { 0 };
	const CUserData* pNode = nullptr;

	printf("Input name : ");
	flush_stdin();
	gets_s(szName, sizeof(szName));

	pNode = (const CUserData*)m_list.findNode(szName);
	if (pNode != nullptr)
	{
		printf("[%p] %s\t%s [%p]\n", pNode, pNode->getName(), pNode->getPhone(), pNode->getNext());
	}
	else
	{
		// puts("ERROR: 데이터를 찾을 수 없습니다.");
	}

	_getch();
}


void CUserInterface::printAll()
{
	const CUserData* pTmp = (const CUserData*)m_list.getFirst();
	while (pTmp != nullptr)
	{
		printf("[%p] %s\t%s [%p]\n", pTmp, pTmp->getName(), pTmp->getPhone(), pTmp->getNext());

		pTmp = (const CUserData*)m_list.moveNext(pTmp);
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
