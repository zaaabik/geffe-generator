#include"GeffeGeneratorCipher.h"
#include<iostream>
#include<fstream>
#include<random>
#include<bitset>
#include<time.h>
using namespace std;
GeffeGeneratorCipher::GeffeGeneratorCipher(int32_t key) {
	setKeys(key);
}

GeffeGeneratorCipher::GeffeGeneratorCipher(string keyPath) {
	ifstream keyFile(keyPath, ios::binary | ios::in);
	if (!keyFile.is_open()) {
		throw new std::exception("file with key does not exist!");
	}
	int32_t a;
	keyFile.read(reinterpret_cast<char *>(&a), sizeof(a));
	keyFile.close();
	setKeys(a);	
}

vector<char> GeffeGeneratorCipher::startAlg(vector<char> input) {
	for (int i = 0; i < input.size(); ++i) {
		int gamma = 0;
		for (int i = 0; i < 8; ++i) {
			auto bit = getNextBit();
			gamma <<= 1;
			gamma |= bit;
		}
		input[i] ^= gamma;
	}
	return input;
}

void GeffeGeneratorCipher::startAlg(string inputFilePath, string outFilePath) {
	ifstream inputFile(inputFilePath, ios::binary | ios::in);
	if (!inputFile.is_open()) {
		throw new exception("input file doesnt exist!");
	}
	vector<char> inputData((::istreambuf_iterator<char>(inputFile)),
		istreambuf_iterator<char>());
	auto result = startAlg(inputData);

	ofstream outFile(outFilePath, ios::binary);
	if (!outFile.is_open()) {
		throw new exception("output file error!");
	}
	for each (auto var in result) {
		outFile.write((char*)(&var), sizeof(char));
	}
}

int GeffeGeneratorCipher::generateKey(string out) {
	ofstream keyFile(out, ios::binary);
	if (!keyFile.is_open()) {
		throw new exception("cant open file");
	}
	std::mt19937 rng;
	rng.seed(time(NULL));
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, LONG_MAX);
	int rndKey = dist(rng);
	keyFile.write((char *)(&rndKey),sizeof(rndKey));
	return rndKey;
}

uint32_t GeffeGeneratorCipher::getNextBit() {
	auto first = getNextBitFirstLfsr();
	auto second = getNextBitSecondLfsr();
	auto third = getNextBitThirdLfsr();
	return (first & second) ^ (third & second) ^ (third);
}
void GeffeGeneratorCipher::setKeys(int32_t rawKey) {
	//16 bit	
	this->key = rawKey & 0xFFFF;
	//9 bit
	this->key1 = (rawKey & 0xFF0000) >> 17;
	//7 bit
	this->key2 = (rawKey & 0xFE000000) >> (16 + 9);
}
//x^16 + x^12 + x^3 + x + 1
uint32_t GeffeGeneratorCipher::getNextBitFirstLfsr() {
	key = ((((key >> 12) ^ (key >> 3) ^ (key >> 1) ^ (key)) & 1) << 15) | (key >> 1);
	return key & 1;
}
//x^7 + x + 1
uint32_t GeffeGeneratorCipher::getNextBitSecondLfsr() {
	key1 = ((((key1 >> 1) ^ (key1)) & 1) << 6) | (key1 >> 1);
	return key1 & 1;
}
//x^9 + x^4 + 1
uint32_t GeffeGeneratorCipher::getNextBitThirdLfsr() {
	key2 = ((((key2 >> 4) ^ key2) & 1) << 8) | (key2 >> 1);
	return key2 & 1;
}