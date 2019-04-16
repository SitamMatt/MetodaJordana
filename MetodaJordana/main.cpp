#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <fstream>

#include "cxxopts.hpp"

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
			string path = options["file"].as<string>();
			if (options.count("r") && options.count("c")) {
				r = options["r"].as<int>();
				c = options["c"].as<int>();
				if (!(c == (r + 1))) {
					cout << "Bledny wymiar tablicy." << endl;
					cout << "Próba odczytu rozmiarów z pliku..." << endl;
					bool result = pietraszko.readFromFile(path);
					if (!result) {
						cerr << "Nie mo¿na odczytaæ wymiarów macierzy." << endl;
						exit(2);
					}
					pietraszko.prepared = true;
				}
				cout << "Reading from " << path << "..." << endl;
				pietraszko.readFromFile(path, r, c);
				pietraszko.prepared = true;
			}
			else {
				bool result = pietraszko.readFromFile(path);
				if (!result) exit(2);
				pietraszko.prepared = true;
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

			if (!(options.count("r") && options.count("c"))) {
				bool result = pietraszko.readFromFile("macierze.txt");
				if (!result) exit(2);
				pietraszko.prepared = true;
			}
			else if (c == (r + 1))
			{
				pietraszko.readFromFile("macierze.txt", r, c);
				pietraszko.prepared = true;
			}
			else
			{
				//cout << "Bledny wymiar tablicy." << endl;
				cout << "Próba odczytu rozmiarów z pliku..." << endl;
				bool result = pietraszko.readFromFile("macierze.txt");
				if (!result) {
					cerr << "Nie mo¿na odczytaæ wymiarów macierzy." << endl;
					exit(2);
				}
				pietraszko.prepared = true;
			}
		}
	}
	catch (const cxxopts::OptionException& e)
	{
		cout << options_parser.help();
		exit(1);
	}


	// obliczanie rozwiazan
	if (pietraszko.prepared) {

		pietraszko.print();
		pietraszko.orderRows();
		cout << "Po uporzadkowaniu: " << endl;
		pietraszko.print();
		int info = pietraszko.reduceToDiagonal();
		if (info) {
			bool inder = pietraszko.checkIndeterminacy();
			if (inder) {
				cout << "Uklad jest nieoznaczony... " << endl;
				pietraszko.print();
			}
			else {
				cout << "Uklad jest sprzeczny... " << endl;
			}
		}
		else {
			pietraszko.reduceToUnit();
			cout << "Macierz wynikowa: " << endl;
			pietraszko.print();
		}
	}
	else {
		cout << options_parser.help();
	}

	system("pause");
	return 0;
}
