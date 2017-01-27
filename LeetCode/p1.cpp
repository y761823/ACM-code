class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashmap;
        for (int i = 0; i < (int)nums.size(); ++i) {
            int x = nums[i];
            auto it = hashmap.find(target - x);
            if (it != hashmap.end())
                return {it->second, i};
            hashmap.insert(make_pair(x, i));
        }
        return {};
    }
};
