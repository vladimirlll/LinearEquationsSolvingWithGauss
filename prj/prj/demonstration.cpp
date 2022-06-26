#include "demonstration.h"

char GetMethodOfFilling()
{
    char method;
    do
    {
        wcout << L"Выберите способ заполнения матрицы: " << endl;
        wcout << L"1. Заполнить с клавиатуры." << endl;
        wcout << L"2. Заполнить случайными числами." << endl;
        wcout << L"3. Заполнить из файла." << endl;
        wcout << L"Введите номер способа: ";
        method = _getch();
    } while (method < '1' || method > '3');
    return (method-48);
}

void FillWithRandomNums(vector<vector<double>>& v, const int rows, const int cols, const int min, const int max)
{
    v.resize(rows);
    for (int i = 0; i < rows; i++)
        v[i].resize(cols);
    int diapason = max - min + 1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            v[i][j] = rand() % diapason + min;
        }
    }
}

void FillByKeyboard(vector<vector<double>>& v, const int rows, const int cols)
{
    v.resize(rows);
    for (int i = 0; i < rows; i++)
        v[i].resize(cols);
    for (int i = 0; i < rows;)
    {
        wstring row;
        wstringstream ss;
        wcout << L"Введите элементы " << i + 1 << L" строк через пробел: " << endl;
        getline(wcin, row);
        ss << row;
        vector<int> rowEls;
        int el;
        while (ss >> el)
        {
            rowEls.push_back(el);
        }
        int enteredRowEls = rowEls.size();
        if (enteredRowEls == cols)
        {
            for (int j = 0; j < enteredRowEls; j++)
            {
                v[i][j] = rowEls[j];
            }
            i++;
        }
        else
        {
            wcout << L"Количество введенных элементов в строке не совпадает с количеством уравнений." << endl;
        }
    }
}

bool FillFromFile(vector<vector<double>>& v, const wstring path)
{
    wifstream fin(path);
    fin.imbue(std::locale(locale::empty(), new codecvt_utf8<wchar_t>));
    if (fin.is_open())
    {
        int count = 0; // количество чисел в файле
        double temp;

        while (fin >> temp)
        {
            count++;
        }

        if (count == 0)
            return false;
        else
        {
            fin.clear();
            fin.seekg(0, ios::beg);

            int space_count = 0;
            wchar_t symbol = ' ';
            while (!fin.eof() && symbol != L'\n')
            {
                fin.get(symbol);
                if (symbol == L' ')
                    space_count++;
            }

            fin.seekg(0, ios::beg);
            fin.clear();

            int rows = count / (space_count + 1);
            int cols = space_count + 1;
            if (rows < 2 || rows > 6 || rows != (cols - 1))
            {
                return false;
            }
            else
            {
                v.resize(rows);
                for (int i = 0; i < rows; i++)
                    v[i].resize(cols);

                for (int i = 0; i < rows; i++)
                    for (int j = 0; j < cols; j++)
                        fin >> v[i][j];

                fin.close();
                return true;
            }
        }
    }
    fin.close();
    return false;
}

bool FillMatrix(vector<vector<double>>& v, const int method)
{
    if (method == 1 || method == 2)
    {
        char temp;
        int rows;
        int cols;
        do
        {
            wcout << endl << L"Введите количество уравнений (2-6): ";
            temp = _getch();
        } while (temp < '2' || temp > '6');
        wcout << endl;
        rows = temp - 48;
        cols = rows+1;
        if (method == 1)
            FillByKeyboard(v, rows, cols);
        else
        {
            int min, max;
            wcout << endl << L"Введите нижнюю границу генерации случайных чисел (целое число): ";
            wcin >> min;
            do
            {
                wcout << endl << L"Введите верхнюю границу генерации случайных чисел, должна быть не ниже нижней границы (целое число): ";
                wcin >> max;
            } while (max < min);
            FillWithRandomNums(v, rows, cols, min, max);
        }
    }
    else
    {
        wstring path;
        wcout << endl << L"Введите название файла с расширением: ";
        wcin >> path;
        if (!FillFromFile(v, path))
        {
            return false;
        }
    }
    return true;
}

void Copy(vector<vector<double>>& In, vector<vector<double>>& Out)
{
    int Inrows = In.size();
    int Incols = In[0].size();
    Out.resize(Inrows);
    for (int i = 0; i < Inrows; i++)
        Out[i].resize(Incols);
    for (int i = 0; i < Inrows; i++)
    {
        for (int j = 0; j < Incols; j++)
            Out[i][j] = In[i][j];
    }
}

