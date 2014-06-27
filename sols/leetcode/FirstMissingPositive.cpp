// store value x at position A[x-1] (if x >= 1)
// scan for missing one

#include <iostream>
#include <algorithm>

using namespace std;
class Solution {
public:
    int firstMissingPositive(int A[], int n) {
        int i = 0;
        while (i<n) {
        	int v = A[i];
        	if (v >= 1 && v - 1 < n && A[v-1] != v)
        		swap(A[v-1], A[i]);
        	else
				i++;
        }

        for (i=0;i<n;i++)
            if (A[i] != i+1)
                return i+1;

        return n+1;
    }
};

int main() {
	int a[] = {-1,4,2,1,9,10};
	Solution s;
	std::cout << s.firstMissingPositive(a,sizeof(a)/sizeof(a[0]));
}
