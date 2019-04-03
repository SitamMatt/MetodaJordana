#include <iostream>
#include <iomanip>



void PrintMatrix(double matrix[][4], int M, int N) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << std::setw(10) << matrix[i][j] << "|";
		}
		std::cout << std::endl;
	}
}

void reduceToDiagonal(double matrix[3][4], int m, int n) {
	int br = 0;
	for (int i = 0; i < m; i++)
	{
		if (matrix[i][i] == 0)
		{
			br++;
		}
		else
		{
			for (int k = 0; k < m; k++)
			{
				if (k != i) {

					double multiplier = matrix[k][i] / matrix[i][i];

					for (int j = 0; j < n; j++)
					{
						matrix[k][j] -= matrix[i][j] * multiplier;
					}
				}
			}
		}
	}
	std::cout << br << std::endl;
	PrintMatrix(matrix, m, n);
}

void reduceToUnit(double matrix[3][4], int m, int n) {
	for (int i = 0; i < m; i++)
	{
		double divider = matrix[i][i];
		if (divider != 0) 
		{
			for (int j = 0; j < n; j++)
			{
				matrix[i][j] /= divider;
			}
		}
	}
}