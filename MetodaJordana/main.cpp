#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <fstream>

#include "cxxopts.hpp"

//#include "Helpers.hpp"
#include "config.hpp"
#include "Matrix.h"

using namespace std;

int main(int argc, char **argv) {
	// tutaj bêdzie wczytywanie z wiersza poleceñ pliku z macierz¹
	cxxopts::Options options_parser("MetodaJordana", "Program oblicza uklady rownan metoda elimiancji gaussa-jordana");
	options_parser.add_options()
		("h,help", "wyswietla ten komunikat")
		("d,debug", "tryb debugowania(operacje na macierzy sa pokazywane krok po kroku)")
		("f,file", "sciezka do pliku z macierza", cxxopts::value<std::string>())
		("i,interactive", "wprowadzenie danych z notepada")
		("r,rows", "liczba wierszy do wczytania", cxxopts::value<int>())
		("c,cols", "liczba kolumn do wczytania", cxxopts::value<int>());

	Matrix pietraszko;
	try
	{
		int r=-1, c=-1;
		auto options = options_parser.parse(argc, argv);

		if (options.count("help")) {
			cout << options_parser.help();
		}
		if (options.count("debug")) {
			pietraszko.debug();
		}
		if (options.count("file")) {
			if (options.count("r") && options.count("c")) {
				r = options["r"].as<int>();
				c = options["c"].as<int>();
				if (c == (r + 1)) {
					cout << "bledny wymiar tablicy" << endl;
				}
				string path = options["file"].as<string>();
				cout << "Reading from " << path << "..." << endl;
				pietraszko.readFromFile(path, r, c);
			}
			else {
				cout << "Musisz podaæ parametry `r` oraz `c` wraz z argumentami" << endl;
				exit(2);
			}
			
		}
		if (options.count("interactive")) {
			if (!(options.count("r") && options.count("c"))) {
				cout << "Otworzy sie plik w ktorym podasz wymiary macierzy a nastepnie wartosci, ostatnia liczba w lini bedzie wynikiem " << endl;
			}
			else {
				cout << "Otworzy sie plik w ktorym podasz wartosci wspolczynnikow rownania" << endl;
				r = options["r"].as<int>();
				c = options["c"].as<int>();
			}
			cout << "wymagany format: 3x4, 4x5, 5x6 ... do 10x11" << endl << "Disclaimer: wartosci rozdzielasz spacjami" << endl;
			system("pause");

			fstream cleaner;
			cleaner.open("macierze.txt", ios::out | ios::trunc); /*czyszcze pliku ze smieci*/
			cleaner.close();
			
			string plik;
			plik = "notepad \macierze";
			system(plik.c_str());
			cout << endl;
			system("pause");
			fstream dane;
			dane.open("macierze.txt");

			if (!(options.count("r") && options.count("c"))) {
				dane >> r;
				dane >> c;
			}
			if (c == (r + 1))
			{
				pietraszko.readFromFile(dane, r, c);
			}
			else
			{
				cout << "bledny wymiar tablicy" << endl;
			}
			dane.close();

		}
	}
	catch (const cxxopts::OptionException& e)
	{
		cout << options_parser.help();
		exit(1);
	}

	// obliczanie rozwiazan
	pietraszko.print();
	pietraszko.orderRows();
	cout << "Po uporzadkowaniu: " << endl;
	pietraszko.print();
	int info = pietraszko.reduceToDiagonal();
	if (info>0) {
		cout << "Uklad jest nieoznaczony... " << endl;
	}
	else if (info < 0) {
		cout << "Uklad jest sprzeczny... " << endl;
	}
	else {
		pietraszko.reduceToUnit();
		cout << "Macierz wynikowa: " << endl;
		pietraszko.print();
	}

	system("pause");
	return 0;
}
