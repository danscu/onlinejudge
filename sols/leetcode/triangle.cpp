class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        if (triangle.empty())
            return 0;

        if (triangle.size() == 1)
            return triangle[0][0];

        int n = triangle[triangle.size()-1].size();
        vector<int> lastrow;
        vector<int> minsum(n);

        lastrow = triangle[0];

        for (int i = 1; i < triangle.size(); i++) {
            for (int j = 0; j <= i; j++)
                minsum[j] = triangle[i][j] +
                	min( (j>=1 ? lastrow[j-1] :
                			lastrow[j]), (j<i ? lastrow[j] : lastrow[j-1]));
            lastrow = minsum;
        }

        return *min_element(minsum.begin(), minsum.end());
    }
};
