#include <iostream>
#include <iomanip>

void PrintMatrix(double matrix[][4], int M, int N) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << std::setw(10) << matrix[i][j] << "||||";
		}
		std::cout << std::endl;
	}
}