void printRow(vector<vector<double>> mat, const int row)
{
    int cols = mat[0].size();
    for (int j = 0; j < cols - 1; j++)
    {
        //вывод коэффициента с переменной
        if (abs(mat[row][j]) < eps)
            wcout << 0 << L"*x_" << j;
        else if (j > 0 && mat[row][j] < 0)
            wcout << -mat[row][j] << L"*x_" << j;
        else
            wcout << mat[row][j] << L"*x_" << j;
        //вывод арифмитеческого знака после
        if (j < (cols - 2) && mat[row][j + 1] >= 0)
            wcout << L" + ";
        else if (j < (cols - 2) && mat[row][j + 1] < 0)
            wcout << L" - ";
    }
    wcout << L" = ";
    if (abs(mat[row][cols - 1]) < eps)
        wcout << 0 << endl;
    else
        wcout << mat[row][cols - 1] << endl;
}

void print(vector<vector<double>> mat)
{
    int rows = mat.size();
    int cols = mat[0].size();
    for (int i = 0; i < rows; i++)
    {
        printRow(mat, i);
    }
    wcout << endl;
}

void swap_rows(vector<vector<double>>& mat, int i, int j)
{
    int cols = mat[0].size();
    for (int k = 0; k < cols; k++)
    {
        double temp = mat[i][k]; 
        mat[i][k] = mat[j][k];
        mat[j][k] = temp;
    }
}

void mulRowOnSomeNum(vector<vector<double>>& mat, const int row, const double num)
{
    int cols = mat[0].size();
    for (int j = 0; j < cols; j++)
    {
        mat[row][j] *= num;
    }
}

void cleanLeadings(vector<vector<double>>& mat)
{
    int rows = mat.size();
    int go_on = 1;
    for (int i = 0; i < rows; i++)
    {
        wcout << L"Перед очищением " << i + 1 << L" строки: " << endl;
        print(mat);
        double cleaner = 1 / mat[i][i];
        wcout << L"Находим коэффциент очищения: " << endl;
        wcout << L"Коэффициент = 1 / элемент"  << i + 1 << L" строки " << i + 1 << L" столбца = " << cleaner << endl;
        wcout << L"Умножаем " << i + 1 << L" строку на этот коэффциент: " << endl;
        mulRowOnSomeNum(mat, i, cleaner);
        wcout << L"После очищения " << i + 1 << L" строки: " << endl;
        print(mat);
        system("pause");
        /*while (go_on != 0)
        {
            wcout << L"Введите 0, чтобы продолжить: ";
            wcin >> go_on;
        }*/
        system("cls");
        go_on = 1;
    }
}

