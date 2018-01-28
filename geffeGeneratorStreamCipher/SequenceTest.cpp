#include "SequenceTest.h"
#include"GeffeGeneratorCipher.h"
#include<iostream>
#include <iomanip>
#define ll long long int
using namespace std;

void SequenceTest::freqTest(vector<char> bits) {
	long long int oneCount = 0;
	int size = bits.size();
	for (int i = 0; i < size; ++i) {
		oneCount += bits[i];
	}
	auto result = pow((oneCount - (size - oneCount)), 2) / size;
	cout << result;
	if (abs(result) < 3) {
		cout << " frequency test have passed" << endl;
	} else {
		cout << " frequency test have not passed" << endl;
	}
}

void SequenceTest::seqFreqTest(vector<char> bits) {
	int l = 8;
	vector<int> numberCount(static_cast<int>(pow(2,l)));
	auto chi2 = 294.32;
	for (int i = 0; i < bits.size(); i += L) {
		auto tmp = 0;
		for (int j = 0; j < L; ++j) {
			tmp ^= (bits[i + j] << j);
		}
		numberCount[tmp]++;
	}
	auto res = 0.;
	auto length = bits.size() - (bits.size() % L);
	auto prob = (length / (L*pow(2, L)));
	for (auto i : numberCount) {
		res += pow((i) - prob, 2);
	}
	res /= prob;
	cout << res;
	if (res < chi2)
		cout << " sequence frequency test have passed!" << endl;
	else
		cout << " sequence frequency test have not passed!" << endl;
}

void SequenceTest::serialTest(vector<char> bits) {
	int l = 15;
	auto chi2 = 45.25;
	int n = bits.size();
	vector<ll> oneSeq(l + 1);
	vector<ll> zeroSeq(l + 1);

	int lenOne = 0;
	int lenZero = 0;
	for (int i = 0; i < n; ++i) {
		if (bits[i] == 1) {
			lenOne++;
			if (lenZero <= l) {
				zeroSeq[lenZero]++;
			}
			lenZero = 0;
		} else {
			lenZero++;
			if (lenOne <= l) {
				oneSeq[lenOne]++;
			}
			lenOne = 0;
		}
	}
	auto once = 0.;
	auto zeros = 0.;
	auto result = 0.;

	for (int i = 1; i <= l; ++i) {
		auto devider = n / pow(2, i + 2);
		once += pow(oneSeq[i] - devider,2)/devider;
		zeros = pow(zeroSeq[i] - devider,2)/devider;		
	}
	double res = once + zeros;
	cout << res;
	if (res < chi2)
		cout << " serial test have passed!" << endl;
	else
		cout << " serial test have not passed!" << endl;
}

void SequenceTest::autoTest(vector<char> bits) {
	int n = bits.size();
	int ones = 0;
	int errors = 0;
	for (int tau = 10; tau < 30; tau+=1) {
		n = (n - tau);
		for (int j = 0; j < n; ++j) {
			bits[j] ^ bits[j + tau] == 1 ? ones++ : 0;
		}
		auto res = (2.0 / sqrt(n) * (ones - n / 2.0));
		if (abs(res) > 3)
			errors++;
		ones = 0;
	}
	if (errors == 0)
		cout << " autocorrelation test have passed!" << endl;
	else
		cout << " autocorrelation test have not passed!" << endl;
}

void SequenceTest::universalTest(vector<char> bits) {
	int l = 8;
	int n = bits.size();
	
	auto v = pow(2,l);
	int q = (v * 10);
	auto k = (n - q) / l;

	vector<int> tab(v);
	vector<int> block;

	int tmp = 0;
	int pos = 0;
	int len = 0;

	for (int i = 0; i < n;++i) {
		tmp += bits[i] << pos;
		pos++;
		if (pos == l) {
			block.push_back(tmp);
			pos = 0;
			tmp = 0;
		}
	}
	for (int i = 0; i < q; ++i) {
		int tmp = block[i];	
		tab[tmp] = i;
	}

	auto sum = 0.;

	for (int i = q + 1; i < q + k; ++i) {
		int tmp = block[i];
		sum += log(i - tab[tmp]);
		tab[tmp] = i;
	}

	sum = (sum / k);
	double e = 7.1836656;
	double d = 3.238;
	double C = 0.7 - 0.8 / L + ((4 + 32 / L) * pow(k, -(double)3 / L)) / 15;
	double result = (sum - e) / (C * (d));

	cout << setprecision(10) << result;

	if (abs(result) < 1.96)
		cout << " universal test have passed!" << endl;
	else
		cout << " universal test have not passed!" << endl;
}