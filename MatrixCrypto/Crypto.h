#pragma once
#include <vector>
#include <string>
#include "Matrix.h"
using namespace std;

class Crypto
{
public:
	vector<float> Encrypt(vector<float>, Matrix key);
	vector<float> Decrypt(vector<float>, Matrix key, bool isDecryptionKey);
	string toString(vector<float> data);
};

