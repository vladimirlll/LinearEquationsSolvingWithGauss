#pragma once
#include<iostream>
#include<fstream>
#include<windows.h>
#include<ctime>
#include<random>
#include<string>
#include<sstream>
#include<vector>
#include<conio.h>
#include<io.h>
#include<fcntl.h>
#include<codecvt>
using namespace std;

bool Has(const vector<int>A, const int num);
vector<wstring> Mix(const vector<wstring> A);
void GetTests(const string testPath, vector<vector<wstring>>& QA, vector<wstring>& correctAns, int& countOfAllQ, int& countOfAskingQ, wstring& lvlSelection);
void PrepareTestsForOut(vector<vector<wstring>>& QA, vector<wstring>& correctAns, const int countOfAllQ);
void GetRandomQ(const vector<vector<wstring>>& allQA, const vector<wstring>& allCorrectAns, vector<vector<wstring>>& resultQA, vector<wstring>& resultCorrectAns, const int qCount);
void GetSomeLvlQ(const vector<vector<wstring>>& allQA, const vector<wstring>& allCorrectAns, vector<vector<wstring>>& resultQA, vector<wstring>& resultCorrectAns, const wstring lvl);
void GetNecessaryQ(const vector<vector<wstring>>& allQA, const vector<wstring>& allCorrectAns, vector<vector<wstring>>& resultQA, vector<wstring>& resultCorrectAns, const int qCount, wstring lvlSelection);
bool IsAnswerCorrect(const wstring corAnsStr, const wstring userAnsStr);
