#include "theory.h"
#include "demonstration.h"
#include "testing.h"
#include "admin.h"
using namespace std;

int Menu()
{
	char chooice;
	do
	{
		wcout << L"�������� ��������, ������� ������ ���������: " << endl;
		wcout << L"1. ����������� ������ �� ������� ������ �������� ��������� ������� ������." << endl;
		wcout << L"2. ���������� ������������ ������� ������ �������� ��������� ������� ������." << endl;
		wcout << L"3. ������ ������������ �� ���� \"������� ������ �������� ��������� ������� ������\"." << endl;
		wcout << L"4. ����������������." << endl;
		wcout << L"0. ��������� ������ ���������." << endl;
		wcout << L"������� ����� ��������: ";
		chooice = _getch();
	} while (chooice < '0' || chooice > '4');
	return (chooice-48);
}

int main()
{
	system("chcp 1251 > nul");
	srand(time(NULL));
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);
	wcout << L"\t   ������������ ��������������� ����������� �����������\n";
	wcout << L"\t     �������� �������������� ���������� � ������������\n\n\n";
	wcout << L"\t\t\t�������� ������� �� ����������\n";
	wcout << L"\t\t   ���������������� � �����������\n";
	wcout << L"\t\t\t������-���������������� ���������\n";
	wcout << L"\t\t   \"������� ������ �������� ��������� ������� ������\"\n";
	wcout << L"  ������-���������������� ���������\n";
	wcout << L"         \"������� ������ �������� ��������� ������� ������\"\n\n\n\n";

	wcout << L"\t\t\t\t\t\t��������: ������� ������ �����-11/1\n\n";
	wcout << L"\t\t\t\t\t\t\t  ����������� �.�.\n\n\n";
	wcout << L"������������, �� ��������� ������-���������������� ��������� \"������� ������ �������� ��������� ������� ������\"." << endl << endl;
	int chooice;
	string theoryPath = "theory.txt";
	string testPath = "test.txt";
	do
	{
		chooice = Menu();
		system("cls");
		switch (chooice)
		{
		case 1:
		{
			vector<vector<wstring>> chapters = GetChapters(theoryPath);
			ReadTheory(chapters);
			break;
		}
		case 2:
		{
			int method = GetMethodOfFilling();
			vector<vector<double>> matr;
			if (!FillMatrix(matr, method))
			{
				wcout << endl << L"������ �������� ����� ��� �������� ������ �����." << endl;
				exit(1);
			}
			vector<double> x;
			if (CanBeSolved(matr))
			{
				x = gaussianElimination(matr);
				wcout << L"������� ������� �������� ���������: " << endl;
				ShowAnswer(x);
			}
			else
			{
				wcout << L"������ ������� �� ����� ������� ��� �� ���������� ����������." << endl;
			}
			break;
		}
		case 3:
		{
			vector<vector<wstring>> allQA; //������ �������� � �������� ������
			vector<wstring> allCorrectAns; //������ ���������� �������
			int countOfAskingQ, countOfAllQ;
			wstring lvlSelection;
			GetTests(testPath, allQA, allCorrectAns, countOfAllQ, countOfAskingQ, lvlSelection);
			if (lvlSelection == L"4" && (countOfAskingQ < 5 || countOfAskingQ > countOfAllQ))
			{
				wcout << L"������� ������������ �������� ��� ���������� ���������� ��������." << endl;
			}
			else if (lvlSelection != L"4" && (countOfAskingQ <= 0 || countOfAskingQ > countOfAllQ))
			{
				wcout << L"������� ������������ �������� ��� ���������� ���������� ��������." << endl;
			}
			else
			{
				vector<vector<wstring>> QAOutVer;
				vector<wstring> correctAnsOutVer;
				GetNecessaryQ(allQA, allCorrectAns, QAOutVer, correctAnsOutVer, countOfAskingQ, lvlSelection);
				int realAskingQ = correctAnsOutVer.size();
				PrepareTestsForOut(QAOutVer, correctAnsOutVer, realAskingQ);
				if (!QAOutVer.empty())
				{
					countOfAskingQ = QAOutVer[0].size();
					wcout << L"������ ";
					if (lvlSelection == L"4")
						wcout << L"������� �� �������� ����������� ���������." << endl;
					else
						wcout << lvlSelection << L" ������� �������." << endl;
					wcout << L"��� ����� ���������� " << countOfAskingQ << L" �������� ������� � ���������� ������, �� ������� �� ������ ������ ��������." << endl;
					wcout << L"���������� ������� �� ������ ������� ����� �������� ������ ���� �� ��������� ������." << endl;
					wcout << L"������� �������� ����� �������� ������. ����� �� ������ ���������� �������, ����� 0 � �������� ������," << endl;
					wcout << L"� ����� ������ ����� �� ������ ������� ����� ��������� ��������. " << endl;
					wcout << L"�� ������ ���������� �����, ���������� ���������� ������� ������������� �� 1.\n�� ������ ������������ ����� - ���������� ������������ ������������� �� 1." << endl;
					wcout << L"������������ ��������� ��������, ���� ���������� ���������� ������� ����� �� ������ ���������� ������������ �������." << endl;
					system("pause");
					system("cls");
					int correctAnsCount = 0, wrongAnsCount = 0;
					int i = 0;
					//wcin.ignore();
					for (int i = 0; i < realAskingQ; i++)
					{
						wcout << L"������: " << endl;
						wcout << QAOutVer[0][i] << endl;
						wcout << L"�������� �������: " << endl;
						wcout << QAOutVer[1][i] << endl;
						wchar_t temp;
						wcout << L"������� ����� �������� ������ ��� ������� 0, ����� ���������� �������: ";
						//getline(wcin, userAns);
						temp = _getwch();
						wstring userAns = L"";
						userAns += temp;
						if (temp != L'0')
						{
							if (IsAnswerCorrect(correctAnsOutVer[i], userAns))
							{
								wcout << endl << L"�� �������� ���������." << endl << endl;
								correctAnsCount++;
							}
							else
							{
								wcout << endl << L"�� �������� �����������." << endl << endl;
								wrongAnsCount++;
							}
						}
						else
						{
							wcout << endl;
							wrongAnsCount++;
						}
						wcout << L"������� ���������: " << endl;
						wcout << L"���������� ���������� �������: " << correctAnsCount << endl;
						wcout << L"���������� ������������ ������: " << wrongAnsCount << endl;
						system("pause");
						system("cls");
					}
					wcout << L"������������ ���������. �������� ���������: " << endl;
					wcout << L"���������� ���������� �������: " << correctAnsCount << endl;
					wcout << L"���������� ������������ ������: " << wrongAnsCount << endl;
					if (correctAnsCount >= wrongAnsCount)
					{
						wcout << L"���������� ���������� ������� �� ������ ������������. ������������ ������ �������. " << endl;
					}
					else
					{
						wcout << L"���������� ���������� ������� ������ ������������. ������������ ������ ���������." << endl;
					}
					system("pause");
					//����� ��������� �� ������ QAOutVer
				}
				else
				{
					wcout << L"�� ������� �������� � ���������� ����������� ������������." << endl;
				}
			}
			break;
		}
		case 4:
		{
			wstring password;
			do
			{
				wcout << L"������� ������. ����� ����� ������� 123: ";
				wcin >> password;
			} while (password != L"adminadmin123" && password != L"123");
			if (password == L"adminadmin123")
			{
				wcout << L"�� ����� � ������ ��������������" << endl;
				int whatChange = AdminMenu();
				if (whatChange == 1)
				{
					wcout << L"�� ������� ���������� ��� ����� � ������� ���� ��� ���������." << endl;
					system("pause");
					ChangeTheory(theoryPath);
				}
				else if (whatChange == 2)
				{
					ChangeTest(testPath);
				}
			}
			break;
		}
		}
	} while (chooice != 0);

	return 0;
}