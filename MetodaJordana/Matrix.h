#pragma once
#include <string>
#include "decimal.h"

using namespace dec;
using namespace std;
//using liczba = decimal<20>;
using liczba = long double;


class Matrix
{
private:
	int cols;
	int rows;
	liczba ** data;
	bool debuggerFlag = false;
public:
	bool prepared = false;

	Matrix();
	Matrix(string path, int r, int c);
	void print();
	void printMarked(int x, int y, string msg);
	void orderRows();
	void swapRows(int index1, int index2);
	bool checkIndeterminacy();
	void debug();
	void stopDebugging();
	void readFromFile(string path, int r, int c);
	void readFromFile(istream &file, int r, int c);
	bool readFromFile(string path);
	int reduceToDiagonal();
	void reduceToUnit();
	liczba *& operator[] (const int index);


	~Matrix();
};

