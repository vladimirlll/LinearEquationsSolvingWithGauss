#include "admin.h"
#include "theory.h"
using namespace std;

int AdminMenu()
{
	char chooice;
	do
	{
		wcout << L"�������� ��������, ������� ������ ���������: " << endl;
		wcout << L"1. �������� ���� � ������������� ����������." << endl;
		wcout << L"2. ��������� ������������." << endl;
		wcout << L"0. ������ �� ������." << endl;
		wcout << L"������� ����� ��������: ";
		chooice = _getch();
	} while (chooice < '0' || chooice > '2');
	return (chooice-48);
}

//����������������� ������

void ReadTheoryChap(const vector<vector<wstring>>& chapters, const int chap)
{
	wcout << L"����� " << chap + 1 << L": " << endl;
	int rowsCountOfChap = chapters[chap].size();
	for (int j = 0; j < rowsCountOfChap; j++)
	{
		int rowSize = chapters[chap][j].size();
		wchar_t ch;
		bool termin = false;
		for (int s = 0; s < rowSize; s++)
		{
			ch = chapters[chap][j][s];
			if (ch != L'&')
			{
				wcout << ch;
			}
			else
			{
				termin = !termin;
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				if (termin)
				{
					SetConsoleTextAttribute(hConsole, 12);
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 15);
				}
			}
		}
	}
	wcout << endl;
	system("pause");
}

void AddHeaderRow(vector<vector<wstring>>& chapters, const int addingChap)
{
	wstring headerContent;
	wcout << L"������� ��������� �����: " << endl;
	getline(wcin, headerContent);
	wstring resultHeader = L"		&";
	resultHeader += headerContent;
	resultHeader += L'&';
	chapters[addingChap].push_back(resultHeader);
}

void AddTextRow(vector<vector<wstring>>& chapters, const int addingChap, const int rowNum)
{
	wstring newRow;
	wcout << L"������� ����� ������ ��� ����������: " << endl;
	getline(wcin, newRow);
	chapters[addingChap].insert(chapters[addingChap].begin() + rowNum, newRow);
}

void AddChapter(vector<vector<wstring>>& chapters, const int addingChapNum)
{
	vector<wstring> newChapter;
	chapters.insert(chapters.begin() + addingChapNum, newChapter);
	AddHeaderRow(chapters, addingChapNum);
	int go_on = 1;
	char temp;
	wcout << L"������� 0, ����� ��������� ��������� ����� �����, ����� ������ ����� - ����������: ";
	temp = _getch();
	go_on = temp - 48;
	int addingRow = 1;
	while (go_on != 0)
	{
		chapters[addingChapNum].resize(addingRow + 1);
		AddTextRow(chapters, addingChapNum, addingRow);
		addingRow++;
		wcout << L"������� 0, ����� ��������� ��������� ����� �����, ����� ������ ����� - ����������: ";
		temp = _getch();
		go_on = temp - 48;
	}
	chapters[addingChapNum][addingRow - 1] += L'#';
	system("cls");
	wcout << L"����� ����� �������: " << endl;
	ReadTheoryChap(chapters, addingChapNum);
}

