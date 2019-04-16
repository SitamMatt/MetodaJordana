#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstring>
#include <conio.h>

#include "decimal.h"

#include "Matrix.h"
 

using namespace dec;
using namespace std;
//using liczba = decimal<20>;
using liczba = long double;
liczba zero() {
	//return decimal_cast<20>(0);
	return 0.0;
}
Matrix::Matrix()
{
}

Matrix::Matrix(string path, int r, int c)
{
	readFromFile(path, r, c);
}

void Matrix::print()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			liczba number = abs(data[i][j]) < 0.000000000001 ? abs(data[i][j]) : data[i][j];
			std::cout << setw(7) << setprecision(4) << fixed << number/*.getAsDouble()*/ << " ";
		}
		std::cout << std::endl;
	}
}

void Matrix::printMarked(int x, int y, string msg)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (x == i && y == j) {
				std::ostringstream sstream;
				sstream << "{" << setprecision(4) << data[i][j] << "}" << msg;
				std::string out = sstream.str();
				std::cout << std::setw(15) << out;
			}
			else
				std::cout << std::setw(15) << setprecision(4) << data[i][j];
		}
		std::cout << std::endl;
	}
}

void Matrix::orderRows()
{
	int ordered = 0;
	for (int i = 0; i < cols-1; i++)
	{
		for (int j = ordered; j < rows; j++)
		{
			if (data[j][i] != zero()) {
				swapRows(j, ordered);
				ordered++;
			}
		}
	}
}

void Matrix::swapRows(int index1, int index2)
{
	liczba *temp = data[index1];
	data[index1] = data[index2];
	data[index2] = temp;
}

bool Matrix::checkIndeterminacy()
{
	liczba suma;
	bool flag = false;

	for (int i = 0; i < rows; i++)
	{
		suma = 0;
		int j = 0;
		for (; j < rows; j++)
		{
			suma += data[i][j];
		}
		if (suma == data[i][j])
			flag = true;
	}
	return flag;
}

void Matrix::debug()
{
	debuggerFlag = true;
}

void Matrix::stopDebugging()
{
	debuggerFlag = false;
}

void Matrix::readFromFile(string path, int r, int c)
{
	data = new liczba *[r];
	int x, y;
	ifstream in(path);

	if (!in) {
		cout << "Cannot open file.\n";
	}

	rows = r;
	cols = c;

	for (y = 0; y < r; y++) {
		data[y] = new liczba[c];
		for (x = 0; x < c; x++) {
			in >> data[y][x];
		}
	}

	in.close();
}

void Matrix::readFromFile(istream & file, int r, int c)
{
	data = new liczba *[r];
	int x, y;

	rows = r;
	cols = c;

	for (y = 0; y < r; y++) {
		data[y] = new liczba[c];
		for (x = 0; x < c; x++) {
			file >> data[y][x];
		}
	}
}

bool Matrix::readFromFile(string path)
{
	ifstream in(path);
	in >> rows;
	in >> cols;
	if (!(cols == (rows + 1))) {
		cout << "bledny wymiar tablicy" << endl;
		return false;
	}
	data = new liczba *[rows];
	int x, y;

	if (!in) {
		cout << "Cannot open file.\n";
	}

	for (y = 0; y < rows; y++) {
		data[y] = new liczba[cols];
		for (x = 0; x < cols; x++) {
			in >> data[y][x];
		}
	}
	in.close();
	return true;
}

int Matrix::reduceToDiagonal()
{
	int c;
	int flag = false;
	int m = 0;
	liczba multiplier = 0;
	for (int i = 0; i < rows; i++)
	{
		if (abs(data[i][i]) < 0.0000000001)
		{
			c = 1;
			while ((i + c) < rows && abs(data[i + c][i]) < 0.0000000001)
				c++;
			if ((i + c) == rows) {
				flag = 1;
				break;
			}
			for (int j=1,k=0;k<=rows;k++)
			{
				liczba temp = data[j][k];
				data[j][k] = data[j + c][k];
				data[j + c][k] = temp;
			}
		}
		for (int j=0;j<rows;j++)
		{
			if (i != j) {

				multiplier = data[j][i] / data[i][i];

				for (int k = 0; k <= rows; k++)
				{
					if (debuggerFlag) {
						system("cls");
						ostringstream msg;
						msg << "-" << setprecision(0) << data[i][k] * multiplier;
						printMarked(k, j, msg.str());
						cout << "multiplier: " << multiplier << endl;
						cout << "first: " << data[i][i] << endl;
						cout << "multiplied: " << data[i][k] * multiplier << endl;
						_getch();
					}

					data[j][k] -= data[i][k] * multiplier;
				}
			}
		}
	}
	return flag;
}

void Matrix::reduceToUnit()
{
	for (int i = 0; i < rows; i++)
	{
		liczba divider = data[i][i];
		if (debuggerFlag) {
			system("cls");
			ostringstream msg;
			msg << "\\" << setprecision(0) << divider;
			printMarked(i, rows, msg.str());
			cout << "divider: " << divider << endl;
			_getch();
		}
		data[i][rows] /= divider;
		if (debuggerFlag) {
			system("cls");
			ostringstream msg;
			msg << "\\" << setprecision(0) << divider;
			printMarked(i, i, msg.str());
			cout << "divider: " << divider << endl;
			_getch();
		}
		data[i][i] /= divider;
	}
		

		
		
}

liczba *& Matrix::operator[](const int index)
{
	return data[index];
}




Matrix::~Matrix()
{
}
