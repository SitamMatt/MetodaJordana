#include <iostream>
#include <stdlib.h>
#include <conio.h>

#include "cxxopts.hpp"

#include "Helpers.hpp"

using namespace std;

int main(int argc, char **argv) {
	// tutaj bêdzie wczytywanie z wiersza poleceñ pliku z macierz¹
	/*cxxopts::Options options("MetodaJordana", "Program oblicza uklady rownan metoda elimiancji gaussa-jordana");
	options.add_options()
		("d,debug", "tryb debugowania(operacje na macierzy sa pokazywane krok po kroku)")
		("h,help", "wyswietla ten komunikat");


	auto opts = options.parse(argc, argv);

	if (opts.count("help")) {
		cout << options.help();
	}*/

	double mat[3][4] = {
		{3,3,1, 1},
		{2,5, 7,20},
		{-4,-10,-14, -20},
	};
	int n = 3;
	PrintMatrix(mat, 3, 4);
	cout << endl << endl;
	int nieoznacz = reduceToDiagonal(mat, 3, 4);
	if (nieoznacz>0) {
		// jest nieoznaczona
		cout << "Uklad jest nieoznaczony... " << endl << "Rownania pokrywajace sie: " << nieoznacz << endl;
		PrintMatrix(mat, 3, 4);
	}
	else if (nieoznacz < 0) {
		cout << "Uklad jest sprzeczny... " << endl;
		PrintMatrix(mat, 3, 4);
	}
	else {
		reduceToUnit(mat, 3, 4);
		PrintMatrix(mat, 3, 4);
	}


	system("pause");
	return 0;
}
