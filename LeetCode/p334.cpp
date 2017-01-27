class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int curMin = 0x7fffffff, curMin2 = curMin; // inf
        for(vector<int>::iterator it = nums.begin(); it != nums.end(); ++it) {
            if(*it > curMin2)
                return true;
            if(*it > curMin)
                curMin2 = min(curMin2, *it);
            curMin = min(curMin, *it);
        }
        return false;
    }
};