int ChooiceChapter(const vector<vector<wstring>> chapters)
{
	int pagesCount = chapters.size();
	for (int i = 0; i < pagesCount; )
	{
		wcout << L"����� " << i + 1 << L": " << endl;
		int rowsCountOfChap = chapters[i].size();
		for (int j = 0; j < rowsCountOfChap; j++) //���� ������ �����
		{
			int rowSize = chapters[i][j].size();
			wchar_t ch;
			bool termin = false;
			for (int s = 0; s < rowSize; s++)
			{
				ch = chapters[i][j][s];
				if (ch != L'&')
				{
					wcout << ch;
				}
				else
				{
					termin = !termin;
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					if (termin)
					{
						SetConsoleTextAttribute(hConsole, 12);
					}
					else
					{
						SetConsoleTextAttribute(hConsole, 15);
					}
				}
			}
		}
		bool changed = false;
		int temp;
		while (!changed)
		{
			do
			{
				do
				{
					wcout << L"������� <-, ����� ��������� �� ���� ����� �����, -> - ����� ������� �� ���� ����� ������," << endl;
					wcout << L"ENTER - ����� ������� ����� ��� ��������� ��� ���������� ����� �� �� �����: ";
					temp = _getch();
				} while (temp != 13 && temp != 224);
				if (temp == 224)
					temp = _getch();
			} while (temp != 13 && temp != 75 && temp != 77);
			wcout << endl;
			if (temp == 75)
			{
				if (i == 0)
				{
					wcout << L"������ ������� �� ����� �����, ��� ��� ��� ������ �����." << endl;
				}
				else
				{
					i--;
					changed = true;
				}
			}
			else if (temp == 77)
			{
				if (i == (pagesCount - 1))
				{
					wcout << L"������ ������� �� ��������� �����, ��� ��� ��� ��������� �����." << endl;
				}
				else
				{
					i++;
					changed = true;
				}
			}
			else
			{
				return i;
			}
		}
		system("cls");
	}
}

int ChooiceRowOfChapForAdd(const vector<vector<wstring>> chapters, const int changingChap)
{
	int result;
	wcout << L"����� " << changingChap + 1 << L": " << endl;
	int rowsCountOfChap = chapters[changingChap].size();
	for (int j = 1; j < rowsCountOfChap; j++) //���� ������ �����
	{
		int rowSize = chapters[changingChap][j].size();
		wchar_t ch;
		bool termin = false;
		wcout << j + 1 << ". ";
		for (int s = 0; s < rowSize; s++)
		{
			ch = chapters[changingChap][j][s];
			if (ch != L'&')
			{
				wcout << ch;
			}
			else
			{
				termin = !termin;
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				if (termin)
				{
					SetConsoleTextAttribute(hConsole, 12);
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 15);
				}
			}
		}
	}
	do
	{
		wcout << L"������� ����� ������ �����, �� ����� ������� ������ �������� ����� (��� ���������� � ����� �����, ������� " << rowsCountOfChap + 1 << ") ";
		wcout << L"����� ������ �� ���������, ������� -1: ";
		wcin >> result;
	} while (result < 2 || result > (rowsCountOfChap+1) || result != -1);
	return result;
}

void ChooiceRowOfChapForChange(const vector<vector<wstring>> chapters, const int changingChap, int &beginRow, int &endRow)
{
	wcout << L"����� " << changingChap + 1 << L": " << endl;
	int rowsCountOfChap = chapters[changingChap].size();
	for (int j = 0; j < rowsCountOfChap; j++) //���� ������ ��������
	{
		int rowSize = chapters[changingChap][j].size();
		wchar_t ch;
		bool termin = false;
		wcout << j + 1 << ". ";
		for (int s = 0; s < rowSize; s++)
		{
			ch = chapters[changingChap][j][s];
			if (ch != L'&')
			{
				wcout << ch;
			}
			else
			{
				termin = !termin;
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				if (termin)
				{
					SetConsoleTextAttribute(hConsole, 12);
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 15);
				}
			}
		}
	}
	do
	{
		wcout << L"������� ����� ��������� ������ ����� ��� ���������: ";
		wcin >> beginRow;
	} while (beginRow < 1 || beginRow > rowsCountOfChap);
	beginRow -= 1;
	do
	{
		wcout << L"������� ����� �������� ������ ����� ��� ���������: ";
		wcin >> endRow;
	} while (endRow < beginRow || beginRow > rowsCountOfChap);
	endRow -= 1;
}

