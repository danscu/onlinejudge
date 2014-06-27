#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int firstMissingValue(int A[], int n) {
        int *imin = min_element(A, A+n);
        int minval = *imin;

        int i = 0;
        while (i<n) {
        	int v = A[i];
        	if (v - minval < n && A[v-minval] != v)
        		swap(A[v-minval], A[i]);
        	else
        		i++;
        }

        for (i=0;i<n;i++)
            if (A[i] != i+minval)
                return i+minval;

        return minval+n;
    }
};

int main() {
	int a[] = {-1,4,2,1,9,10};
	Solution s;
	std::cout << s.firstMissingValue(a,sizeof(a)/sizeof(a[0]));
}
