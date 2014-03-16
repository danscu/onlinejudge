class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int min = INT_MAX, max = -1;
        int profit = 0;

        int i, n = prices.size();
        for (i = 0; i < n; i++) {
            int pri = prices[i];
            if (pri < min) {
                min = max = pri;
            }
            if (pri > max) {
                max = pri;
                if (max - min > profit)
                    profit = max - min;
            }
        }

        return profit;
    }
};
