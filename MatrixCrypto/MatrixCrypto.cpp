// MatrixCrypto.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Matrix.h"
#include "Crypto.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    vector<float> emptyVector;
    vector<vector<float>> key;
    string entryStr = "";
    float entry = 0;
    int row = 0;
    int col = 0;
    int n = 1;
    cout << "Please enter the dimension of the key as an integer: \n";
    cin >> n;
    key.assign(n, emptyVector);
    while (row < n)
    {
        while (true)
        {
            cout << "Please enter entry for Row: " << row << " Column: " << col << "\n";
            try {
                cin >> entryStr;
                entry = stof(entryStr);
                key[col].push_back(entry);

                col++;
                if (col >= n)
                    break;
            }
            catch (invalid_argument) { cout << "That's not a number. Try again."; }
        }
        row++;
        col = 0;
    }

    cout << "Key you entered: \n";
    Matrix::test_print(key);
    cout << "\n";

    /*cin.ignore();
    string data;
    cout << "Please enter the data: " << endl;
    getline(cin, data);*/

    string inPath = "";
    cout << "Please enter the input data file path: " << endl;
    cin >> inPath;

    string outPath = "";
    cout << "Please enter the output data file path: " << endl;
    cin >> outPath;

    string operation = "";
    cout << "Encrypt or Decrypt? (e/d): \n";
    cin >> operation;
    bool encrypt = operation == "e";
    bool isDecryptionKey = false;
    if (!encrypt)
    {
        string doInvertStr = "";
        cout << "Does the key need to be inverted? (y/n)\n";
        cin >> doInvertStr;
        isDecryptionKey = doInvertStr == "n";
    }

    Matrix keyMatrix = Matrix::Matrix(key, n, n);
    Crypto crypto = Crypto();
    vector<float> numericData;


    if (encrypt)
    {
        ifstream f(inPath, ios::binary | ios::in);
        if (!f.good())
            throw exception("File not found");
        char c;
        while (f.get(c)) {
            numericData.push_back(c);
        }
        f.close();
        vector<float> encryptedData = crypto.Encrypt(numericData, keyMatrix);
        string encrypted = crypto.toString(encryptedData);
        cout << "Encrypted: " << encrypted;
        ofstream outFile;
        outFile.open(outPath, ios::binary | ios::out);
        for (int i = 0; i < encryptedData.size(); ++i)
        {
            int toStore = encryptedData[i];
            outFile.write((char*)&toStore, sizeof(toStore));
        }
        outFile.close();
    }
    else
    {
        //decrypt

        ifstream f(inPath, ios::binary | ios::in);
        if (!f.good())
            throw exception("File not found");
        int c = 0;
        while (f.read((char*)&c, sizeof(c))) {
            numericData.push_back(c);
        }
        f.close();
        vector<float> decryptedData = crypto.Decrypt(numericData, keyMatrix, isDecryptionKey);
        string decrypted = crypto.toString(decryptedData);
        cout << "Decrypted: " << decrypted;
        ofstream outFile;
        outFile.open(outPath, ios::binary | ios::out);
        outFile << decrypted;
        outFile.close();
    }
}

int main();
