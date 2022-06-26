#include "testing.h"

bool Has(const vector<int> A, const int num)
{
	int Asize = A.size();
	for (int i = 0; i < Asize; i++)
	{
		if (A[i] == num)
			return true;
	}
	return false;
}

vector<wstring> Mix(const vector<wstring> A)
{
	int Asize = A.size();
	vector<int> mentioned;
	vector<wstring> mixed;
	for (int i = 0; i < Asize; i++)
	{
		int generatedIndex;
		do
		{
			generatedIndex = rand() % Asize;
		} while (Has(mentioned, generatedIndex));
		mixed.push_back(A[generatedIndex]);
		mentioned.push_back(generatedIndex);
	}
	return mixed;
}

void GetTests(const string testPath, vector<vector<wstring>>& QA, vector<wstring>& correctAns, int& countOfAllQ, int& countOfAskingQ, wstring& lvlSelection)
{
	wifstream fin("test.txt");
	fin.imbue(std::locale(locale::empty(), new codecvt_utf8<wchar_t>));
	QA.resize(3);
	wstring counterNLevel;
	getline(fin, counterNLevel);
	wstringstream counterS;
	counterS << counterNLevel;
	counterS >> countOfAskingQ >> lvlSelection;
	wstring currentLvl; //строка с уровнем для текущего вопроса
	wstring row; //строка вопроса
	wstring variants; //строка вариантов ответа
	wstring corAns; //строка правильного ответа
	int index = 0;
	while (getline(fin, row)) //получение вопроса
	{
		QA[0].resize(index + 1);
		QA[1].resize(index + 1);
		QA[2].resize(index + 1);
		wchar_t lastSymbolOfRow = row.back();
		if (lastSymbolOfRow == L'#')
		{
			getline(fin, variants); //получение вариантов ответа
			getline(fin, corAns); //получение правильного ответа
			correctAns.push_back(corAns);
			QA[1][index] = variants;
			QA[0][index] += row;

			getline(fin, currentLvl);
			QA[2][index] = currentLvl;
			index++;
		}
		else
		{
			QA[0][index] += row;
			QA[0][index] += L'\n';
		}
	}
	countOfAllQ = QA[0].size();
}

void PrepareTestsForOut(vector<vector<wstring>>& QA, vector<wstring>& correctAns, const int countOfAllQ)
{
	for (int i = 0; i < countOfAllQ; i++)
	{
		vector<wstring> variantsTemp;
		wstring variants = QA[1][i];

		wstring delim = L"&";
		int prev = 0;
		int next;
		int delta = delim.length();

		while ((next = variants.find(delim, prev)) != string::npos)
		{
			wstring tmp = variants.substr(prev, next - prev);
			variantsTemp.push_back(tmp); //получение разделенных вариантов
			prev = next + delta;
		}
		wstring tmp = variants.substr(prev);
		variantsTemp.push_back(tmp); //получение разделенных вариантов

		variants = L"";
		int variantsCount = variantsTemp.size();
		bool numOfCorAnsFound = false;
		int s = 0;
		while (s < variantsCount && !numOfCorAnsFound)
		{
			if (variantsTemp[s] == correctAns[i])
			{
				numOfCorAnsFound = true;
				wstringstream tempStream;
				tempStream << (s + 1);
				tempStream >> correctAns[i];
			}
			s++;
		}
		for (int i = 0; i < variantsCount; i++)
		{
			wstringstream s2;
			wstring temp;
			s2 << (i + 1);
			s2 >> temp;
			variants += temp;
			variants += L". ";
			variants += variantsTemp[i];
			variants += L'\n';
		}

		QA[1][i] = variants;
		QA[0][i].resize(QA[0][i].size() - 1);
		QA[0][i] += L'\n';
	}
}

