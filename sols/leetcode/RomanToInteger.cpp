class Solution {
public:
    int romanToInt(string s) {
        char syms[] = "IVXLCDM??"; // add a place holder for consistency
        int nums[] = {1, 5, 10, 50, 100, 500, 1000, 5000};
        int num = 0;

        int si = 6; // si-->one, si+1-->five
        int i = 0, d = 0;
        while (i < s.length() && si >= 0) {
            char c = s[i];
            if (c == syms[si]) {
                d++;
            } else if (c == syms[si+1]) {
                if (d == 1)
                    d = 4;
                else if (d == 0)
                    d = 5;
            } else if (c == syms[si+2] && d == 1)
                d = 9;
            else {
                // not recognized char
                num += d * nums[si];
                si -= 2; d = 0;
                continue;
            }
            i++;
        }
        if (si >= 0)
            num += d * nums[si];
        return num;
    }
};
