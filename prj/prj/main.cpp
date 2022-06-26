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
		wcout << L"Выберите действие, которое хотите выполнить: " << endl;
		wcout << L"1. Просмотреть теорию по решению систем линейных уравнений методом Гаусса." << endl;
		wcout << L"2. Посмотреть демонстрацию решения систем линейных уравнений методом Гаусса." << endl;
		wcout << L"3. Пройти тестирование по теме \"решение систем линейных уравнений методом Гаусса\"." << endl;
		wcout << L"4. Администирование." << endl;
		wcout << L"0. Завершить работу программы." << endl;
		wcout << L"Введите номер действия: ";
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
	wcout << L"\t   Астраханский государственный технический университет\n";
	wcout << L"\t     Институт Информационных технологий и коммуникаций\n\n\n";
	wcout << L"\t\t\tКурсовой провект по дисциплине\n";
	wcout << L"\t\t   Программирование и информатика\n";
	wcout << L"\t\t\tУчебно-демонстрационная программа\n";
	wcout << L"\t\t   \"Решение систем линейных уравнений методом Гаусса\"\n";
	wcout << L"  Учебно-демонстрационная программа\n";
	wcout << L"         \"Решение систем линейных уравнений методом Гаусса\"\n\n\n\n";

	wcout << L"\t\t\t\t\t\tВыполнил: студент группы ДИПРБ-11/1\n\n";
	wcout << L"\t\t\t\t\t\t\t  Лиджигоряев В.А.\n\n\n";
	wcout << L"Здравствуйте, Вы запустили учебно-демонстрационную программу \"Решение систем линейных уравнений методом Гаусса\"." << endl << endl;
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
				wcout << endl << L"Ошибка открытия файла или неверный формат файла." << endl;
				exit(1);
			}
			vector<double> x;
			if (CanBeSolved(matr))
			{
				x = gaussianElimination(matr);
				wcout << L"Решение системы линейных уравнений: " << endl;
				ShowAnswer(x);
			}
			else
			{
				wcout << L"Данная система не имеет решений или их количество бесконечно." << endl;
			}
			break;
		}
		case 3:
		{
			vector<vector<wstring>> allQA; //вектор вопросов и вариатов ответа
			vector<wstring> allCorrectAns; //вектор правильных ответов
			int countOfAskingQ, countOfAllQ;
			wstring lvlSelection;
			GetTests(testPath, allQA, allCorrectAns, countOfAllQ, countOfAskingQ, lvlSelection);
			if (lvlSelection == L"4" && (countOfAskingQ < 5 || countOfAskingQ > countOfAllQ))
			{
				wcout << L"Выбрано некорректное значение для количества задаваемых вопросов." << endl;
			}
			else if (lvlSelection != L"4" && (countOfAskingQ <= 0 || countOfAskingQ > countOfAllQ))
			{
				wcout << L"Выбрано некорректное значение для количества задаваемых вопросов." << endl;
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
					wcout << L"Выбран ";
					if (lvlSelection == L"4")
						wcout << L"уровень со случайно выбираемыми заданиями." << endl;
					else
						wcout << lvlSelection << L" уровень заданий." << endl;
					wcout << L"Вам будет предложены " << countOfAskingQ << L" тестовых заданий с вариантами ответа, на которые Вы должны будете ответить." << endl;
					wcout << L"Правильным ответом на каждое задание может являться только один из вариантов ответа." << endl;
					wcout << L"Ответом является номер варианта ответа. Также Вы можете пропустить задание, введя 0 в качестве ответа," << endl;
					wcout << L"в таком случае ответ на вопрос задания будет считаться неверным. " << endl;
					wcout << L"За каждый правильный ответ, количество правильных ответов увеличивается на 1.\nЗа каждый неправильный ответ - количество неправильных увеличивается на 1." << endl;
					wcout << L"Тестирование считается успешным, если количество правильных ответов будет не меньше количества неправильных ответов." << endl;
					system("pause");
					system("cls");
					int correctAnsCount = 0, wrongAnsCount = 0;
					int i = 0;
					//wcin.ignore();
					for (int i = 0; i < realAskingQ; i++)
					{
						wcout << L"Вопрос: " << endl;
						wcout << QAOutVer[0][i] << endl;
						wcout << L"Варианты ответов: " << endl;
						wcout << QAOutVer[1][i] << endl;
						wchar_t temp;
						wcout << L"Введите номер варианта ответа или введите 0, чтобы пропустить задание: ";
						//getline(wcin, userAns);
						temp = _getwch();
						wstring userAns = L"";
						userAns += temp;
						if (temp != L'0')
						{
							if (IsAnswerCorrect(correctAnsOutVer[i], userAns))
							{
								wcout << endl << L"Вы ответили правильно." << endl << endl;
								correctAnsCount++;
							}
							else
							{
								wcout << endl << L"Вы ответили неправильно." << endl << endl;
								wrongAnsCount++;
							}
						}
						else
						{
							wcout << endl;
							wrongAnsCount++;
						}
						wcout << L"Текущий результат: " << endl;
						wcout << L"Количество правильных ответов: " << correctAnsCount << endl;
						wcout << L"Количество неправильных ответо: " << wrongAnsCount << endl;
						system("pause");
						system("cls");
					}
					wcout << L"Тестирование завершено. Итоговый результат: " << endl;
					wcout << L"Количество правильных ответов: " << correctAnsCount << endl;
					wcout << L"Количество неправильных ответо: " << wrongAnsCount << endl;
					if (correctAnsCount >= wrongAnsCount)
					{
						wcout << L"Количество правильных ответов не меньше неправильных. Тестирование прошло успешно. " << endl;
					}
					else
					{
						wcout << L"Количество правильных ответов меньше неправильных. Тестирование прошло неуспешно." << endl;
					}
					system("pause");
					//конец ветвления не пустой QAOutVer
				}
				else
				{
					wcout << L"Не нашлось вопросов с выбранными настройками тестирования." << endl;
				}
			}
			break;
		}
		case 4:
		{
			wstring password;
			do
			{
				wcout << L"Введите пароль. Чтобы выйти введите 123: ";
				wcin >> password;
			} while (password != L"adminadmin123" && password != L"123");
			if (password == L"adminadmin123")
			{
				wcout << L"Вы вошли в панель администратора" << endl;
				int whatChange = AdminMenu();
				if (whatChange == 1)
				{
					wcout << L"Вы сможете посмотреть все главы и выбрать одну для изменения." << endl;
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