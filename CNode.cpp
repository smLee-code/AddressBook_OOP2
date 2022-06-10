#include "pch.h"
#include "CNode.h"

CNode::CNode()
{
	pNext = nullptr;
}

CNode::~CNode()
{

}

int CNode::read(FILE* fp)
{
	pNext = nullptr;

	return 1;
}

int CNode::write(FILE* fp)
{
	return 1;
}