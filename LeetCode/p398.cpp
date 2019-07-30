class Solution {
public:
    Solution(vector<int>& nums)
        : arr(nums) {
        srand(time(NULL));
    }
    
    int pick(int target) {
        int res = -1, cnt = 0;
        for (int i = 0, n = arr.size(); i < n; ++i) {
            if (arr[i] == target && rand() % ++cnt == 0) {
                res = i;
            }
        }
        return res;
    }
    
private:
    vector<int>& arr;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */
