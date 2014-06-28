class Solution {
public:
    int maxSubArray(int A[], int n) {
        int i;
        int sum=INT_MIN;
        int res = sum;
        for (i=0;i<n;i++) {
            if (A[i]>=0)
                if (sum < 0)
                    sum = A[i];
                else
                    sum += A[i];
            else
                if (sum < 0)
                    sum = max(A[i], sum);
                else
                    sum += A[i];
            res = max(res, sum);
        }
        return res;
    }
};
