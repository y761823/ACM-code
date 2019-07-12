class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        if (nums.empty())
            return {};
        int x = nums.front(), cx = 0, y = nums.front(), cy = 0;
        for (int i : nums) {
            if (i == x)
                cx++;
            else if (i == y)
                cy++;
            else if (cx == 0)
                x = i, cx++;
            else if (cy == 0)
                y = i, cy++;
            else
                cx--, cy--;
        }
        
        vector<int> res;
        int k = nums.size() / 3;
        if (cx && count(nums.begin(), nums.end(), x) > k)
            res.push_back(x);
        if (cy && count(nums.begin(), nums.end(), y) > k)
            res.push_back(y);
        return res;
    }
};
