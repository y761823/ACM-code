/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), [](Interval a, Interval b) {
            return a.start < b.start;
        });
        vector<Interval> res;
        for (auto& x : intervals) {
            if (res.empty() || res.back().end < x.start)
                res.push_back(x);
            else if (res.back().end < x.end)
                res.back().end = x.end;
        }
        return res;
    }
};