int GetRowType(const vector<vector<wstring>>& chapters, const int changingChap, const int rowNum)
{
	if (rowNum == (chapters[changingChap].size()-1))
	{
		return 0;
	}
	else
	{
		int rowSize = chapters[changingChap][rowNum].size();
		wchar_t lastSymbolOfRow = chapters[changingChap][rowNum][rowSize - 1];
		if (lastSymbolOfRow == L'\n')
		{
			lastSymbolOfRow = chapters[changingChap][rowNum][rowSize - 2];
		}
		if (lastSymbolOfRow == L'&')
			return 1;
		else
			return 2;
	}
}

void DeleteRow(vector<vector<wstring>>& chapters, const int changingChap, const int deletingRow, const int rowType)
{
	if (rowType == 0)
	{
		if (chapters[changingChap].size() > 2)
		{
			chapters[changingChap][deletingRow - 1] += L'#';
			chapters[changingChap].pop_back();
		}
		else
		{
			chapters[changingChap].pop_back();
		}
	}
	else
	{
		vector<wstring>::iterator it = chapters[changingChap].begin() + deletingRow;
		chapters[changingChap].erase(it);
	}
}

void ChangeRows(vector<vector<wstring>> &chapters, const int changingChap, const int beginRow, const int endRow)
{
	if (beginRow != endRow)
	{
		wcout << L"������ �" << beginRow + 1 << L" �� " << endRow + 1 << L" ����� �" << changingChap << L":" << endl;
	}
	else
	{
		wcout << L"������ �" << beginRow + 1 << L" ����� �" << changingChap << L":" << endl;
	}
	for (int i = beginRow; i <= endRow; i++)
	{
		int rowType = GetRowType(chapters, changingChap, i); //0 - ����� �����, 1 - ���������, 2 - ������ ������ ������
		
		wcout << chapters[changingChap][i] << endl;
		wcout << L"������� ����� ��� ��������� " << i + 1 << L" ������, ������������ ����. ����� (&, #) �� �����." << endl;
		wstring newRow;
		wcin.ignore();
		getline(wcin, newRow);
		if (newRow.empty())
		{
			DeleteRow(chapters, changingChap, i, rowType);
		}
		else
		{
			if (rowType == 0 || rowType == 2)
			{
				chapters[changingChap][i] = newRow;
			}
			else
			{
				chapters[changingChap][i] = L"		&";
				chapters[changingChap][i] += newRow;
				chapters[changingChap][i] += L"&\n";
			}
		}
	}
}

void ChangeChapter(vector<vector<wstring>> &chapters, const int changingChap)
{
	char temp;
	int changeOrAdd;
	do
	{
		wcout << L"1. �������� ������������ ������." << endl;
		wcout << L"2. �������� ����� ������." << endl;
		wcout << L"������� ����� ��������: ";
		temp = _getch();
		changeOrAdd = temp - 48;
	} while (changeOrAdd < 1 || changeOrAdd > 2);
	system("cls");
	if (changeOrAdd == 1)
	{
		int beginRow, endRow;
		ChooiceRowOfChapForChange(chapters, changingChap, beginRow, endRow);
		ChangeRows(chapters, changingChap, beginRow, endRow);
	}
	else
	{
		char go_on;
		do
		{
			ReadTheoryChap(chapters, changingChap);
			wcout << L"������� 0, ����� �������� ����� ������, ����� ������ ����� - ����� ����������� ����� �����." << endl;
			go_on = _getch();
		} while (go_on != '0');
		int addingRowNum;
		do
		{
			addingRowNum = ChooiceRowOfChapForAdd(chapters, changingChap);
			AddTextRow(chapters, changingChap, addingRowNum);
		} while (addingRowNum != -1);
	}
	system("cls");
	wcout << L"����� ����� �������: " << endl;
	ReadTheoryChap(chapters, changingChap);
}


