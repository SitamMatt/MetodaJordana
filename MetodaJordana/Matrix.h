#pragma once
#include <string>

using namespace std;


class Matrix
{
private:
	int cols;
	int rows;
	double ** data;
	bool debuggerFlag = false;
public:
	Matrix();
	Matrix(string path, int r, int c);
	void print();
	void printMarked(int x, int y, string msg);
	void orderRows();
	void swapRows(int index1, int index2);
	void debug();
	void stopDebugging();
	void readFromFile(string path, int r, int c);
	void readFromFile(istream &file, int r, int c);
	int reduceToDiagonal();
	void reduceToUnit();
	double*& operator[] (const int index);


	~Matrix();
};