bool forwardElim(vector<vector<double>>& mat)
{
    wcout << L"Выполнение прямого хода метода Гаусса: " << endl;
    wcout << L"Система линейных уравнений: " << endl;
    print(mat);
    int rows = mat.size();
    int cols = mat[0].size();
    //k - номер текущего столбца или текущей строки основной матрицы 
    for (int k = 0; k < rows; k++)
    {
        int go_on = 1;
        wcout << L"Находим не нулевой максимальный элемент в " << k + 1 << L" столбце среди элементов, находящихся не выше главной диагонали: " << endl;
        int i_max = k; //индекс максимального в столбце k
        double v_max = mat[i_max][k]; //значение максимального в столбце k

        /* find greater amplitude for pivot if any */
        for (int i = k + 1; i < rows; i++)
            if (abs(mat[i][k]) > v_max)
            {
                v_max = mat[i][k];
                i_max = i;
            }

        if (!mat[k][i_max])
        {
            wcout << L"Не найден ненулевой элемент в " << k + 1 << L" столбце среди элементов, находящихся не выше главной диагонали: " << endl;
            return false;
        }
        wcout << L"Максимальный элемент = " << v_max << L", он расположен в " << i_max + 1 << L" строке." << endl;

        if (i_max != k)
        {
            wcout << L"Меняем " << k + 1 << L" и " << i_max + 1 << L" строки местами." << endl;
            wcout << L"Перед изменениями: " << endl;
            print(mat);
            swap_rows(mat, k, i_max);
            wcout << L"После изменений: " << endl;
            print(mat);
            system("pause");
            /*while (go_on != 0)
            {
                wcout << L"Введите 0, чтобы продолжить: ";
                wcin >> go_on;
            }*/
            system("cls");
        }
        go_on = 1;

        for (int i = k + 1; i < rows; i++)
        {
            wcout << L"Находим коэффициент для обнуления элемента в " << i + 1 << L" строке " << k + 1 << L" столбце: " << endl;
            double f = mat[i][k] / mat[k][k];
            wcout << L"коэффциент = "  << L"элемент " << i+1 << L" строки " << k+1 << L" столбца / элемент " << k+1 << L" строки " << k+1 << L" столбца = "  << f << endl;
            wcout << L"Из " << i + 1 << L" строки вычитаем " << k + 1 << L" строку, умноженную на " << L"коэффциент, равный " << f << endl;
            wcout << L"Перед изменениями в " << i + 1 << L" строке: " << endl;
            print(mat);
            /* subtract fth multiple of corresponding kth
               row element*/
            for (int j = k + 1; j < cols; j++)
                mat[i][j] -= mat[k][j] * f;

            /* filling lower triangular matrix with zeros*/
            mat[i][k] = 0;
            wcout << L"После изменений в " << i + 1 << L" строке: " << endl;
            print(mat);
            /*while (go_on != 0)
            {
                wcout << L"Введите 0, чтобы продолжить: ";
                wcin >> go_on;
            }*/
            system("pause");
            system("cls");
            go_on = 1;
        }
    }
    return true;
}

bool CanBeSolved(vector<vector<double>>& mat)
{
    if (!forwardElim(mat))
        return false;
    return true;
}

vector<double> gaussianElimination(vector<vector<double>>& mat)
{
    int countOfX = mat.size();
    vector<double> x;
    int go_on = 1;
    x.resize(countOfX);
    wcout << L"Перед очищением главной диагонали: " << endl;
    print(mat);
    cleanLeadings(mat);
    wcout << L"После очищения главной диагонали: " << endl;
    print(mat);
    wcout << L"Прямой ход метода Гаусса завершен." << endl << endl;
    system("pause");
    /*while (go_on != 0)
    {
        wcout << L"Введите 0, чтобы продолжить: ";
        wcin >> go_on;
    }*/
    system("cls");
    go_on = 1;
    wcout << L"Находим значения переменных: " << endl;
    wcout << L"Система: " << endl;
    print(mat);
    wcout << L"Значение x_" << countOfX - 1 << L" находим из " << countOfX << L" строки. ";
    wcout << countOfX << L" строка: " << endl;
    printRow(mat, countOfX - 1);
    x[countOfX - 1] = mat[countOfX - 1][countOfX];
    wcout << L"x_" << countOfX - 1 << L" равно: " << x[countOfX - 1] << endl;
    system("pause");
    /*while (go_on != 0)
    {
        wcout << L"Введите 0, чтобы продолжить: ";
        wcin >> go_on;
    }*/
    go_on = 1;
    system("cls");
    for (int i = countOfX - 2; i >= 0; i--)
    {
        wcout << L"Система: " << endl;
        print(mat);
        wcout << L"Значение x_" << i << L" находим из " << i + 1 << L" строки: " << endl;
        wcout << i + 1 << L" строка: " << endl;
        printRow(mat, i);
        wcout << L"При этом зная, что: " << endl;
        for (int j = countOfX - 1; j > i + 1; j--)
        {
            wcout << L"x_" << j << L" = " << x[j] << L", ";
        }
        wcout << L"x_" << i + 1 << L" = " << x[i + 1] << endl;
        x[i] = mat[i][countOfX];

        for (int j = i + 1; j < countOfX; j++)
        {
            x[i] -= mat[i][j] * x[j];
        }
        wcout << L"Получаем: " << endl;
        wcout << L"x_" << i << L" = " << x[i] << endl;
        system("pause");
        /*while (go_on != 0)
        {
            wcout << L"Введите 0, чтобы продолжить: ";
            wcin >> go_on;
        }*/
        go_on = 1;
        system("cls");
    }
    return x;
}

void ShowAnswer(vector<double> x)
{
    int countOfX = x.size();
    for (int i = 0; i < countOfX; i++)
    {
        wcout << L"x_" << i << L" = " << x[i] << endl;
    }
}
