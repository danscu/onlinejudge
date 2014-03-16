class Solution {
public:
    int reverse(int x) {
        int s = x >= 0 ? 1 : -1;
        int n = 0;
        x = abs(x);
        while (x) {
            n = n * 10 + x % 10;
            x /= 10;
        }
        return s * n;
    }
};
