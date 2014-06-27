class Solution {
public:
    void nextPermutation(vector<int> &num) {
        int i = num.size() - 1, j = i;
        while (i > 0) {
            if (num[i - 1] < num[i]) {
                while (j > i && num[j] <= num[i - 1])
                    j--;
                swap(num[i-1], num[j]);
                break;
            }
            i--;
        }
        reverse(num.begin() + i, num.end());
    }
};
