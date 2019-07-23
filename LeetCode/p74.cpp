class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix.front().empty())
            return false;
        int n = matrix.size(), m = matrix.front().size();
        int l = 0, r = n * m;
        while (l < r) {
            int mid = (l + r) / 2;
            if (matrix[mid / m][mid % m] < target)
                l = mid + 1;
            else
                r = mid;
        }
        return l < n * m && matrix[l / m][l % m] == target;
    }
};
