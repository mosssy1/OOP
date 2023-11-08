#include <iostream>
#include <fstream>
#include <iomanip>
#include <optional>
using namespace std;

const int N = 3;
using Matrix3x3 = double[3][3];
using Matrix2x2 = double[2][2];

struct Args
{
    string inputFileName;
};
optional<Args> ParseArgs(int argc, char* argv[]);

void ReadMatrix(Matrix3x3 inputMatrix, string fileName)
{
    ifstream input;
    input.open(fileName);
    if (!input.is_open()) 
    {
        throw exception("Error: Could not open file");
    }
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            if (!(input >> inputMatrix[i][j])) 
            {
                throw exception("Error: Could not read matrix element");
            }
        }
    }
    input.close();
}

void PrintMatrix(Matrix3x3 inputMatrix)
{
    cout << fixed << setprecision(3);
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            cout << inputMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

double GetDeterminant(Matrix3x3 inputMatrix)
{
    double det = 0;
    det = inputMatrix[0][0] * inputMatrix[1][1] * inputMatrix[2][2];
    det += inputMatrix[2][0] * inputMatrix[0][1] * inputMatrix[1][2];
    det += inputMatrix[1][0] * inputMatrix[2][1] * inputMatrix[0][2];
    det -= inputMatrix[2][0] * inputMatrix[1][1] * inputMatrix[0][2];
    det -= inputMatrix[0][0] * inputMatrix[2][1] * inputMatrix[1][2];
    det -= inputMatrix[1][0] * inputMatrix[0][1] * inputMatrix[2][2];
    return det;
}

void TransposeMatrix(Matrix3x3 inputMatrix, Matrix3x3 adjugateMatrix)
{
    for (int i = 0; i < N; ++i) 
    { 
        for (int j = 0; j < N; ++j) 
        {
            adjugateMatrix[j][i] = inputMatrix[i][j];
        }
    }
}

void CreateAddMatrix(Matrix3x3 addMatrix, Matrix3x3 adjugateMatrix)
{
    for (int i = 0; i < N; ++i) 
    {
        for (int j = 0; j < N; ++j) 
        {
            addMatrix[i][j] = adjugateMatrix[i][j];
        }
    }
}

void MinorCalc(Matrix2x2 minor, Matrix3x3 addMatrix, int i, int j)
{
    int r = 0, c = 0;
    for (int k = 0; k < N; k++) 
    {
        if (k != i) 
        {
            c = 0;
            for (int l = 0; l < N; l++) 
            {
                if (l != j) 
                {
                    minor[r][c] = addMatrix[k][l];
                    c++;
                }
            }
            r++;
        }
    }
}

int SignCalc(int i, int j, int sign) 
{
    if ((i + j) % 2 == 0) 
    {
        sign = 1;
    }
    else 
    {
        sign = -1;
    }
    return sign;
}

void CreateAdjugateMatrix(Matrix3x3 adjugateMatrix)
{
    Matrix3x3 addMatrix;
    CreateAddMatrix(addMatrix, adjugateMatrix);
    int sign = 1;
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            sign = SignCalc(i, j, sign);


            Matrix2x2 minor;
            MinorCalc(minor, addMatrix, i, j);

            // Вычисляем определитель минора
            double det = minor[0][0] * minor[1][1] - minor[0][1] * minor[1][0];

            // Вычисляем алгебраическое дополнение и записываем
            adjugateMatrix[i][j] = sign * det;
        }
    }
}

void MultiMatrixOnNumber(double det, Matrix3x3 transposeMatrix , Matrix3x3 invertMatrix) 
{
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            invertMatrix[i][j] = (1 / det) * transposeMatrix[i][j];
        }
    }
}

void InvertMatrix(Matrix3x3 inputMatrix, Matrix3x3 invertMatrix) 
{
    double det = GetDeterminant(inputMatrix);
    if (det == 0) 
    {
        cout << "Error: Matrix is singular, inxert matrix does not exist" << endl;
        exit(1);
    }
    Matrix3x3 transpose;
    TransposeMatrix(inputMatrix, transpose);
    CreateAdjugateMatrix(transpose);
    MultiMatrixOnNumber(det, transpose, invertMatrix);
}

int main(int argc, char* argv[]) 
{
    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }
    string fileName = args->inputFileName;

    Matrix3x3 inputMatrix;
    Matrix3x3 invertMatrix;

    try
    {
        ReadMatrix(inputMatrix, fileName);
        InvertMatrix(inputMatrix, invertMatrix);
        PrintMatrix(invertMatrix);
    }
    catch (exception const& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: Invert.exe <input file name> \n";
        return nullopt;
    }

    Args args;
    args.inputFileName = argv[1];

    return args;
}