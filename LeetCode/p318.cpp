class Solution {
public:
    int maxProduct(vector<string>& words) {
        if (words.empty())
            return 0;
        int bits[words.size()];
        for (size_t i = 0; i < words.size(); ++i)
            bits[i] = getBits(words[i]);
        int res = 0;
        for (size_t i = 0; i < words.size(); ++i)
            for (int j = i + 1; j < words.size(); ++j)
                if ((bits[i] & bits[j]) == 0)
                    res = max<int>(res, words[i].size() * words[j].size());
        return res;
    }
    
    inline int getBits(const string& str) {
        int res = 0;
        for (char c : str)
            res |= (1 << (c - 'a' + 1));
        return res;
    }
};
