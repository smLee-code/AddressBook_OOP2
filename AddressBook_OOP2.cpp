#pragma once
#include "pch.h"
#include "CUserInterface.h"
#include "CLinkedList.h"

int main()
{
    CLinkedList myList;
    CUserInterface myUI(myList);

    myUI.run();
    return 0;
}

