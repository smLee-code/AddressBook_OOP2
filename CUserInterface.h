#pragma once
#include "CLinkedList.h"
#include "CUserData.h"

class CUserInterface
{
private:
	CLinkedList& m_list;

public:
	CUserInterface(CLinkedList& db);  
	~CUserInterface();

	void flush_stdin();
	void add();
	void search();
	void printAll();
	void remove();
	int printUI();
	void run();
};

