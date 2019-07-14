class Solution {
public:
    struct Node {
        int val, pos;
    };
    
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        n = nums.size(), this->k = k;
        que.clear();
        
        for (int i = 0; i < n; ++i) {
            push(nums[i], i);
            if (i + 1 >= k)
                res.push_back(que.back().val);
        }
        
        return res;
    }
    
    void push(int val, int pos) {
        if (!que.empty() && que.back().pos <= pos - k)
            que.pop_back();
        while (!que.empty() && que.front().val <= val)
            que.pop_front();
        que.push_front({val, pos});
    }
    
private:
    deque<Node> que;
    int n, k;
};
