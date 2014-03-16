class Solution {
public:
    string intToRoman(int num) {
        char syms[] = "IVXLCDM";
        int nums[] = {1, 5, 10, 50, 100, 500, 1000};

        // convert each digit
        char buf[64];
        int bi = 0, si = 0, j;
        while (num) {
            int d = num % 10;
            num /= 10;
            // convert digit to roman (reverse)
            if (d <= 3)
                for (j = 0; j < d; j++)
                    buf[bi++] = syms[si];
            else if (d == 4) {
                buf[bi++] = syms[si+1]; buf[bi++] = syms[si];
            } else if (d <= 8) {
                for (j = 0; j < d - 5; j++)
                    buf[bi++] = syms[si];
                buf[bi++] = syms[si+1];
            } else if (d == 9) {
                buf[bi++] = syms[si+2];
                buf[bi++] = syms[si];
            }
            si+=2;
        }
        buf[bi] = 0;
        reverse(buf, buf+bi);
        return string(buf);
    }
};
