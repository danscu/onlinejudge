class Solution {
public:
    int maxArea(vector<int> &height) {
        int maxa = 0;
        int i,j;
        list<int> curv; // index
        for(i=0;i<height.size();i++) {
            int localArea = 0;
            int fi;
            while (!curv.empty() && height[fi = curv.back()] < height[i])
                curv.pop_back();
            if (!curv.empty()) {
                localArea += (i - fi) * height[fi];
                maxa = max(maxa, localArea);
            }
            curv.push_back(i);
        }
        return maxa;
    }
};
