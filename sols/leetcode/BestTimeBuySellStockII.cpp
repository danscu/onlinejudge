class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int min, max, last;
        int profit = 0;
        int totalProfit = 0;

        if (prices.empty())
            return 0;

        last = min = max = prices[0];

        int i, n = prices.size();
        for (i = 1; i < n; i++) {
            int pri = prices[i];
            if (pri < last) {
                profit = last - min;
                if (profit > 0)
                    totalProfit += profit;
                profit = 0;
                min = max = pri;
            }
            if (pri < min) {
                min = max = pri;
                totalProfit += profit;
                profit = 0;
            }
            if (pri > max) {
                max = pri;
                if (max - min > profit)
                    profit = max - min;
            }
            last = pri;
        }

        totalProfit += profit;

        return totalProfit;
    }
};
