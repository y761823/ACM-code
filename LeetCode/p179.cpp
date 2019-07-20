class Solution {
public:
    string largestNumber(vector<int>& nums) {
        string(*itos)(int) = to_string;
        vector<string> strs(nums.size());
        transform(nums.begin(), nums.end(), strs.begin(), itos);
        sort(strs.begin(), strs.end(), [](const string& lhs, const string& rhs) {
            return lhs + rhs > rhs + lhs;
        });
        string res;
        for (const string& x : strs)
            res += x;
        return res.empty() || res.front() == '0' ? "0" : res;
    }
};
