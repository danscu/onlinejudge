class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        int w = m + n - 1;
        int ra = m - 1;
        int rb = n - 1;

        // copy loop
        while (ra >= 0 && rb >= 0) {
            if (B[rb] > A[ra])
                A[w--] = B[rb--];
            else
                A[w--] = A[ra--];
        }

        // copy rest B
        while (rb >= 0)
            A[w--] = B[rb--];
    }
};
