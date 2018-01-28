#pragma once
#include<string>
#include<vector>
using namespace std;
static class SequenceTest {
public:
	static void freqTest(vector<char> bits);
	static void seqFreqTest(vector<char> bits);
	static void serialTest(vector<char> bits);
	static void autoTest(vector<char> bits);
	static void universalTest(vector<char> bits);
private:
	static const int L = 8;
};