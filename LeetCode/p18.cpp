class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<int>& a = nums;
        sort(a.begin(), a.end());
        int n = a.size();
        vector<vector<int>> res;
        
        for (int i = 0; i < n; ++i) {
            if (i > 0 && a[i] == a[i - 1]) continue;
            
            for (int j = i + 1; j < n; ++j) {
                if (j > i + 1 && a[j] == a[j - 1]) continue;
                
                for(int k = j + 1, l = n - 1; k < n; ++k) {
                    if (k > j + 1 && a[k] == a[k - 1]) continue;
                    
                    while (k < l && a[i] + a[j] + a[k] + a[l] > target)
                        l--;
                    if (k < l && a[i] + a[j] + a[k] + a[l] == target)
                        res.push_back({a[i], a[j], a[k], a[l]});
                }
            }
        }
        
        return res;
    }
};
