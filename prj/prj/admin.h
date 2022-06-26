#pragma once
#include<iostream>
#include<fstream>
#include<windows.h>
#include<string>
#include<sstream>
#include<vector>
#include<iomanip>
#include<conio.h>
#include<io.h>
#include<fcntl.h>
#include<codecvt>
#include"theory.h"
#include"testing.h"
using namespace std;

int AdminMenu();

//администрирование теории
void ReadTheoryChap(const vector<vector<wstring>>& chapters, const int chap);
void AddHeaderRow(vector<vector<wstring>>& chapters, const int changingChap);
void AddTextRow(vector<vector<wstring>>& chapters, const int changingChap, const int rowNum);
void AddChapter(vector<vector<wstring>>& chapters, const int addingChapNum);
int ChooiceChapter(const vector<vector<wstring>> chapters);
int ChooiceRowOfChapForAdd(const vector<vector<wstring>> chapters, const int changingChap);
void ChooiceRowOfChapForChange(const vector<vector<wstring>> chapters, const int changingChap, int& beginRow, int& endRow);
int GetRowType(const vector<vector<wstring>>& chapters, const int changingChap, const int rowNum);
void DeleteRow(vector<vector<wstring>>& chapters, const int changingChap, const int deletingRow, const int rowType);
void ChangeRows(vector<vector<wstring>> &chapters, const int changingChap, const int beginRow, const int endRow);
void ChangeChapter(vector<vector<wstring>> &chapters, const int changingChap);
bool ChangeTheoryFile(const string theoryPath, vector<vector<wstring>> chapters);
bool ChangeTheory(const string theoryPath);
//\\администрирование теории

//администрирование тестирования
//void GetTests(const string testPath, vector<vector<wstring>>& QA, vector<wstring>& correctAns, int& countOfAllQ, int& countOfAskingQ, wstring& lvlSelection);
void AddQ(vector<vector<wstring>>& QA, vector<wstring>& correctAns, int& countOfAllQ);
void DeleteQ(vector<vector<wstring>>& QA, vector<wstring>& correctAns, int& countOfAllQ, const int deletingQ);
void MakeNewLines(wstring& Q);
void EditQ(vector<vector<wstring>>& QA, vector<wstring>& correctAns, const int countOfAllQ, const int editingQ);
bool OutToFile(const string testPath, const vector<vector<wstring>> QA, const vector<wstring> correctAns, const int countOfAllQ, const int countOfAskingQ, const wstring lvlSelection);
void ChangeTest(const string testPath);
void OutAllTest(vector<vector<wstring>> QA, vector<wstring> correctAns, const int countOfAllQ, const int countOfAskingQ, const wstring lvlSelection);
//\\администрирование тестирования