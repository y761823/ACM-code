class Solution {
public:
    int maxArea(vector<int>& height) {
        int res = 0, l = 0, r = (int)height.size() - 1;
        while (l < r) {
            if (height[l] < height[r])
                res = max(res, (r - l) * height[l]), l++;
            else
                res = max(res, (r - l) * height[r]), r--;
        }
        return res;
    }
};
