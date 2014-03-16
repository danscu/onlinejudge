/* O(n) time, forward/backward algorithm */

public class Solution {
    
	// make this function dynamic
	int min1, max1, profit1;
	int min2, max2, profit2;

	void updateBest1(int pri) {
        if (pri <= min1) {
        	min1 = max1 = pri;
        }
        if (pri >= max1) {
        	max1 = pri;
            if (max1 - min1 > profit1)
            	profit1 = max1 - min1;
        }
    }
    
    void updateBest2(int pri) {
        if (pri <= min2) {
        	min2 = pri;
        	if (max2 - min2 > profit2)
        		profit2 = max2 - min2;
        }
        if (pri >= max2) {
        	min2 = max2 = pri;
        }
    }
    
    public int maxProfit(int[] prices) {
        int n = prices.length;
        
        if (n < 2)
            return 0;
        
        int i;
        
        int profits1[] = new int[n];
        int profits2[] = new int[n];
        
        min1 = Integer.MAX_VALUE;
        max1 = 0;
        profit1 = 0;
        
        for (i = 0; i < n; i++) {
        	updateBest1(prices[i]);
        	profits1[i] = profit1;
        }
        
        min2 = Integer.MAX_VALUE;
        max2 = 0;
        profit2 = 0;
        
        for (i = n - 1; i >= 0; i--) {
        	updateBest2(prices[i]);
        	profits2[i] = profit2;
        }

		int profit = 0;

		for (i = 0; i < n; i++) {
        	profit = Math.max(profit, profits1[i] + profits2[i]);
        }

        return profit;
    }
}