#pragma once
#include<iostream>
#include<vector>
#include<iomanip>
#include<Windows.h>
#include<fstream>
#include<conio.h>
#include<io.h>
#include<fcntl.h>
#include<codecvt>
#include<string>
#include<sstream>
using namespace std;

const double eps = 0.0000001;

char GetMethodOfFilling();
void FillWithRandomNums(vector<vector<double>>& v, const int rows, const int cols, const int min, const int max);
void FillByKeyboard(vector<vector<double>>& v, const int rows, const int cols);
bool FillFromFile(vector<vector<double>>& v, const wstring path);
bool FillMatrix(vector<vector<double>>& v, const int method);
void Copy(vector<vector<double>>& In, vector<vector<double>>& Out);
void printRow(vector<vector<double>> mat, const int row);
void print(vector<vector<double>> mat);
void swap_rows(vector<vector<double>>& mat, int i, int j);
void mulRowOnSomeNum(vector<vector<double>>& mat, const int row, const double num);
void cleanLeadings(vector<vector<double>>& mat);
bool forwardElim(vector<vector<double>>& mat);
bool CanBeSolved(vector<vector<double>>& mat);
vector<double> gaussianElimination(vector<vector<double>>& mat);
void ShowAnswer(vector<double> x);
