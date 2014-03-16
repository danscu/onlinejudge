/*
 * This solutions is TLE (Time limit exeeded)
 * 
 * Need to improve to O(n^2)
 */

public class Solution {
    
    // m[i][j]: i last transaction day
    //          j remaining transactions
    
    // m[i][j+1] = max_{k=0,i-1} m[k][j] + best(i, N-1)
    // best(a, b): best pair of buy and sell within days [a, b]
    
    // init: m[i][0] = 0
    
    // best(a, b) = search from a to b
    
    // Time complexity: O(n^3)
    
    int best(int[] prices, int a, int b) {
        int i;
        int min = Integer.MAX_VALUE;
        int max = 0;
        int profit = 0;

        for (i = a; i < b; i++) {
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
    
    public int maxProfit(int[] prices) {
        int n = prices.length;
        
        if (n == 0)
            return 0;
        
        int m[][];
        int i,j,k;
        m = new int[n][3];
        
        // init
        for (i=0; i<n; i++)
            m[i][0] = 0;
        
        // DP
        for (j = 1; j <= 2; j++) {
            for (i = 0; i < n; i++) {
                m[i][j] = 0;
                for (k = 0; k < i; k++) {
                    int profit = m[k][j] + best(prices, i, n);
                    if (profit > m[i][j])
                        m[i][j] = profit;
                }
            }
        }
        
        return m[n-1][2];
    }
}