#include "Matrix.h"

Matrix::Matrix(int nRows, int nCols, int nOperation)
{
	setNumRows(nRows);
	setNumCols(nCols);
	setMatrixPtr();
	setOperationMode(nOperation);
}

Matrix::~Matrix()
{
}

void Matrix::setNumRows(int nRows)
{
	mNumRows = nRows;
	if (mNumRows < 0)
	{
		mNumRows = 0;
	}
}

void Matrix::setNumCols(int nCols)
{
	mNumCols = nCols;
	if (mNumCols < 0)
	{
		mNumCols = 0;
	}
}

void Matrix::setMatrixPtr()
{
	mMatrixPtr = new RowNode;
}

void Matrix::setOperationMode(int nMode)
{
	mOperationMode = nMode;
}

void Matrix::resetMatrixPtr()
{
	mMatrixPtr = nullptr;
}

int Matrix::getNumRows()
{
	return mNumRows;
}

int Matrix::getNumCols()
{
	return mNumCols;
}

int Matrix::getOperationMode()
{
	return mOperationMode;
}

RowNode * Matrix::getMatrixPtr()
{
	return mMatrixPtr;
}

void Matrix::resetMatrix()
{
	RowNode* pRow = mMatrixPtr, * pTempRow = nullptr;
	ColumnNode* pCol = nullptr, * pTempCol = nullptr;

	resetMatrixPtr();

	while (pRow)
	{
		pCol = pRow->getColPtr();
		pRow->setColPtr(nullptr);

		while (pCol)
		{
			pTempCol = pCol;
			pCol = pCol->getColPtr();
			delete pTempCol;
			pTempCol = nullptr;
		}

		pTempRow = pRow;
		pRow = pRow->getRowPtr();
		delete pTempRow;
		pTempRow = nullptr;
	}

	setMatrixPtr();
	setNumCols(0);
	setNumRows(0);
}

