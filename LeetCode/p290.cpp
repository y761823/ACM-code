class Solution {
public:
    bool wordPattern(string pattern, string str) {
        stringstream sin(str);
        map<char, string> mp;
        set<string> st;
        size_t i = 0;
        while (sin >> str) {
            if (i == pattern.size())
                return false;
            char c = pattern[i++];
            auto it = mp.find(c);
            if (it != mp.end()) {
                if (it->second != str)
                    return false;
            } else {
                if (st.find(str) != st.end())
                    return false;
                mp.insert(make_pair(c, str));
                st.insert(str);
            }
        }
        return i == pattern.size();
    }
};
