#include <iostream>
#include <vector>
using namespace std;

//----------------------------
//Returns a vector containing the zero based index of
//  the start of each match of the string K in S.
//  Matches may overlap
//----------------------------
vector<int> KMP(string S, string K) {
	vector<int> T(K.size() + 1, -1);
	vector<int> matches;

	if (K.size() == 0)
	{
		matches.push_back(0);
		return matches;
	}

	// KMP table
	for(int i = 1; i <= (int)K.size(); i++)
	{
		int pos = T[i - 1];
		while (pos != -1 && K[pos] != K[i - 1]) pos = T[pos];
		T[i] = pos + 1;
	}

	// Search
	int sp = 0;
	int kp = 0;
	while(sp < S.size())
	{
		while(kp != -1 && (kp == K.size() || K[kp] != S[sp])) kp = T[kp];
		kp++;
		sp++;
		if(kp == K.size()) matches.push_back(sp - K.size());
	}

	return matches;
}

int main() {
	vector<int> matches = KMP("ABCABCDABABCDABCDABDE", "ABCDABD");
	for (vector<int>::iterator it = matches.begin(); it!=matches.end(); ++it)
		cout << *it << " ";
	cout << endl;
	return 0;
}
