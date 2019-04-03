#include <iostream>
#include <stdlib.h>
#include <conio.h>

#include "Helpers.hpp"

using namespace std;



int main() {
	double mat[3][4] = {
		{1,-1,1, -4},
		{8,2.21,-5, -10},
		{4,1,1, 2}
	};
	int n = 3;
	PrintMatrix(mat, 3, 4);
	cout << endl << endl;


	for (int i = 0; i < n; i++) {

		// i,i element rownania
		double a = mat[i][i];
		// dzielenie wiersza przez jego i,i element
		for (int j = 0; j < 4; j++) {
			mat[i][j] /= a;
			/*system("cls");
			PrintMatrix(mat, 3, 4);
			_getch();*/
		}
		// odejmowanie wierszy i mnozenie
		for (int k = 0; k < n; k++) {
			

			// pomijamy wiersz obecny
			if (k != i) {
				//int wiers_razy_a[4];
				// mnozenie aktualnego wiersza przez k,i
				/*for (int l = 0; l < 4; l++) {
					wiers_razy_a[l] = mat[i][l] * mat[k][i];
				}*/
				double b = mat[k][i] / mat[i][i];
				// odejmowanie wiersza
				for (int m = 0; m < 4; m++) {
					mat[k][m] -= mat[i][m] * b;
					/*system("cls");
					PrintMatrix(mat, 3, 4);
					_getch();*/
				}
			}
		}
	}
	PrintMatrix(mat, 3, 4);

	system("pause");
	return 0;
}