void Matrix::inputMatrixSize()
{
	int numRows = 0, numCols = 0;
	bool verifyInput = false;

	while (!verifyInput)
	{
		cout << endl << "Number of rows: ";

		if (!(cin >> numRows))
		{
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
		{
			setNumRows(numRows);
			cout << endl << "Your matrix has " << getNumRows() << " rows." << endl;
			verifyInput = true;
		}
	}

	verifyInput = false;

	while (!verifyInput)
	{
		cout << endl << "Number of columns: ";

		if (!(cin >> numCols))
		{
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
		{
			setNumCols(numCols);
			cout << endl << "Your matrix has " << getNumCols() << " columns." << endl;
			verifyInput = true;
		}
	}

}

void Matrix::propagateRows()
{
	RowNode* pRow = mMatrixPtr;//local row pointer
	ColumnNode* pCol = nullptr;//local column pointer

	for (int i = 0; i < mNumRows; i++)
	{
		pRow->setColPtr(new ColumnNode);//set row node's column pointer to a new column node

		pCol = pRow->getColPtr();//set pCol to point at the new column node

		for (int j = 1; j < mNumCols; j++)//iterate for number of columns (start at 1 because first node is already made
		{
			pCol->setColPtr(new ColumnNode);//attach the next column node to the current column node's colPtr
			pCol = pCol->getColPtr();//update pCol to point to new column node
		}
	
		pRow->setRowPtr(new RowNode);//attach the next row node to the current row node's rowPtr

		pRow = pRow->getRowPtr();//update pRow to point to the new row node

	}
}

void Matrix::propagateValues()
{
	RowNode* pRow = mMatrixPtr;
	ColumnNode* pCol = nullptr;
	int rowCount = 1, colCount = 1;
	bool verifyInput = false;
	double colValue = 0.0;
	cout << endl;

	for (; rowCount <= mNumRows; rowCount++)
	{
		pCol = pRow->getColPtr();

		for (colCount = 1; colCount <= mNumCols; colCount++)
		{
			verifyInput = false;

			while (!verifyInput)
			{
				cout << "Row " << rowCount << ", " << "Column " << colCount << endl << "Enter value: ";

				if (!(cin >> colValue))
				{
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else
				{
					pCol->setColVal(colValue);
					pCol = pCol->getColPtr();
					verifyInput = true;
				}
			}
		}

		pRow = pRow->getRowPtr();
	}
}

void Matrix::printMatrix()
{
	RowNode* pRow = mMatrixPtr;
	ColumnNode* pCol = nullptr;
	int rowCount = 1, colCount = 1;

	cout << endl;

	if (!mMatrixPtr->getColPtr())
	{
		cout << "Your matrix is empty." << endl;
	}
	else
	{
		for (; rowCount <= mNumRows; rowCount++)
		{
			pCol = pRow->getColPtr();

			cout << endl << "Row " << rowCount;

			for (colCount = 1; colCount <= mNumCols; colCount++)
			{
				cout << "    " << "(" << colCount << ") " << pCol->getColVal();
				pCol = pCol->getColPtr();
			}
			cout << endl;

			pRow = pRow->getRowPtr();
		}
	}
	cout << endl;
}

int Matrix::displayMenu()
{
	int menuOption = 0;

	while (menuOption == 0)
	{
		cout << "Please choose one of the following options:" << endl <<
			"1. Quit" << endl <<
			"2. Input a matrix" << endl <<
			"3. Clear your matrix" << endl <<
			"4. Print your matrix" << endl <<
			"5. Swap rows" << endl <<
			"6. Scale a row" << endl <<
			"7. Scale a row so leading entry is 1" << endl <<
			"8. Scale all rows so leading entries are 1" << endl <<
			"9. Replace rows" << endl <<
			"10. Generate a random n x m matrix" << endl <<
			"11. Convert matrix to reduced echelon form (not fully implemented)" << endl <<
			"12. Generate an n x n identity matrix" << endl;

		if (!(cin >> menuOption))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "I'm sorry that is not a valid choice." << endl;
			menuOption = 0;
		}
		else
		{
			switch (menuOption)
			{
			case 1://quit
				resetMatrix();
				cout << endl << endl << "Goodbye! :)" << endl;
				break;
			case 2://input a matrix
				resetMatrix();
				inputMatrixSize();
				propagateRows();
				propagateValues();
				printMatrix();
				break;
			case 3://clear matrix
				resetMatrix();
				printMatrix();
				break;
			case 4://print matrix
				printMatrix();
				break;
			case 5://swap rows
				swapRows();
				printMatrix();
				break;
			case 6://scale a row
				scaleRow();
				printMatrix();
				break;
			case 7://set leading entry to 1
				scaleToOne();
				printMatrix();
				break;
			case 8://scale all leading entries to 1
				scaleAllToOne();
				printMatrix();
				break;
			case 9://row replacement
				replaceRows();
				printMatrix();
				break;
			case 10://random matrix
				resetMatrix();
				randomMatrix();
				printMatrix();
				break;
			case 11://row reduce
				rowReduce();
				printMatrix();
			case 12://identity matrix
				resetMatrix();
				identityMatrix();
				printMatrix();
				break;
			default:
				cout << "I'm sorry that is not a valid choice." << endl;
				menuOption = 0;
				break;
			}
		}
	}

	return menuOption;
}

void Matrix::runApp()
{
	setOperationMode(displayMenu());
}

void Matrix::swapRows()
{
	int rowSource = -1, rowDestination = -1;

	if (getNumRows() == 0)
	{
		cout << "Your matrix is empty." << endl;
		return;
	}

	cout << "Enter first row to swap: ";

	while (rowSource == -1)
	{
		if (!(cin >> rowSource))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please try again." << endl;
		}
		if (rowSource > getNumRows())
		{
			cout << "Your matrix does not have that many rows." << endl;
			rowSource = -1;
		}
	}

	cout << endl << "Enter second row to swap: ";
	
	while (rowDestination == -1)
	{
		if (!(cin >> rowDestination))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please try again." << endl;
		}
		if (rowDestination > getNumRows())
		{
			cout << "Your matrix does not have that many rows." << endl;
			rowDestination = -1;
		}
	}

	RowNode* rowSptr = getMatrixPtr(), *rowDptr = getMatrixPtr();
	ColumnNode* rowTempPtr = nullptr;
	int i = 0;

	for (i = 1; i < rowSource; i++)
	{
		rowSptr = rowSptr->getRowPtr();
	}

	for (i = 1; i < rowDestination; i++)
	{
		rowDptr = rowDptr->getRowPtr();
	}

	rowTempPtr = rowSptr->getColPtr();
	rowSptr->setColPtr(rowDptr->getColPtr());
	rowDptr->setColPtr(rowTempPtr);
}

