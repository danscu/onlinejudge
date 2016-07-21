// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int low = 1, high = n;
        while (low < high) {
            int mid = low + (high - low) / 2;
            int r = guess(mid);
            if (!r) return mid;
            if (r == -1) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
};
