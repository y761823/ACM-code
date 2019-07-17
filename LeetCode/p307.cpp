class NumArray {
public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        tree = vector<int>(n + 1);
        for (int i = 0; i < n; ++i)
            tUpdate(i + 1, nums[i]);
    }
    
    void update(int i, int val) {
        int old = sumRange(i, i);
        tUpdate(i + 1, val - old);
    }
    
    int sumRange(int i, int j) {
        return tQuery(j + 1) - tQuery(i);
    }
    
private:
    int lowbit(int x) {
        return x & -x;
    }
    
    void tUpdate(int p, int v) {
        while (p <= n) {
            tree[p] += v;
            p += lowbit(p);
        }
    }
    
    int tQuery(int p) {
        int res = 0;
        while (p) {
            res += tree[p];
            p -= lowbit(p);
        }
        return res;
    }
    
    vector<int> tree;
    int n;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */
