#include "demonstration.h"

char GetMethodOfFilling()
{
    char method;
    do
    {
        wcout << L"�������� ������ ���������� �������: " << endl;
        wcout << L"1. ��������� � ����������." << endl;
        wcout << L"2. ��������� ���������� �������." << endl;
        wcout << L"3. ��������� �� �����." << endl;
        wcout << L"������� ����� �������: ";
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
        wcout << L"������� �������� " << i + 1 << L" ����� ����� ������: " << endl;
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
            wcout << L"���������� ��������� ��������� � ������ �� ��������� � ����������� ���������." << endl;
        }
    }
}

bool FillFromFile(vector<vector<double>>& v, const wstring path)
{
    wifstream fin(path);
    fin.imbue(std::locale(locale::empty(), new codecvt_utf8<wchar_t>));
    if (fin.is_open())
    {
        int count = 0; // ���������� ����� � �����
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
            wcout << endl << L"������� ���������� ��������� (2-6): ";
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
            wcout << endl << L"������� ������ ������� ��������� ��������� ����� (����� �����): ";
            wcin >> min;
            do
            {
                wcout << endl << L"������� ������� ������� ��������� ��������� �����, ������ ���� �� ���� ������ ������� (����� �����): ";
                wcin >> max;
            } while (max < min);
            FillWithRandomNums(v, rows, cols, min, max);
        }
    }
    else
    {
        wstring path;
        wcout << endl << L"������� �������� ����� � �����������: ";
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
        //����� ������������ � ����������
        if (abs(mat[row][j]) < eps)
            wcout << 0 << L"*x_" << j;
        else if (j > 0 && mat[row][j] < 0)
            wcout << -mat[row][j] << L"*x_" << j;
        else
            wcout << mat[row][j] << L"*x_" << j;
        //����� ��������������� ����� �����
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
        wcout << L"����� ��������� " << i + 1 << L" ������: " << endl;
        print(mat);
        double cleaner = 1 / mat[i][i];
        wcout << L"������� ���������� ��������: " << endl;
        wcout << L"����������� = 1 / �������"  << i + 1 << L" ������ " << i + 1 << L" ������� = " << cleaner << endl;
        wcout << L"�������� " << i + 1 << L" ������ �� ���� ����������: " << endl;
        mulRowOnSomeNum(mat, i, cleaner);
        wcout << L"����� �������� " << i + 1 << L" ������: " << endl;
        print(mat);
        system("pause");
        /*while (go_on != 0)
        {
            wcout << L"������� 0, ����� ����������: ";
            wcin >> go_on;
        }*/
        system("cls");
        go_on = 1;
    }
}

bool forwardElim(vector<vector<double>>& mat)
{
    wcout << L"���������� ������� ���� ������ ������: " << endl;
    wcout << L"������� �������� ���������: " << endl;
    print(mat);
    int rows = mat.size();
    int cols = mat[0].size();
    //k - ����� �������� ������� ��� ������� ������ �������� ������� 
    for (int k = 0; k < rows; k++)
    {
        int go_on = 1;
        wcout << L"������� �� ������� ������������ ������� � " << k + 1 << L" ������� ����� ���������, ����������� �� ���� ������� ���������: " << endl;
        int i_max = k; //������ ������������� � ������� k
        double v_max = mat[i_max][k]; //�������� ������������� � ������� k

        /* find greater amplitude for pivot if any */
        for (int i = k + 1; i < rows; i++)
            if (abs(mat[i][k]) > v_max)
            {
                v_max = mat[i][k];
                i_max = i;
            }

        if (!mat[k][i_max])
        {
            wcout << L"�� ������ ��������� ������� � " << k + 1 << L" ������� ����� ���������, ����������� �� ���� ������� ���������: " << endl;
            return false;
        }
        wcout << L"������������ ������� = " << v_max << L", �� ���������� � " << i_max + 1 << L" ������." << endl;

        if (i_max != k)
        {
            wcout << L"������ " << k + 1 << L" � " << i_max + 1 << L" ������ �������." << endl;
            wcout << L"����� �����������: " << endl;
            print(mat);
            swap_rows(mat, k, i_max);
            wcout << L"����� ���������: " << endl;
            print(mat);
            system("pause");
            /*while (go_on != 0)
            {
                wcout << L"������� 0, ����� ����������: ";
                wcin >> go_on;
            }*/
            system("cls");
        }
        go_on = 1;

        for (int i = k + 1; i < rows; i++)
        {
            wcout << L"������� ����������� ��� ��������� �������� � " << i + 1 << L" ������ " << k + 1 << L" �������: " << endl;
            double f = mat[i][k] / mat[k][k];
            wcout << L"���������� = "  << L"������� " << i+1 << L" ������ " << k+1 << L" ������� / ������� " << k+1 << L" ������ " << k+1 << L" ������� = "  << f << endl;
            wcout << L"�� " << i + 1 << L" ������ �������� " << k + 1 << L" ������, ���������� �� " << L"����������, ������ " << f << endl;
            wcout << L"����� ����������� � " << i + 1 << L" ������: " << endl;
            print(mat);
            /* subtract fth multiple of corresponding kth
               row element*/
            for (int j = k + 1; j < cols; j++)
                mat[i][j] -= mat[k][j] * f;

            /* filling lower triangular matrix with zeros*/
            mat[i][k] = 0;
            wcout << L"����� ��������� � " << i + 1 << L" ������: " << endl;
            print(mat);
            /*while (go_on != 0)
            {
                wcout << L"������� 0, ����� ����������: ";
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
    wcout << L"����� ��������� ������� ���������: " << endl;
    print(mat);
    cleanLeadings(mat);
    wcout << L"����� �������� ������� ���������: " << endl;
    print(mat);
    wcout << L"������ ��� ������ ������ ��������." << endl << endl;
    system("pause");
    /*while (go_on != 0)
    {
        wcout << L"������� 0, ����� ����������: ";
        wcin >> go_on;
    }*/
    system("cls");
    go_on = 1;
    wcout << L"������� �������� ����������: " << endl;
    wcout << L"�������: " << endl;
    print(mat);
    wcout << L"�������� x_" << countOfX - 1 << L" ������� �� " << countOfX << L" ������. ";
    wcout << countOfX << L" ������: " << endl;
    printRow(mat, countOfX - 1);
    x[countOfX - 1] = mat[countOfX - 1][countOfX];
    wcout << L"x_" << countOfX - 1 << L" �����: " << x[countOfX - 1] << endl;
    system("pause");
    /*while (go_on != 0)
    {
        wcout << L"������� 0, ����� ����������: ";
        wcin >> go_on;
    }*/
    go_on = 1;
    system("cls");
    for (int i = countOfX - 2; i >= 0; i--)
    {
        wcout << L"�������: " << endl;
        print(mat);
        wcout << L"�������� x_" << i << L" ������� �� " << i + 1 << L" ������: " << endl;
        wcout << i + 1 << L" ������: " << endl;
        printRow(mat, i);
        wcout << L"��� ���� ����, ���: " << endl;
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
        wcout << L"��������: " << endl;
        wcout << L"x_" << i << L" = " << x[i] << endl;
        system("pause");
        /*while (go_on != 0)
        {
            wcout << L"������� 0, ����� ����������: ";
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
