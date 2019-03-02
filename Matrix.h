#pragma once
#include "Node.h"

class Matrix
{
public:
	Matrix(int nRows = 0, int nColumns = 0, int nOperation = 0);
	~Matrix();
	void setNumRows(int nRows);
	void setNumCols(int nColumns);
	void setMatrixPtr();
	void setOperationMode(int nMode);
	void resetMatrixPtr();
	int getNumRows();
	int getNumCols();
	int getOperationMode();
	RowNode* getMatrixPtr();
	void resetMatrix();
	void inputMatrixSize();
	void propagateRows();
	void propagateValues();
	void printMatrix();
	int displayMenu();
	void runApp();
	void swapRows();
	void swapRows(int sourceRow, int destRow);
	void scaleRow();
	void scaleToOne();
	void scaleAllToOne();
	void replaceRows();
	void randomMatrix();
	int makeRandomInt();
	double makeRandomDouble();
	void sortEchelon(int row, int column);
	void rowReduce();
	void identityMatrix();
private:
	RowNode* mMatrixPtr;
	int mOperationMode;
	int mNumRows;
	int mNumCols;
};