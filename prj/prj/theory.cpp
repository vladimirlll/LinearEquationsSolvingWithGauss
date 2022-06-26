#include "theory.h"

vector<vector<wstring>> GetChapters(const string theoryPath)
{
	vector<vector<wstring>> chapters;
	wifstream fin(theoryPath);
	fin.imbue(std::locale(locale::empty(), new codecvt_utf8<wchar_t>));
	wstring row; //строка в тексте
	int index = 0;
	int rowsIndex = 0;
	while (getline(fin, row)) //получение строки
	{
		chapters.resize(index + 1);
		wchar_t lastSymbolOfRow = row.back();
		chapters[index].resize(rowsIndex + 1);
		if (lastSymbolOfRow == L'#')
		{
			row.resize(row.size() - 1);
			chapters[index][rowsIndex] += row;
			chapters[index][rowsIndex] += L'\n';
			index++;
			rowsIndex = 0;
		}
		else
		{
			chapters[index][rowsIndex] += row;
			chapters[index][rowsIndex] += L'\n';
			rowsIndex++;
		}
	}
	fin.close();
	return chapters;
}

void ReadTheory(const vector<vector<wstring>>& chapters)
{
	int chapsCount = chapters.size();
	for (int i = 0; i < chapsCount; )
	{
		wcout << L"√лава " << i + 1 << L": " << endl;
		int rowsCountOfChap = chapters[i].size();
		for (int j = 0; j < rowsCountOfChap; j++)
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
					wcout << L"Ќажмите <-, чтобы вернутьс€ на одну главу назад, -> - чтобы перейти на одну главу вперед: ";
					temp = _getch();
				} while (temp != 224);
				temp = _getch();
			} while (temp != 75 && temp != 77);
			if (temp == 75)
			{
				if (i == 0)
				{
					wcout << endl << L"Ќельз€ перейти на главу назад, так как это перва€ глава." << endl;
				}
				else
				{
					i--;
					changed = true;
				}
			}
			else
			{
				i++;
				changed = true;
			}
		}
		system("cls");
	}
	wcout << L"ѕоказ теории завершен." << endl;
}
