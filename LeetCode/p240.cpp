class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty())
            return false;
        int n = matrix.size(), m = matrix.front().size(), r = 0, c = m - 1;
        while (r < n && c >= 0) {
            int v = matrix[r][c];
            if (v == target)
                return true;
            else if (v < target)
                r++;
            else
                c--;
        }
        return false;
    }
};
