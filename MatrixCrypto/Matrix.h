#pragma once
#include <vector>
using namespace std;

class Matrix
{
public:
    Matrix(vector<vector<float>>, int rows, int cols);
    void test_print(void);
    static void test_print(vector<vector<float>> input);
    vector<float> multiply_by_vector(vector<float> vector);
    Matrix CalculateInverse();
    int rows;
    int cols;
private:
    vector<vector<float>> internalMatrix;



};