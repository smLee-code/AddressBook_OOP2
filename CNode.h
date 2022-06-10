#pragma once
class CNode
{
	friend class CLinkedList;

private:
	CNode* pNext;

public:
	CNode();
	virtual ~CNode();

	virtual int read(FILE* fp);
	virtual int write(FILE* fp);
	virtual  const char* getKey() const { return nullptr; }

	const CNode* getNext() const { return pNext; }
};

