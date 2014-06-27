#include <iostream>

class Solution {
public:
    int binsearch(int a[], int lo, int hi, int target)
    {
        int m;
        while (lo < hi) {
            m = (lo + hi) / 2;
            if (target > a[m])
                lo = m + 1;
            else
                hi = m;
        }
        return a[lo] == target ? lo : -1;
    }

    int search(int a[], int n, int target) {
        // search for the split
        int lo, hi, mid, sp;
        int res;
        lo = 0, hi = n - 1; // search for start of the split
        if (a[lo] > a[hi]) {
            while (lo < hi) {
                sp = (lo + hi) / 2;
                if (a[lo] < a[sp])
                    lo = sp + 1;
                else
                    hi = sp;
            }
            sp = lo;
        } else sp = -1;

        if (sp >= 0) {
            res = binsearch(a, 0, sp, target);
            if (res >= 0)
                return res;
        }

        res = binsearch(a, sp + 1, n - 1, target);
        return res;
    }
};

int main() {
	int a[] = {3,5,1};
	Solution s;
	std::cout << s.search(a, 3, 1) << std::endl;
}
