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


CLinkedList::USERDATA* CLinkedList::getFirst()
{
    return m_Head.pNext;
}


CLinkedList::USERDATA* CLinkedList::findNode(char* pszName)
{
    USERDATA* pTmp = getFirst();

    while (pTmp != nullptr) 
    {
        if (strcmp(pTmp->szName, pszName) == 0)
            return pTmp;
            
        pTmp = pTmp->pNext;
    }

    return nullptr;
}


int CLinkedList::addNewNode(char* pszName, char* pszPhone)
{
    USERDATA* pNewUser = nullptr;

    if (findNode(pszName) != nullptr)
        return 0;

    pNewUser = (USERDATA*)malloc(sizeof(USERDATA));
    memset(pNewUser, 0, sizeof(USERDATA));

    sprintf_s(pNewUser->szName, sizeof(pNewUser->szName), "%s", pszName);
    sprintf_s(pNewUser->szPhone, sizeof(pNewUser->szPhone), "%s", pszPhone);

    pNewUser->pNext = m_Head.pNext;
    m_Head.pNext = pNewUser;

    return 1;
}


int CLinkedList::removeNode(char* pszName)
{
    USERDATA* pPrevNode = &m_Head;
    USERDATA* pDelete = nullptr;

    while (pPrevNode->pNext != nullptr)
    {
        pDelete = pPrevNode->pNext;

        if (strcmp(pDelete->szName, pszName) == 0)
        {
            pPrevNode->pNext = pDelete->pNext;
            free(pDelete);

            return 1;
        }

        pPrevNode = pPrevNode->pNext;
    }

    return 0;
}


void CLinkedList::releaseList()
{
    USERDATA* pTmp = getFirst();
    USERDATA* pDelete = nullptr;

    while (pTmp != nullptr)
    {
        pDelete = pTmp;
        pTmp = pTmp->pNext;

        free(pDelete);
    }

    memset(&m_Head, 0, sizeof(USERDATA));
}


int CLinkedList::loadList()
{
    FILE* fp = nullptr;
    USERDATA user = { 0 };

    fopen_s(&fp, DATA_FILE_NAME, "rb");

    if (fp == nullptr)
        return 0;

    releaseList();

    while (fread(&user, sizeof(USERDATA), 1, fp))
        addNewNode(user.szName, user.szPhone);

    fclose(fp);

    return 0;
}


int CLinkedList::saveList()
{
    FILE* fp = nullptr;
    USERDATA* pTmp = getFirst();

    fopen_s(&fp, DATA_FILE_NAME, "wb");

    if (fp == nullptr)
    {
        // puts("ERROR: 리스트 파일을 쓰기 모드로 열지 못했습니다.");
        // _getch();

        return 0;
    }

    while (pTmp != nullptr)
    {
        if (fwrite(pTmp, sizeof(USERDATA), 1, fp) != 1)
        {
            // printf("ERROR: %s에 대한 정보를 저장하는 데 실패했습니다.\n", pTmp->szName);
            return 0;
        }

        pTmp = pTmp->pNext;
    }

    fclose(fp);

    return 1;
}
