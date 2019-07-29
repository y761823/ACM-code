class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        a.resize(n);
        for (int i = 0; i < n; ++i)
            a[i] = make_pair(i, nums[i]);
        res = vector<int>(n);
        tmp.resize(n);
        
        mergeSort(0, n - 1);
        return res;
    }
    
    void mergeSort(int l, int r) {
        if (l < r) {
            int mid = (l + r) / 2;
            mergeSort(l, mid);
            mergeSort(mid + 1, r);
            
            int i = l, j = mid + 1, k = 0;
            while (i <= mid || j <= r) {
                if (j > r || (i <= mid && a[i].second <= a[j].second)) {
                    res[a[i].first] += j - mid - 1;
                    tmp[k++] = a[i++];
                } else {
                    tmp[k++] = a[j++];
                }
            }
            copy(tmp.begin(), tmp.begin() + k, a.begin() + l);
        }
    }
    
private:
    vector<pair<int, int>> a, tmp;
    vector<int> res;
};