bool ChangeTheoryFile(const string theoryPath, vector<vector<wstring>> chapters)
{
	wofstream fout(theoryPath);
	fout.imbue(std::locale(locale::empty(), new codecvt_utf8<wchar_t>));
	if (fout)
	{
		int chaptersCount = chapters.size();
		for (int i = 0; i < chaptersCount; i++)
		{
			int rowsCount = chapters[i].size();
			for (int j = 0; j < (rowsCount - 1); j++)
			{
				fout << chapters[i][j];
			}
			int lastRowSize = chapters[i][rowsCount - 1].size();
			if (chapters[i][rowsCount - 1][lastRowSize - 1] == '\n')
			{
				chapters[i][rowsCount - 1][lastRowSize - 1] = '#';
				chapters[i][rowsCount - 1] += L"\n";
			}
			else
				chapters[i][rowsCount - 1] += L"#\n";
			fout << chapters[i][rowsCount - 1];
		}
		return true;
	}
	return false;
}

bool ChangeTheory(const string theoryPath)
{
	vector<vector<wstring>> chapters = GetChapters(theoryPath);
	char temp;
	int changeOrAdd;
	do
	{
		wcout << L"1. �������� ������������ �����." << endl;
		wcout << L"2. �������� ����� �����." << endl;
		wcout << L"������� ����� ��������: ";
		temp = _getch();
		changeOrAdd = temp - 48;
	} while (changeOrAdd < 1 || changeOrAdd > 2);
	system("cls");
	if (changeOrAdd == 1)
	{
		int changingChap = ChooiceChapter(chapters);
		ChangeChapter(chapters, changingChap);
	}
	else
	{
		int addingChap = ChooiceChapter(chapters);
		AddChapter(chapters, addingChap);
	}
	if (ChangeTheoryFile(theoryPath, chapters))
		return true;
	return false;
}

//\\����������������� ������

//����������������� ������������

void AddQ(vector<vector<wstring>>& QA, vector<wstring>& correctAns, int& countOfAllQ)
{
	countOfAllQ++;
	QA[0].resize(countOfAllQ);
	QA[1].resize(countOfAllQ);
	QA[2].resize(countOfAllQ);
	correctAns.resize(countOfAllQ);
	wstring Q, destructors, corAns, lvl;
	wcout << L"������� ����� ������� (������� \'\\n\' ��� �������� �� ����� ������ � �����): " << endl;
	wcin.ignore();
	getline(wcin, Q);
	Q += '#';
	QA[0][countOfAllQ - 1] = Q;
	wcout << L"������� �����������, �������� �� ������ &: " << endl;
	getline(wcin, destructors);
	QA[1][countOfAllQ - 1] = destructors;
	do
	{
		wcout << L"������� ������� ��������� ������� (1, 2 ��� 3): ";
		wcin >> lvl;
	} while (lvl != L"1" && lvl != L"2" && lvl != L"3");
	QA[2][countOfAllQ - 1] = lvl;
	wcout << L"������� ���������� ����� �� ������ ������: " << endl;
	wcin.ignore();
	getline(wcin, corAns);
	correctAns[countOfAllQ - 1] = corAns;
}

void DeleteQ(vector<vector<wstring>>& QA, vector<wstring>& correctAns, int& countOfAllQ, const int deletingQ)
{
	QA[0].erase(QA[0].begin() + (deletingQ - 1));
	QA[1].erase(QA[1].begin() + (deletingQ - 1));
	QA[2].erase(QA[2].begin() + (deletingQ - 1));
	correctAns.erase(correctAns.begin() + (deletingQ - 1));
	countOfAllQ--;
}

void MakeNewLines(wstring& Q)
{
	int qSize = Q.size();
	for (int i = 0; i < qSize; i++)
	{
		if (Q[i] == '&')
			Q[i] = '\n';
	}
}

