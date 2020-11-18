// MatrixCrypto.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Matrix.h"
#include "Crypto.h"
#include <iostream>

int main()
{
    vector<vector<float>> key = { {1,2,5}, {0,1,7}, {0,0,1} };

    Matrix keyMatrix = Matrix(key, 3, 3);

    keyMatrix.test_print();

    std::cout << "\n";

    std::vector<float> test = { 4,2,3 };

    Crypto crypto = Crypto();
    std::vector<float> encrypted = crypto.Encrypt(test, keyMatrix);

    vector<vector<float>> encryptedMatrix = { encrypted };

    Matrix::test_print(encryptedMatrix);
}

int main();
