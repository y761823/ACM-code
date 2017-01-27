class Solution {
public:
    int target;
    
    bool search(vector<int>& a, int l, int r) {
        if (l > r) return false;
        if (l == r) return a[l] == target;
        
        if (a[l] == target) return true;
        
        int mid = (l + r) >> 1;
        if (a[mid] == a[l])
            return search(a, l + 1, mid - 1) || search(a, mid + 1, r);
        if (a[l] < a[mid]) {
            if (a[l] <= target && target <= a[mid])
                return *lower_bound(a.begin() + l, a.begin() + mid + 1, target) == target;
            return search(a, mid + 1, r);
        } else {
            if (a[mid] <= target && target <= a[r])
                return *lower_bound(a.begin() + mid, a.begin() + r + 1, target) == target;
            return search(a, l + 1, mid - 1);
        }
    }

    bool search(vector<int>& nums, int _target) {
        if (nums.empty()) return false;
        target = _target;
        return search(nums, 0, (int)nums.size() - 1);
    }
};
