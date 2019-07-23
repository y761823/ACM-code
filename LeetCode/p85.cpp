class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix.front().empty())
            return 0;
        int n = matrix.size(), m = matrix.front().size(), res = 0;
        vector<int> heights(m);
        stack<int> stk;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                matrix[i][j] == '1' ? heights[j]++ : (heights[j] = 0);
            
            for (int j = 0; j <= m; ++j) {
                int h = j < m ? heights[j] : 0;
                while (!stk.empty() && heights[stk.top()] >= h) {
                    int t = stk.top(); stk.pop();
                    int pre = stk.empty() ? -1 : stk.top();
                    res = max(res, heights[t] * (j - 1 - pre));
                }
                stk.push(j);
            }
            stk.pop();
        }
        return res;
    }
};
