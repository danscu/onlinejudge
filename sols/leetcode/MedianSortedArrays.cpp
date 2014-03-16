class Solution {
public:
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        int target, tot = m + n, need;
        if (tot == 0) return 0;

        if (tot & 1) {
            target = (tot + 1) / 2 - 1;
            need = 1;
        } else {
            target = tot / 2 - 1; // need 2
            need = 2;
        }

        int idx = 0, i = 0, j = 0;
        int num[2];

        int found = 0;
        while (i < m && j < n && found < need) {
            int cur;
            if (A[i] <= B[j])
                cur = A[i++];
            else
                cur = B[j++];
            if (idx++ == target) {
                num[found++] = cur;
                target++;
            }
        }

        while (found < need && i < m) {
            if (idx++ == target) {
                num[found++] = cur;
                target++;
            }
        }

        while (found < need && j < n) {
            if (idx++ == target) {
                num[found++] = cur;
                target++;
            }
        }

        if (need == 2)
            return ((double)num[0] + num[1]) / 2;
        else
            return num[0];
    }
};
