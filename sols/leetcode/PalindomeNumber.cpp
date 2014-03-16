class Solution {
public:
    bool isPalindrome(int x) {
        if (x<0) return false;
        if (x<10) return true;
        int i, n, m = 0;
        n = 0; int t = x; while (t) { t/=10; m=m?(m*10):1; n++; }
        for (i=0; i<=n/2; i++) {
            if (x / m % 10 != x % 10)
                return false;
            n /= 10; m /= 100;
        }
        return true;
    }
};
