#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <climits>
#include <cfloat>
#include <cmath>
#include <map>
#include <list>

using namespace std;

class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if (n <= 1)
            return n;

        int w = 1, r = 1;
        int last = A[0];

        while (r < n) {
            if (A[r] != last)
                A[w++] = last = A[r];
            r++;
        }

        return w;
    }
};

int main() {
	Solution sn;
	int A[] = {1,1,2,3};
	cout << sn.removeDuplicates(A, 4);
}