void Matrix::swapRows(int sourceRow, int destRow)
{
	RowNode* rowSptr = getMatrixPtr(), *rowDptr = getMatrixPtr();
	ColumnNode* rowTempPtr = nullptr;
	int i = 0;

	for (i = 1; i < sourceRow; i++)
	{
		rowSptr = rowSptr->getRowPtr();
	}

	for (i = 1; i < destRow; i++)
	{
		rowDptr = rowDptr->getRowPtr();
	}

	rowTempPtr = rowSptr->getColPtr();
	rowSptr->setColPtr(rowDptr->getColPtr());
	rowDptr->setColPtr(rowTempPtr);

}

void Matrix::scaleRow()
{
	RowNode* pRow = getMatrixPtr();
	int rowOption = 0;
	double scalar = 0.0;

	if (!(pRow->getColPtr()))
	{
		cout << "Your matrix is empty." << endl;
		return;
	}
	else
	{
		while (rowOption == 0)
		{
			cout << "Row: ";

			if (!(cin >> rowOption))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				rowOption = 0;
			}
			else if (rowOption < 0)
			{
				rowOption = 0;
			}
			else if (rowOption > getNumRows())
			{
				rowOption = 0;
			}
		}

		while (scalar == 0)
		{
			cout << "Scalar: ";

			if (!(cin >> scalar))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				scalar = 0;
			}
		}

		for (int i = 1; i < rowOption; i++)
		{
			pRow = pRow->getRowPtr();
		}

		ColumnNode* pCol = pRow->getColPtr();

		while (pCol)
		{
			pCol->setColVal((pCol->getColVal()) * scalar);
			pCol = pCol->getColPtr();
		}

	}
}

void Matrix::scaleToOne()
{
	RowNode* pRow = getMatrixPtr();
	int rowOption = 0;
	double scalar = 0.0;

	if (!(pRow->getColPtr()))
	{
		cout << "Your matrix is empty." << endl;
		return;
	}
	else
	{
		while (rowOption == 0)
		{
			cout << "Row: ";

			if (!(cin >> rowOption))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				rowOption = 0;
			}
			else if (rowOption < 0)
			{
				rowOption = 0;
			}
			else if (rowOption > getNumRows())
			{
				rowOption = 0;
			}
		}

		for (int i = 1; i < rowOption; i++)
		{
			pRow = pRow->getRowPtr();
		}

		ColumnNode* pCol = pRow->getColPtr();

		while (!(pCol->getColVal()))
		{
			pCol = pCol->getColPtr();
		}

		scalar = (1 / pCol->getColVal());

		while (pCol)
		{
			pCol->setColVal((pCol->getColVal()) * scalar);
			pCol = pCol->getColPtr();
		}

	}
}

void Matrix::scaleAllToOne()
{
	RowNode* pRow = getMatrixPtr();
	double scalar = 0.0;

	if (!(pRow->getColPtr()))
	{
		cout << "Your matrix is empty." << endl;
		return;
	}
	else
	{
		for (int i = 0; i < getNumRows(); i++)
		{

			ColumnNode* pCol = pRow->getColPtr();

			while (!(pCol->getColVal()))
			{
				pCol = pCol->getColPtr();
			}

			scalar = (1 / pCol->getColVal());

			while (pCol)
			{
				pCol->setColVal((pCol->getColVal()) * scalar);
				pCol = pCol->getColPtr();
			}

			pRow = pRow->getRowPtr();
		}
	}
}

