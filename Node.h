#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class ColumnNode
{
public:
	ColumnNode(double nValue = 0, ColumnNode* nPtr = nullptr);
	~ColumnNode();
	void setColVal(double nValue);
	void setColVal(int nValue);
	void setColPtr(ColumnNode* nPtr);
	double getColVal();
	ColumnNode* getColPtr();
private:
	double mColVal;
	ColumnNode* mColPtr;
};

class RowNode
{
public:
	RowNode(RowNode* nRowPtr = nullptr, ColumnNode* nColPtr = nullptr);
	~RowNode();
	void setRowPtr(RowNode* nPtr);
	void setColPtr(ColumnNode* nPtr);
	RowNode* getRowPtr();
	ColumnNode* getColPtr();
private:
	RowNode* mRowPtr;
	ColumnNode* mColPtr;
};

