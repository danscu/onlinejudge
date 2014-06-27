class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        vector<int> r;
        int lo, hi, first, last, m;
        lo = 0; hi = n - 1;
        while (lo < hi) {
            m = (lo+hi) / 2;
            if (A[m] < target)
                lo = m + 1;
            else
                hi = m;
        }
        if (A[lo] != target) {
            r.push_back(-1); r.push_back(-1);
            return r;
        }
        first = lo;

        lo = 0; hi = n - 1;
        while (lo < hi) {
            m = (lo+hi+1)/2;
            if (A[m] <= target)
                lo = m;
            else
                hi = m - 1;
        }

        last = hi;

        r.push_back(first); r.push_back(last);
        return r;
    }
};
