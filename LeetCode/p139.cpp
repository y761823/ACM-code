class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp(s.size() + 1, 0);
        dp[s.size()] = true;
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        
        for (int i = s.size() - 1; i >= 0; --i) {
            for (int j = i + 1; j <= s.size(); ++j) {
                if (dp[j] && words.find(s.substr(i, j - i)) != words.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[0];
    }
};
