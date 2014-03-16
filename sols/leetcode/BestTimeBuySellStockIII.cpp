// Need to fix
// Need to generate longest holds

/*
Input:		[1,2,4,2,5,7,2,4,9,0]
Output:		12
Expected:	13
*/

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int min, max, last;
        int profit = 0;
        int totalProfit = 0;

        int best1 = 0, best2 = 0;

        if (prices.empty())
            return 0;

        last = min = max = prices[0];

        int i, n = prices.size();
        for (i = 1; i < n; i++) {
            int pri = prices[i];
            if (pri < last) {
                profit = last - min;
                if (profit > 0) {
                    // totalProfit += profit;
                    if (profit >= best1) {
                        best2 = best1;
                        best1 = profit;
                    } else if (profit > best2)
                        best2 = profit;
                }
                profit = 0;
                // TODO should not reset min/max here
                min = max = pri;
            }
            if (pri < min) {
                min = max = pri;
                // totalProfit += profit;
                if (profit >= best1) {
                    best2 = best1;
                    best1 = profit;
                } else if (profit > best2)
                    best2 = profit;

                profit = 0;
            }
            if (pri > max) {
                max = pri;
                if (max - min > profit)
                    profit = max - min;
            }
            last = pri;
        }

        // totalProfit += profit;
        if (profit >= best1) {
            best2 = best1;
            best1 = profit;
        } else if (profit > best2)
            best2 = profit;

        return best1 + best2;
    }
};
