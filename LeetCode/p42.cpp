class Solution {
public:
    int trap(vector<int>& height) {
        int lmax = 0, rmax = 0, lpos = 0, rpos = height.size() - 1, res = 0;
        while (lpos <= rpos) {
            if (lmax < rmax) {
                if (height[lpos] > lmax) lmax = height[lpos];
                else res += lmax - height[lpos];
                lpos++;
            } else {
                if (height[rpos] > rmax) rmax = height[rpos];
                else res += rmax - height[rpos];
                rpos--;
            }
        }
        return res;
    }
};
