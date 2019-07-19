class Solution {
public:
    int findMin(vector<int>& nums) {
        function<int(int, int)> dfs = [&](int l, int r) {
            if (l + 5 >= r)
                return *min_element(nums.begin() + l, nums.begin() + r);
            int res = nums[l], ll = l + 1, rr = r;
            while (ll < rr) {
                int mid = (ll + rr) / 2;
                if (nums[l] == nums[mid]) {
                    res = min(res, dfs(mid, rr));
                    if (rr < r)
                        res = min(res, nums[rr]);
                    rr = mid;
                } else if (nums[l] < nums[mid]) {
                    ll = mid + 1;
                } else {
                    rr = mid;
                }
            }
            if (ll < r) res = min(res, nums[ll]);
            return res;
        };
        return dfs(0, nums.size());
    }
};