void Testing(const string testPath, vector<vector<wstring>>& QA, vector<wstring>& correctAns, int& countOfAllQ, int &countOfAskingQ, wstring &lvlSelection)
{
	wifstream fin("test.txt");
	fin.imbue(std::locale(locale::empty(), new codecvt_utf8<wchar_t>));
	QA.resize(3);
	wstring counterNLevel;
	getline(fin, counterNLevel);
	wstringstream counterS;
	counterS << counterNLevel;
	counterS >> countOfAskingQ >> lvlSelection;
	wstring currentLvl; //строка с уровнем для текущего вопроса
	wstring row; //строка вопроса
	wstring variants; //строка вариантов ответа
	wstring corAns; //строка правильного ответа
	int index = 0;
	while (getline(fin, row)) //получение вопроса
	{
		QA[0].resize(index + 1);
		QA[1].resize(index + 1);
		QA[2].resize(index + 1);
		wchar_t lastSymbolOfRow = row.back();
		if (lastSymbolOfRow == L'#')
		{
			getline(fin, variants); //получение вариантов ответа
			vector<wstring> variantsTemp;

			wstring delim = L"&";
			int prev = 0;
			int next;
			int delta = delim.length();

			while ((next = variants.find(delim, prev)) != string::npos) 
			{
				wstring tmp = variants.substr(prev, next - prev);
				variantsTemp.push_back(tmp); //получение разделенных вариантов
				prev = next + delta;
			}
			wstring tmp = variants.substr(prev);
			variantsTemp.push_back(tmp); //получение разделенных вариантов

			variantsTemp = Mix(variantsTemp); //перемешивание

			getline(fin, corAns); //получение правильного ответа

			variants = L"";
			int variantsCount = variantsTemp.size();
			bool numOfCorAnsFound = false;
			int i = 0;
			while (i < variantsCount && !numOfCorAnsFound)
			{
				if (variantsTemp[i] == corAns)
				{
					numOfCorAnsFound = true;
					wstringstream tempStream;
					tempStream << (i + 1);
					tempStream >> corAns;
				}
				i++;
			}
			correctAns.push_back(corAns);
			for (int i = 0; i < variantsCount; i++)
			{
				wstringstream s2;
				wstring temp;
				s2 << (i + 1);
				s2 >> temp;
				variants += temp;
				variants += L". ";
				variants += variantsTemp[i];
				variants += L'\n';
			}
			QA[1][index] = variants;
			row.resize(row.size() - 1);
			QA[0][index] += row;
			QA[0][index] += L'\n';

			getline(fin, currentLvl);
			QA[2][index] = currentLvl;
			index++;
		}
		else
		{
			QA[0][index] += row;
			QA[0][index] += L'\n';
		}
	}
	countOfAllQ = QA[0].size();
}

void GetRandomQ(const vector<vector<wstring>>& allQA, const vector<wstring>& allCorrectAns, vector<vector<wstring>>& resultQA, vector<wstring>& resultCorrectAns, const int qCount)
{
	resultQA.resize(3);
	int QAcount = allQA[0].size();
	vector<int> mentioned;
	for (int i = 0; i < qCount; i++)
	{
		int generatedIndex;
		do
		{
			generatedIndex = rand() % QAcount;
		} while (Has(mentioned, generatedIndex));
		mentioned.push_back(generatedIndex);
		resultQA[0].push_back(allQA[0][generatedIndex]);
		resultQA[1].push_back(allQA[1][generatedIndex]);
		resultQA[2].push_back(allQA[2][generatedIndex]);
		resultCorrectAns.push_back(allCorrectAns[generatedIndex]);
	}
}

void GetSomeLvlQ(const vector<vector<wstring>>& allQA, const vector<wstring>& allCorrectAns, vector<vector<wstring>>& resultQA, vector<wstring>& resultCorrectAns, const wstring lvl)
{
	resultQA.resize(3);
	int QAcount = allQA[0].size();
	for (int i = 0; i < QAcount; i++)
	{
		if (allQA[2][i] == lvl)
		{
			resultQA[0].push_back(allQA[0][i]);
			resultQA[1].push_back(allQA[1][i]);
			resultQA[2].push_back(allQA[2][i]);
			resultCorrectAns.push_back(allCorrectAns[i]);
		}
	}
}

void GetNecessaryQ(const vector<vector<wstring>>& allQA, const vector<wstring>& allCorrectAns, vector<vector<wstring>>& resultQA, vector<wstring>& resultCorrectAns, const int qCount, wstring lvlSelection)
{
	if (lvlSelection == L"4")
		GetRandomQ(allQA, allCorrectAns, resultQA, resultCorrectAns, qCount);
	else
		GetSomeLvlQ(allQA, allCorrectAns, resultQA, resultCorrectAns, lvlSelection);
}

bool IsAnswerCorrect(const wstring corAnsStr, const wstring userAnsStr)
{
	vector<wstring> allCorAns;
	wistringstream s1(corAnsStr);
	wstring String;
	while (s1 >> String)
		allCorAns.push_back(String);
	String = L"";
	vector<wstring> allUserAns;
	wistringstream s2(userAnsStr);
	while (s2 >> String)
		allUserAns.push_back(String);
	int allUserAnswersCount = allUserAns.size();
	int allCorrectAnswersCount = allCorAns.size();
	if (allCorrectAnswersCount != allUserAnswersCount)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < allUserAnswersCount; i++)
		{
			wstring userAns = allUserAns[i];
			int j = 0;
			while (j < allCorrectAnswersCount && userAns != allCorAns[j])
				j++;
			if (j == allCorrectAnswersCount)
				return false;
		}
		return true;
	}
}
