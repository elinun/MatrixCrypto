#include "Matrix.h"
#include <iostream>

Matrix::Matrix(vector<vector<float>> matrix, int numRows, int numCols)
{
    rows = numRows;
    cols = numCols;
    internalMatrix = matrix;
}

vector<float> Matrix::multiply_by_vector(vector<float> inVector)
{
    if (inVector.size() != cols)
        throw new exception("Dimension mismatch exception."); //TODO: Add more useful info

    vector<float> product;
    for (int r = 0; r < rows; ++r)
    {
        float sum = 0;
        for (int c = 0; c < cols; ++c)
        {
            sum += (internalMatrix[c][r] * inVector[c]);
        }
        product.push_back(sum);
    }

    return product;
}

Matrix Matrix::CalculateInverse()
{
    //https://www.geeksforgeeks.org/adjoint-inverse-matrix/
    if (rows != cols)
        throw new exception("Can not calculate inverse of non-square matrix");

    //Augment Identity matrix to the right of matrix
    vector<vector<float>> augmentedMatrix;
    for (int i = 0; i < rows; ++i)
    {
        augmentedMatrix.push_back(internalMatrix[i]);
    }

    for (int i = 0; i < rows; ++i)
    {
        vector<float> columnI;
        for (int j = 0; j < cols; ++j)
        {
            columnI.push_back((j == i ? 1 : 0));
        }
        augmentedMatrix.push_back(columnI);
    }



    //RREF
    //https://en.wikipedia.org/wiki/Gaussian_elimination#Pseudocode
    //https://stackoverflow.com/questions/31756413/solving-a-simple-matrix-in-row-reduced-form-in-c
    int lead = 0;
    vector<vector<float>> A = augmentedMatrix;

    while (lead < rows) {
        float d, m;

        for (int r = 0; r < rows; r++) { // for each row ...
            /* calculate divisor and multiplier */
            d = A[lead][lead];
            m = A[lead][r] / A[lead][lead];

            for (int c = 0; c < augmentedMatrix.size(); c++) { // for each column ...
                if (r == lead)
                    A[c][r] /= d;               // make pivot = 1
                else
                    A[c][r] -= A[c][lead] * m;  // make other = 0
            }
        }

        lead++;
        //test_print(A);
    }

    //Grab the relevant columns
    vector<vector<float>> invertedMatrix(A.end() - cols, A.end());

    return Matrix(invertedMatrix, rows, cols);
}




void Matrix::test_print(vector<vector<float>> input)
{
    for (int r = 0; r < input[0].size(); ++r) {
        for (int c = 0; c < input.size(); ++c) {
            std::cout << input[c][r] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "\n\n";
}
void Matrix::test_print(void)
{
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            std::cout << internalMatrix[c][r] << ' ';
        }
        std::cout << '\n';
    }
}