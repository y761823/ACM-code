class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        size_t l = 0, n = nums.size();
        while (l < n) {
            int cur = l;
            while (cur + 1 < n && nums[cur] + 1 == nums[cur + 1])
                cur++;
            res.push_back(buildStr(nums[l], nums[cur]));
            l = cur + 1;
        }
        return res;
    }
    
    string buildStr(int l, int r) {
        char buff[256];
        if (l == r)
            sprintf(buff, "%d", l);
        else
            sprintf(buff, "%d->%d", l, r);
        return buff;
    }
};
