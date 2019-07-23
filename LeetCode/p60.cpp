class Solution {
public:
    string getPermutation(int n, int k) {
        int fact[n + 1] = {1};
        for (int i = 1; i <= n; ++i)
            fact[i] = fact[i - 1] * i;
        
        bool used[n + 1] = {};
        
        string res;
        for (int i = n - 1; i >= 0; --i) {
            int cur = 1;
            while (fact[i] * cur < k)
                cur++;
            k -= fact[i] * (cur - 1);
            
            for (int j = 1; j <= cur; ++j)
                cur += used[j];
            used[cur] = true;
            res.push_back(cur + '0');
        }
        return res;
    }
};
