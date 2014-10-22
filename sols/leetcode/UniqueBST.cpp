class Solution {
public:
    int numTrees(int n) {
        int C[n + 1]; memset(C, 0, sizeof(C)); C[0] = 1;
        // Cn = sum_{i=0}^{n-1} C_i C_{n-i-1}
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= i - 1; j++)
                C[i] += C[j] * C[i - j - 1];
        }
        return C[n];
    }
};