void EditQ(vector<vector<wstring>>& QA, vector<wstring>& correctAns, const int countOfAllQ, const int editingQ)
{
	wstring Q, destructors, corAns, lvl;
	char way;
	do
	{
		wcout << L"1. �������� ����� �������." << endl;
		wcout << L"2. �������� �������� ������." << endl;
		wcout << L"3. �������� ���������� �����." << endl;
		wcout << L"4. �������� ������� ��������� �������." << endl;
		wcout << L"5. ��������� �����." << endl;
		wcout << L"������� ����� ��������: ";
		way = _getch();
		wcout << endl;
	} while (way < '1' || way > '5');
	if (way == '1')
	{
		wcout << L"������� ����� ������� (������� & ��� �������� �� ����� ������ � �����): " << endl;
		do
		{
			getline(wcin, Q);
		} while (Q.empty());
		MakeNewLines(Q);
		Q += '#';
		QA[0][editingQ - 1] = Q;
	}
	else if (way == '2')
	{
		wcout << L"������� �������� ������, �������� �� ������ &: " << endl;
		getline(wcin, destructors);
		QA[1][editingQ - 1] = destructors;
	}
	else if (way == '3')
	{
		wcout << L"������� ���������� ����� �� ������ ������: " << endl;
		wcin.ignore();
		getline(wcin, corAns);
		correctAns[editingQ - 1] = corAns;
	}
	else if (way == '4')
	{
		do
		{
			wcout << L"������� ������� ��������� ������� (1, 2 ��� 3): ";
			wcin >> lvl;
		} while (lvl != L"1" && lvl != L"2" && lvl != L"3");
		QA[2][editingQ - 1] = lvl;
	}
}

bool OutToFile(const string testPath, vector<vector<wstring>> QA, vector<wstring> correctAns, const int countOfAllQ, const int countOfAskingQ, const wstring lvlSelection)
{
	wofstream fout(testPath);
	fout.imbue(std::locale(locale::empty(), new codecvt_utf8<wchar_t>));
	if (fout)
	{
		wstringstream temp;
		temp << countOfAskingQ << " " << lvlSelection;
		wstring countNLvl = temp.str();
		fout << countNLvl << endl;
		for (int i = 0; i < (countOfAllQ - 1); i++)
		{
			fout << QA[0][i] << endl;
			fout << QA[1][i] << endl;
			fout << correctAns[i] << endl;
			fout << QA[2][i] << endl;
		}
		fout << QA[0][countOfAllQ - 1] << endl;
		fout << QA[1][countOfAllQ - 1] << endl;
		fout << correctAns[countOfAllQ - 1] << endl;
		fout << QA[2][countOfAllQ - 1];
		return true;
	}
	return false;
}

