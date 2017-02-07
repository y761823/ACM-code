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
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> res;
        auto it = intervals.begin();
        for (; it != intervals.end(); ++it) {
            if (it->end < newInterval.start) {
                res.push_back(*it);
                continue;
            }
            if (newInterval.end < it->start)
                break;
            if (it->start < newInterval.start) newInterval.start = it->start;
            if (newInterval.end < it->end) newInterval.end = it->end;
        }
        res.push_back(newInterval);
        copy(it, intervals.end(), back_insert_iterator<vector<Interval>>(res));
        return res;
    }
};
