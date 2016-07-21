class Solution {
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int, int>> res;
        int p = 0, q = 0;
        int np, nq;

        if (k > 0 && nums1.size() && nums2.size())
            res.push_back(make_pair(nums1[0], nums2[0]));

        for (int i = 1; i < k && p < nums1.size() && q < nums2.size();) {
            bool takeUp, takeDown = false;
            if (nums2.size() - 1 == q)
                takeUp = true, takeDown = false;
            else if (nums1.size() - 1 == p)
                takeUp = false, takeDown = true;
            else {
                takeUp = nums1[p + 1] + nums2[q] <= nums1[p] + nums2[q + 1];
                takeDown = nums1[p + 1] + nums2[q] >= nums1[p] + nums2[q + 1];
            }

            if (takeUp) {
                res.push_back(make_pair(nums1[np = p + 1], nums2[nq = q]));
                i++;
            }

            if (i == k)
                break;

            if (takeDown) {
                res.push_back(make_pair(nums1[p], nums2[nq = q + 1]));
                np = p + 1;
                i++;
            }

            p = np, q = nq;
        }

        return res;
    }
};