void ChangeTest(const string testPath)
{
	vector<vector<wstring>> QA;
	vector<wstring> corAns;
	int allQ, askingQ;
	wstring lvlSelection;
	GetTests(testPath, QA, corAns, allQ, askingQ, lvlSelection);
	vector<vector<wstring>> QAOutVer = QA;
	vector<wstring> corAnsOutVer = corAns;
	PrepareTestsForOut(QAOutVer, corAnsOutVer, allQ);
	wcout << L"���� � ��������� ���������: " << endl;
	OutAllTest(QAOutVer, corAnsOutVer, allQ, askingQ, lvlSelection);
	int way;
	do
	{
		char temp;
		do
		{
			wcout << L"1. �������� ������." << endl;
			wcout << L"2. ������� ������." << endl;
			wcout << L"3. ������������� ������������ ������." << endl;
			wcout << L"4. ������� ������� ��������� ������������." << endl;
			wcout << L"5. ������� ���������� ���������� �������� (������ ��� 4 ������ ���������)." << endl;
			wcout << L"0. ��������� ��������� ����� ������������." << endl;
			wcout << L"������� ����� ��������: ";
			temp = _getch();
			way = temp - 48;
			wcout << endl;
		} while (way < 0 || way > 5);
		switch (way)
		{
		case 1:
			AddQ(QA, corAns, allQ);
			break;
		case 2:
			if (allQ == 0)
				wcout << L"0 �������� �����." << endl;
			else
			{
				int deletingQ;
				do
				{
					wcout << L"������� ����� ���������� �������: ";
					wcin >> deletingQ;
				} while (deletingQ < 1 || deletingQ > allQ);
				DeleteQ(QA, corAns, allQ, deletingQ);
			}
			break;
		case 3:
			if (allQ == 0)
				wcout << L"0 �������� �����." << endl;
			else
			{
				int editingQ;
				do
				{
					wcout << L"������� ����� �������������� �������: ";
					wcin >> editingQ;
				} while (editingQ < 1 || editingQ > allQ);
				EditQ(QA, corAns, allQ, editingQ);
			}
			break;
		case 4:
			wcout << L"������� ������� ��������� ������������: " << lvlSelection << endl << endl;
			do
			{
				wcout << L"������� ������� ��������� ������������ (1, 2, 3 ��� 4): ";
				wcin >> lvlSelection;
			} while (lvlSelection != L"1" && lvlSelection != L"2" && lvlSelection != L"3" && lvlSelection != L"4");
			break;
		case 5:
			if (allQ < 5)
				wcout << L"������ 5 �������� �����. �������� �������, ����� �������� ���������� ���������� ��������." << endl;
			else
			{
				wcout << L"���������� ���������� �������� �� 4 ������ ���������: " << askingQ << endl;
				do
				{
					wcout << L"������� ���������� ���������� �������� (�� ����� 5). ������� �������� ����� ������ �� 4 ������ ���������: ";
					wcin >> askingQ;
				} while (askingQ < 5 || askingQ > allQ);
			}
			break;
		}
		system("cls");
		if (way != 0)
		{
			if (OutToFile(testPath, QA, corAns, allQ, askingQ, lvlSelection))
			{
				wcout << L"���� ������������ ��������." << endl;
				QA.clear();
				corAns.clear();
				GetTests(testPath, QA, corAns, allQ, askingQ, lvlSelection);
				QAOutVer = QA;
				corAnsOutVer = corAns;
				int check;
				do
				{
					wcout << L"������� SPACE, ����� ���������� ����� ����������� �����, ENTER - ����� �����������: ";
					check = _getch();
				} while (check != 13 && check != 32);
				wcout << endl;
				if (check == 13)
				{
					wcout << L"���� � ��������� ���������: " << endl;
					GetTests(testPath, QA, corAns, allQ, askingQ, lvlSelection);
					PrepareTestsForOut(QAOutVer, corAnsOutVer, allQ);
					OutAllTest(QAOutVer, corAnsOutVer, allQ, askingQ, lvlSelection);
				}
			}
			else
				wcout << L"������ �������� ����� � �������������." << endl;
		}
	} while (way != 0);
}

void OutAllTest(vector<vector<wstring>> QA, vector<wstring> correctAns, const int countOfAllQ, const int countOfAskingQ, const wstring lvlSelection)
{
	wcout << L"���������� ���������� �������� �� 4 ������ ���������: " << countOfAskingQ << endl;
	wcout << L"������� ������� ��������� ������������: " << lvlSelection << endl << endl;
	for (int i = 0; i < countOfAllQ;)
	{
		int qLeft = countOfAllQ - i;
		int outQCount;
		if (qLeft >= 5)
			outQCount = 5;
		else
			outQCount = qLeft;
		for (int j = i; (j-i) < outQCount; j++)
		{
			wcout << L"������ �" << j + 1 << L". ������� ���������: " << QA[2][j] << "." << endl;
			wcout << L"����� �������: " << endl;
			wcout << QA[0][j] << endl;
			wcout << L"�������� �������: " << endl;
			wcout << QA[1][j] << endl;
			wcout << L"���������� �����: ";
			wcout << correctAns[j] << endl;
			wcout << L"===================================" << endl;
		}
		i += outQCount;
		if (i < countOfAllQ)
		{
			wcout << L"� ���� ���� ��� �������." << endl;
			system("pause");
		}
		else
			system("pause");
	}
}

//\\����������������� ������������
