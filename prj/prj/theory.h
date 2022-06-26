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
using namespace std;

vector<vector<wstring>> GetChapters(const string theoryPath);
void ReadTheory(const vector<vector<wstring>>& chapters);