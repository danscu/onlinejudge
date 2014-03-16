class Solution {
public:
    int singleNumber(int A[], int n) {
        int i;
        int single = 0;
        for (i = 0; i < n; i++)
            single ^= A[i];
        return single;
    }
};
