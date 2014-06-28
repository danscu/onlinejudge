/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

 struct IntervalSort {
     bool operator()(const Interval&a, const Interval&b) {
         return a.start < b.start || a.start == b.start && a.end < b.end;
     }
 } iSort;

class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals) {
        sort(intervals.begin(), intervals.end(), iSort);
        bool in = false;
        int curend = -1, curstart = -1;
        vector<Interval> res;
        for (int i = 0; i<intervals.size(); i++) {
            if (curstart >= 0 && intervals[i].start > curend) {
                res.push_back(Interval(curstart, curend));
                curstart = -1;
            } else
                curend = max(curend, intervals[i].end);
            if (curstart < 0) {
                curstart = intervals[i].start;
                curend = intervals[i].end;
            }
        }
        if (curstart>=0)
            res.push_back(Interval(curstart, curend));
        return res;
    }
};
