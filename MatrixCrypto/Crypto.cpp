#include "Crypto.h"

vector<float> Crypto::Encrypt(vector<float> inputData, Matrix key)
{
	//Support for data that is not a length that is a multiple of key.cols
	while (inputData.size() % key.cols != 0)
	{
		inputData.push_back(-1);
	}

	std::vector<float> retVal;

	std::vector<float> chunk;
	for (int i = 0; i <= inputData.size(); ++i)
	{
		if ((i % key.cols == 0) && i != 0)
		{
			//Encrypt chunk, append to retVal, and clear chunk
			std::vector<float> encryptedChunk = key.multiply_by_vector(chunk);

			//append to retVal
			for (int j = 0; j < encryptedChunk.size(); ++j)
			{
				retVal.push_back(encryptedChunk[j]);
			}

			chunk.clear();
		}

		//MOAH... Please fix.
		if(i != inputData.size())
			chunk.push_back(inputData[i]);
	}

	return retVal;
}

vector<float> Crypto::Decrypt(vector<float> inputData, Matrix key, bool isDecryptionKey)
{
	vector<float> retVal;

	Matrix decryptionKey = (isDecryptionKey ? key : key.CalculateInverse());

	vector<float> chunk;
	for (int i = 0; i <= inputData.size(); ++i)
	{
		if ((i % decryptionKey.cols == 0) && i != 0)
		{
			//Encrypt chunk, append to retVal, and clear chunk
			std::vector<float> encryptedChunk = decryptionKey.multiply_by_vector(chunk);

			//append to retVal
			for (int j = 0; j < encryptedChunk.size(); ++j)
			{
				retVal.push_back(encryptedChunk[j]);
			}

			chunk.clear();
		}

		//MOAH... Please fix.
		if (i != inputData.size())
			chunk.push_back(inputData[i]);
	}

	return retVal;
}

string Crypto::toString(vector<float> data)
{
	string retVal = "";
	for (int i = 0; i < data.size(); ++i)
	{
		retVal += (char)data[i];
	}
	return retVal;
}