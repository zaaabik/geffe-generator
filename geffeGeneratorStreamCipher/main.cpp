#include<iostream>
#include<math.h>
#include"GeffeGeneratorCipher.h"
#include"SequenceTest.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

using namespace std;
int main(int argc, char** argv){
	const string outKey = "-o";
	const string inKey = "-i";
	const string keyFileKey = "-k";
	const string generatKeyFileMode = "-g";
	const string encryptMode = "encr/decr";
	const string mode = "mode";
	const string cmdArgsErrorMsg = "invalid keys";
	const string defaultOut = "out.txt";
	const string defaultIn = "in.txt";
	const string defaultKey = "key.txt";
	const string testsKey = "-t";

	auto argMap = map<string, string>({
		{mode,encryptMode},
		{outKey,defaultOut},
		{inKey,defaultIn},
		{keyFileKey,defaultKey},
	});
	for (int i = 1; i < argc; ++i) {
		if (argv[i] == outKey) {
			if (!(i + 1 < argc)) {
				cout << cmdArgsErrorMsg;
				return 0;
			}
			argMap[outKey] = argv[i + 1];
		}else if (argv[i] == inKey) {
			if (!(i + 1 < argc)) {
				cout << cmdArgsErrorMsg;
				return 0;
			}
			argMap[inKey] = argv[i + 1];
		}else if (argv[i] == keyFileKey) {
			if (!(i + 1 < argc)) {
				cout << cmdArgsErrorMsg;
				return 0;
			}
			argMap[keyFileKey] = argv[i + 1];
		} else if (argv[i] == generatKeyFileMode) {
			argMap[mode] = generatKeyFileMode;
		} else if (argv[i] == testsKey) {
			argMap[mode] = testsKey;
		}
	}
	if (argMap[mode] == generatKeyFileMode) {
		GeffeGeneratorCipher::generateKey(argMap[outKey]);
	} else if (argMap[mode] == testsKey) {	
		srand(time(NULL));
		auto key = GeffeGeneratorCipher::generateKey(argMap[outKey]);	
		auto cipher = GeffeGeneratorCipher(key);
		auto bits = vector<char>();
		for (int i = 0; i < pow(2, 18); ++i) {
			bits.push_back(cipher.getNextBit());
			bits.push_back(rand() % 2);		
		}
		
		SequenceTest::freqTest(bits);
		SequenceTest::seqFreqTest(bits);
		SequenceTest::serialTest(bits);
		SequenceTest::autoTest(bits);
		SequenceTest::universalTest(bits);
		return 0;
	} else {
		if (argMap.find(keyFileKey) == argMap.end()) {
			cout << "key file does not set";
			return 0;
		}
		try {
			auto cipher = GeffeGeneratorCipher(argMap[keyFileKey]);
			cipher.startAlg(argMap[inKey], argMap[outKey]);
		} catch (exception* e) {
			cout << e->what();
		}
	}	

    return 0;
}

