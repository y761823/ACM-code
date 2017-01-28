class Solution {
public:
    int jump(vector<int>& nums) {
        int last = 0, now = 0, res = 0, n = nums.size();
        while (now < n - 1) {
            if (now + nums[now] >= n - 1)
                return res + 1;
            
            int newlast = now + nums[now], nxt = now;
            for (int i = last; i <= newlast; ++i)
                if (i + nums[i] > nxt + nums[nxt]) nxt = i;
            last = newlast + 1;
            now = nxt;
            res++;
        }
        return res;
    }
};
