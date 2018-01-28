#pragma once
#include<string>
#include<vector>
#include<map>
using namespace std;
class GeffeGeneratorCipher{
public:
	GeffeGeneratorCipher(int32_t key);
	GeffeGeneratorCipher(string key);
	vector<char> startAlg(vector<char> input);
	void startAlg(string input, string out);
	static int generateKey(string out);
	uint32_t getNextBit();
private:
	uint32_t key;
	uint32_t key1;
	uint32_t key2;
	uint32_t getNextBitFirstLfsr();
	uint32_t getNextBitSecondLfsr();
	uint32_t getNextBitThirdLfsr();
	void setKeys(int32_t key);
};