void Matrix::replaceRows()
{
	int rowSource = -1, rowDestination = -1;

	if (getNumRows() == 0)
	{
		cout << "Your matrix is empty." << endl;
		return;
	}

	cout << endl << "Enter row to use: ";

	while (rowSource == -1)
	{
		if (!(cin >> rowSource))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please try again." << endl;
		}
		if (rowSource > getNumRows())
		{
			cout << "Your matrix does not have that many rows." << endl;
			rowSource = -1;
		}
	}

	cout << endl << "Enter row to modify: ";

	while (rowDestination == -1)
	{
		if (!(cin >> rowDestination))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please try again." << endl;
		}
		if (rowDestination > getNumRows())
		{
			cout << "Your matrix does not have that many rows." << endl;
			rowDestination = -1;
		}
	}

	RowNode* rowSptr = getMatrixPtr(), *rowDptr = getMatrixPtr();
	ColumnNode* colSptr = nullptr, *colDptr = nullptr;
	int i = 0;

	for (i = 1; i < rowSource; i++)
	{
		rowSptr = rowSptr->getRowPtr();
	}

	for (i = 1; i < rowDestination; i++)
	{
		rowDptr = rowDptr->getRowPtr();
	}

	colSptr = rowSptr->getColPtr();
	colDptr = rowDptr->getColPtr();
	
	int useColumn = -1;
	double scalar = 0.0;

	while (useColumn == -1)
	{
		cout << endl << "Enter column to use: ";

		if (!(cin >> useColumn))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			useColumn = 0;
		}
		if (useColumn > mNumCols)
		{
			cout << "Your matrix does not have that many columns." << endl;
			useColumn = -1;
		}
	}

	for (i = 1; i < useColumn; i++)
	{
		colSptr = colSptr->getColPtr();
		colDptr = colDptr->getColPtr();
	}

	if (colSptr->getColVal() == 0)
	{
		cout << "The value in that cell is zero.  No change to matrix." << endl;
		return;
	}
	else
	{
		scalar = (colDptr->getColVal()) / (colSptr->getColVal());

		colSptr = rowSptr->getColPtr();
		colDptr = rowDptr->getColPtr();

		for (i = 0; i < mNumCols; i++)
		{
			colDptr->setColVal((colDptr->getColVal()) - scalar*(colSptr->getColVal()));
			colSptr = colSptr->getColPtr();
			colDptr = colDptr->getColPtr();
		}
	}
}

void Matrix::randomMatrix()
{
	inputMatrixSize();
	propagateRows();

	RowNode* pRow = mMatrixPtr;
	ColumnNode* pCol = nullptr;
	int rowCount = 1, colCount = 1;
	cout << endl;

	for (; rowCount <= mNumRows; rowCount++)
	{
		pCol = pRow->getColPtr();

		for (colCount = 1; colCount <= mNumCols; colCount++)
		{

					pCol->setColVal(makeRandomInt());
					pCol = pCol->getColPtr();
		}

		pRow = pRow->getRowPtr();
	}

}

int Matrix::makeRandomInt()
{

	int rando = rand() % 40 - 20;

	return rando;
}

double Matrix::makeRandomDouble()
{
	int numerator = rand() % 40 - 20;
	int denominator = rand() % 40 - 20;

	while (denominator == 0)
	{
		denominator = rand() % 40 - 20;
	}
	
	double rando = (double)numerator / denominator;

	return rando;
}

void Matrix::sortEchelon(int row, int column)
{
	RowNode* rowS = getMatrixPtr(), *rowD = getMatrixPtr();
	int j = 0;

	for (j = 1; j < row; j++)
	{
		rowS = rowS->getRowPtr();
		rowD = rowD->getRowPtr();
	}

	int k = j;

	ColumnNode* colS = rowS->getColPtr(), *colD = rowD->getColPtr(), *colTemp = nullptr;

	for (int i = 1; i < column; i++)
	{
		colS = colS->getColPtr();
		colD = colD->getColPtr();
	}
	if (colD->getColVal() == 1)
	{
		return;
	}
	else
	{
		while (rowS)
		{
			k++;
			rowS = rowS->getRowPtr();
			colS = rowS->getColPtr();
			if (colS->getColVal() == 1)
			{
				swapRows(j, k);
				return;
			}
		}
	}
}

void Matrix::rowReduce()
{
	for (int i = 1; i < mNumRows && i < mNumCols; i++)
	{
		sortEchelon(i, i);
	}
}

void Matrix::identityMatrix()
{
	int numRows = 0;
	bool verifyInput = false;

	while (!verifyInput)
	{
		cout << endl << "Enter size of desired identity matrix: ";

		if (!(cin >> numRows))
		{
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
		{
			setNumRows(numRows);
			setNumCols(numRows);
			cout << endl << "You are using an " << getNumRows() << " x " << getNumCols() << " identity matrix." << endl;
			verifyInput = true;
		}
	}

	propagateRows();

	for (int i = 0; i < getNumRows(); i++)
	{
		RowNode* rowSet = getMatrixPtr();
		ColumnNode* colSet = nullptr;
		
		for (int j = 1; j <= i; j++)
		{
			rowSet = rowSet->getRowPtr();
		}

		colSet = rowSet->getColPtr();

		for (int j = 1; j <= i; j++)
		{
			colSet = colSet->getColPtr();
		}

		colSet->setColVal(1);
	}

}
