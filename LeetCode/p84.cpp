class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stk;
        int res = 0;
        for (int i = 0, n = heights.size(); i <= n; ++i) {
            int h = i < n ? heights[i] : 0;
            while (!stk.empty() && heights[stk.top()] >= h) {
                int t = stk.top(); stk.pop();
                int pre = stk.empty() ? -1 : stk.top();
                res = max(res, heights[t] * (i - 1 - pre));
            }
            stk.push(i);
        }
        return res;
    }
};
