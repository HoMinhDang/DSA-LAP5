#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int SIZE = 10;


void input(bool A[SIZE][SIZE], string fileName)
{
    string s;
    ifstream fi;
    fi.open(fileName);
    int cnt_i = 0;
    while (getline(fi, s))
    {
        int x;
        int cnt_j = 0;
        stringstream ss(s);
        while (ss >> x)
        {
            if (x == 0)
                A[cnt_i][cnt_j] = false;
            else
                A[cnt_i][cnt_j] = true;
            cnt_j++;
        }
    cnt_i++;
    }

    fi.close();
}

void print(bool A[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            if (A[i][j])
                cout << "o ";
            else    
                cout << ". ";
        cout << "\n";
    }
    cout <<"\n\n";
}

bool is_inside(int ni, int nj)
{
    if (0 <= ni && ni < SIZE && 0 <= nj && nj < SIZE)
        return true;
    return false;
}

bool is_equal(bool A[SIZE][SIZE], bool B[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (A[i][j] != B[i][j])
                return false;
    return true;
}

// B = A
void copy(bool A[SIZE][SIZE], bool B[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            B[i][j] = A[i][j];
}

void nextGenerate(bool A[SIZE][SIZE])
{
    bool tmp[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            tmp[i][j] = A[i][j];
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int live = 0;
            for (int ii = -1; ii < 2; ii++)
                for (int jj = -1; jj < 2; jj++)
                {
                    if(ii == 0 && jj == 0)
                        continue;
                    if (tmp[i + ii][j + jj] && is_inside(i+ii, j+jj))
                        live++;
                }
            if (live < 2)
                A[i][j] = false;
            else if (live == 3)
                A[i][j] = true;
            else if (live > 3)
                A[i][j] = false;
        }
    }
}

void output(bool F0[SIZE][SIZE])
{
    bool O[SIZE][SIZE] = {0};

    bool F1[SIZE][SIZE], F2[SIZE][SIZE];


    cout << "Output: \n";

    while (true)
    {
        copy(F0, F1);
        nextGenerate(F1);

        copy(F1, F2);
        nextGenerate(F2);

        if (is_equal(F0, F2) || (is_equal(F0, F1)))
            break;

        copy(F2, F0);
        nextGenerate(F0);
    }

    if (is_equal(F0, O))
    {
        cout << "All death";
    }
    else if (is_equal(F0, F1))
    {
        print(F0);
    }
    else  
    {
        print(F0);
        print(F1);
    }  
        
}

int main()
{
    bool A[SIZE][SIZE] = {0};
    string fileName;
    cout << "Nhap ten file Input: "; cin >> fileName;
    input(A, fileName);
    output(A);
    return 0;
}