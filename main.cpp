#include "Matrix.h"

int main(int argc, char argv[])
{
	srand((unsigned int)time(NULL));

	Matrix a;

	while (a.getOperationMode() != 1)
	{
		a.runApp();
	}
	
	return 0;
}