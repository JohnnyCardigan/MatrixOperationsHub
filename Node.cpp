#include "Node.h"

ColumnNode::ColumnNode(double nValue, ColumnNode* nPtr)
{
	setColVal(nValue);
	setColPtr(nPtr);
}

ColumnNode::~ColumnNode()
{
}

void ColumnNode::setColVal(double nValue)
{
	mColVal = nValue;
}

void ColumnNode::setColVal(int nValue)
{
	mColVal = (double)nValue;
}

void ColumnNode::setColPtr(ColumnNode * nPtr)
{
	mColPtr = nPtr;
}

double ColumnNode::getColVal()
{
	return mColVal;
}

ColumnNode * ColumnNode::getColPtr()
{
	return mColPtr;
}

RowNode::RowNode(RowNode* nRowPtr, ColumnNode* nColPtr)
{
	setRowPtr(nRowPtr);
	setColPtr(nColPtr);
}

RowNode::~RowNode()
{
}

void RowNode::setRowPtr(RowNode * nPtr)
{
	mRowPtr = nPtr;
}

void RowNode::setColPtr(ColumnNode * nPtr)
{
	mColPtr = nPtr;
}

RowNode * RowNode::getRowPtr()
{
	return mRowPtr;
}

ColumnNode * RowNode::getColPtr()
{
	return mColPtr;
}

