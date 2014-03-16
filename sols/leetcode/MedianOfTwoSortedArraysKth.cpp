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
    int findkth(int k, int A[], int m, int B[], int n) {
    	// m <= n
    	if (m == 0)
    		return B[k-1];
    	if (k==1)
    		return min(A[0],B[0]);
    	int pa = min(k/2, m), pb = k - pa;
    	if (A[pa - 1] < B[pb - 1])
    		return findkth(k - pa, A + pa, m - pa, B, n - pb);
    	else if (A[pa - 1] > B[pb - 1])
    		return findkth(k - pb, A, m, B + pb, n - pb);
    	else
    		return A[pa - 1];
    }

    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        int k, tot = m + n, need;
        int idx = 0, i = 0, j = 0;

        if (tot == 0) return 0;

        // assume m <= n
        if (m > n) {
            swap(A, B); swap(m, n);
        }

        if (tot & 1) {
            k = (tot + 1) / 2 - 1;
            need = 1;
        } else {
            k = tot / 2 - 1; // need 2
            need = 2;
        }

        int num[2];
        num[0] = findkth(k + 1, A, m, B, n);
        if (need == 2)
            num[1] = findkth(k + 2, A, m, B, n);

done:
        if (need == 2)
            return ((double)num[0] + num[1]) / 2;
        else
            return num[0];
    }
};

int main() {
	Solution sn;
	int A1[] = {1,2};
	int B1[] = {1,1};
	cout << sn.findMedianSortedArrays(A1, 2, B1, 2) << endl;

	int A2[] = {1,1};
	int B2[] = {1,1};
	cout << sn.findMedianSortedArrays(A2, 2, B2, 2) << endl;

	int A3[] = {1,1,1};
	int B3[] = {1,1,1};
	cout << sn.findMedianSortedArrays(A3, 3, B3, 3) << endl;

	int A4[] = {100001};
	int B4[] = {100000};
	cout << sn.findMedianSortedArrays(A4, 1, B4, 1) << endl;

	int A5[] = {1,2};
	cout << sn.findMedianSortedArrays(A5, 2, A5, 2) << endl;

	int A6[] = {1,1};
	int B6[] = {1,2};
	cout << sn.findMedianSortedArrays(A6, 2, B6, 2) << endl;

	int A7[] = {1,2};
	int B7[] = {1,2,3};
	cout << sn.findMedianSortedArrays(A7, 2, B7, 3) << endl;

	return 0;
}
