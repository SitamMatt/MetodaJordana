#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstring>
#include <conio.h>

#include "Matrix.h"
 


using namespace std;


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
			std::cout << std::setw(15) << data[i][j];
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
			if (data[j][i] != 0) {
				swapRows(j, ordered);
				ordered++;
			}
		}
	}
}

void Matrix::swapRows(int index1, int index2)
{
	double *temp = data[index1];
	data[index1] = data[index2];
	data[index2] = temp;
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
	data = new double *[r];
	int x, y;
	ifstream in(path);

	if (!in) {
		cout << "Cannot open file.\n";
	}

	rows = r;
	cols = c;

	for (y = 0; y < r; y++) {
		data[y] = new double[c];
		for (x = 0; x < c; x++) {
			in >> data[y][x];
		}
	}

	in.close();
}

void Matrix::readFromFile(istream & file, int r, int c)
{
	data = new double *[r];
	int x, y;

	rows = r;
	cols = c;

	for (y = 0; y < r; y++) {
		data[y] = new double[c];
		for (x = 0; x < c; x++) {
			file >> data[y][x];
		}
	}
}

int Matrix::reduceToDiagonal()
{
	int br = 0;
	bool conflict = false;
	for (int i = 0; i < rows; i++)
	{
		if (data[i][i] == 0)
		{
			for (int o = 0; o < cols; o++)
			{
				if (data[o] != 0) conflict = true;
			}
			br++;
		}
		else
		{
			for (int k = 0; k < rows; k++)
			{
				if (k != i) {

					double multiplier = data[k][i] / data[i][i];

					for (int j = 0; j < cols; j++)
					{
						if (debuggerFlag) {
							system("cls");
							ostringstream msg;
							msg << "-" << setprecision(0) << data[i][j] * multiplier;
							printMarked(k, j, msg.str());
							cout << "multiplier: " << multiplier << endl;
							cout << "first: " << data[i][i] << endl;
							cout << "multiplied: " << data[i][j] * multiplier << endl;
							_getch();
						}
						
						data[k][j] -= data[i][j] * multiplier;
						data[k][j] = abs(data[k][j]);
					}
				}
			}
		}
	}
	if (conflict) return -1;
	return br;
}

void Matrix::reduceToUnit()
{
	for (int i = 0; i < rows; i++)
	{
		double divider = data[i][i];

		if (divider != 0)
		{
			for (int j = 0; j < cols; j++)
			{
				if (debuggerFlag) {
					system("cls");
					ostringstream msg;
					msg << "\\" << setprecision(0) << divider;
					printMarked(i, j, msg.str());
					cout << "divider: " << divider << endl;
					_getch();
				}
				data[i][j] /= divider;
			}
		}
	}
}

double *& Matrix::operator[](const int index)
{
	return data[index];
}




Matrix::~Matrix()
{
}
