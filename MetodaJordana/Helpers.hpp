#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>

#include "config.h"

using namespace std;


void PrintMatrix(double matrix[][4], int M, int N) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << std::setw(15) << matrix[i][j];
		}
		std::cout << std::endl;
	}
}

void PrintMatrixM(double matrix[][4], int M, int N, int x, int y, string msg) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (x == i && y == j) {
				std::ostringstream sstream;
				sstream << "{" << setprecision(4) << matrix[i][j] << "}" << msg;
				std::string out = sstream.str();
				std::cout << std::setw(15) << out;
			}
			else
				std::cout << std::setw(15) << setprecision(4) <<  matrix[i][j];
		}
		std::cout << std::endl;
	}
}

int reduceToDiagonal(double matrix[3][4], int m, int n) {
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
#ifdef ELO
						system("cls");
						ostringstream msg;
						msg << "-" << setprecision(0) << matrix[i][j] * multiplier;
						PrintMatrixM(matrix, m, n, k, j, msg.str());
						cout << "multiplier: " << multiplier << endl;
						cout << "first: " << matrix[i][j] << endl;
						cout << "multiplied: " << matrix[i][j] * multiplier << endl;
						_getch();
#endif // ELO
						matrix[k][j] -= matrix[i][j] * multiplier;
					}
				}
			}
		}
	}
	return br;
}

void reduceToUnit(double matrix[3][4], int m, int n) {
	for (int i = 0; i < m; i++)
	{
		double divider = matrix[i][i];
		
		if (divider != 0) 
		{
			for (int j = 0; j < n; j++)
			{
#ifdef ELO
				system("cls");
				ostringstream msg;
				msg << "\\" << setprecision(0) << divider;
				PrintMatrixM(matrix, m, n, i, j, msg.str());
				cout << "divider: " << divider << endl;
				_getch();
#endif // ELO
				matrix[i][j] /= divider;
			}
		}
	}
}