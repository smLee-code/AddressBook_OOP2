#include "pch.h"
#include "CLinkedList.h"
#define DATA_FILE_NAME "Address.dat"

CLinkedList::CLinkedList()
{
    loadList();
}


CLinkedList::~CLinkedList()
{
    saveList();
    releaseList();
}


const CUserData* CLinkedList::getFirst()
{
    return m_Head.getNext();
}


const CUserData* CLinkedList::findNode(char* pszName)
{
    const CUserData* pTmp = m_Head.getNext();

    while (pTmp != nullptr) 
    {
        if (strcmp(pTmp->getName(), pszName) == 0)
            return pTmp;
            
        pTmp = moveNext(pTmp);
    }

    return nullptr;
}


int CLinkedList::addNewNode(char* pszName, char* pszPhone)
{
    CUserData* pNewUser = nullptr;

    if (findNode(pszName) != nullptr)
        return 0;

    pNewUser = new CUserData();

    pNewUser->setName(pszName);
    pNewUser->setPhone(pszPhone);

    pNewUser->pNext = (CUserData*)m_Head.getNext();
    m_Head.pNext = pNewUser;
    return 1;
}

int CLinkedList::addNewNode(FILE* fp)
{
    CUserData* pNewData = new CUserData;

    if (!pNewData->read(fp))
    {
        delete pNewData;
        return 0;   
    }

    pNewData->pNext = (CUserData*)m_Head.getNext();
    m_Head.pNext = pNewData;
    return 1;
}

int CLinkedList::removeNode(char* pszName)
{
    CUserData* pPrevNode = &m_Head;
    CUserData* pDelete = nullptr;

    while (pPrevNode->getNext() != nullptr)
    {
        pDelete = pPrevNode->pNext;

        if (strcmp(pDelete->getName(), pszName) == 0)
        {
            pPrevNode->pNext = pDelete->pNext;
            delete pDelete;

            return 1;
        }

        pPrevNode = pPrevNode->pNext;
    }

    return 0;
}


void CLinkedList::releaseList()
{
    CUserData* pTmp = m_Head.pNext;
    CUserData* pDelete = nullptr;

    while (pTmp != nullptr)
    {
        pDelete = pTmp;
        pTmp = pTmp->pNext;

        free(pDelete);
    }

    m_Head.pNext = nullptr;
}


int CLinkedList::loadList()
{
    FILE* fp = nullptr;

    fopen_s(&fp, DATA_FILE_NAME, "rb");

    if (fp == nullptr)
        return 0;

    releaseList();

    while (addNewNode(fp));

    fclose(fp);

    return 0;
}


int CLinkedList::saveList()
{
    FILE* fp = nullptr;
    CUserData* pTmp = m_Head.pNext;

    fopen_s(&fp, DATA_FILE_NAME, "wb");

    if (fp == nullptr)
    {
        // puts("ERROR: 리스트 파일을 쓰기 모드로 열지 못했습니다.");
        // _getch();

        return 0;
    }

    while (pTmp != nullptr)
    {
        if (pTmp->write(fp) != 1)
        {
            // printf("ERROR: %s에 대한 정보를 저장하는 데 실패했습니다.\n", pTmp->szName);
            return 0;
        }

        pTmp = pTmp->pNext;
    }

    fclose(fp);

    return 1;
}


const CUserData* CLinkedList::moveNext(const CUserData* pCurNode) 
{
    if (pCurNode != nullptr)
    {
        return pCurNode->getNext();
    }
}
