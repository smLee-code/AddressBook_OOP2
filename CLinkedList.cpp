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


const CNode* CLinkedList::getFirst()
{
    return m_Head.getNext();
}


const CNode* CLinkedList::findNode(const char* pszKey)
{
    const CNode* pTmp = m_Head.getNext();

    while (pTmp != nullptr) 
    {
        if (strcmp(pTmp->getKey(), pszKey) == 0)
            return pTmp;
            
        pTmp = moveNext(pTmp);
    }

    return nullptr;
}


int CLinkedList::addNewNode(CNode* pNewNode)
{
    if (findNode(pNewNode->getKey()) != NULL)
        return 0;

    pNewNode->pNext = (CNode*)m_Head.getNext();
    m_Head.pNext = pNewNode;
    return 1;
}

int CLinkedList::addNewNode(FILE* fp)
{
    CNode* pNewData = new CUserData;

    if (!pNewData->read(fp))
    {
        delete pNewData;
        return 0;   
    }

    pNewData->pNext = (CNode*)m_Head.getNext();
    m_Head.pNext = pNewData;
    return 1;
}

int CLinkedList::removeNode(char* pszKey)
{
    CNode* pPrevNode = &m_Head;
    CNode* pDelete = nullptr;

    while (pPrevNode->getNext() != nullptr)
    {
        pDelete = pPrevNode->pNext;

        if (strcmp(pDelete->getKey(), pszKey) == 0)
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
    CNode* pTmp = m_Head.pNext;
    CNode* pDelete = nullptr;

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
    CNode* pTmp = m_Head.pNext;

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


const CNode* CLinkedList::moveNext(const CNode* pCurNode) 
{
    if (pCurNode != nullptr)
    {
        return pCurNode->getNext();
    }

    return nullptr;
}
