class Solution {
public:
    vector<int> twoSum(vector<int>& a, int target) {
        for (int l = 0, r = a.size() - 1; l < r; ++l) {
            while (l < r && a[l] + a[r] > target) --r;
            if (l < r && a[l] + a[r] == target)
                return {l + 1, r + 1};
        }
        return {0, 0};
    }
};
