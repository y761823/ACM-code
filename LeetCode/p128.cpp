class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> hash;
        for (int x : nums)
            hash.insert(x);
        
        int res = 0;
        while (!hash.empty()) {
            int x = *hash.begin(); hash.erase(x);
            int up = x, down = x;
            unordered_set<int>::iterator it;
            while ((it = hash.find(up + 1)) != hash.end()) {
                up++;
                hash.erase(it);
            }
            while ((it = hash.find(down - 1)) != hash.end()) {
                down--;
                hash.erase(it);
            }
            res = max(res, up - down + 1);
        }
        return res;
    }
};
