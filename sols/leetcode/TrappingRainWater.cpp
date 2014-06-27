#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int trap(int A[], int n) {
        vector<int> st;
        vector<int> maxL(n), maxR(n);
        int i;

        int mL = -1, mR = -1;
        for (i=0;i<n;i++) {
        	maxL[i] = mL;
        	if (mL == -1 || A[i] > A[mL])
        		mL = i;
        	maxR[n-i-1] = mR;
        	if (mR == -1 || A[n-i-1] > A[mR])
        		mR = n-i-1;
        }

        int water = 0;
        for (i=0;i<n;i++) {
        	int lH = maxL[i] == -1 ? 0 : A[maxL[i]];
        	int rH = maxR[i] == -1 ? 0 : A[maxR[i]];
        	water += max(0, min(lH,rH) - A[i]);
        }

        return water;
    }
};

int main() {
	Solution s;
	int A[]={5,2,1,2,1,5};
	cout<<s.trap(A,6)<<endl;
	int B[]={4,2,0,3,2,5};
	cout<<s.trap(B,6)<<endl;
	int C[]={6,4,2,0,3,2,0,3,1,4,5,3,2,7,5,3,0,1,2,1,3,4,6,8,1,3};
	cout<<s.trap(C,sizeof(C)/sizeof(C[0]))<<endl;
}
