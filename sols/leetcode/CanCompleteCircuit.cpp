class Solution {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        int cnt = 0, round = 0;
        int i = 0, n = gas.size();
        int g = 0;
        while (cnt < n) {
            g += gas[i] - cost[i];
            if (g < 0) {
                cnt = 0;
                g = 0; // start from i
            } else cnt++;
            if (++i == n) {
                i = 0; round++;
                if (round == 2) break;
            }
        }
        if (cnt == n) return i; else return -1;
    }
};
