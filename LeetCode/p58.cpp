class Solution {
public:
    int lengthOfLastWord(string s) {
        while (!s.empty() && s.back() == ' ') s.pop_back();
        size_t pos = s.rfind(' ');
        return pos == string::npos ?
            (int)s.size() : (int)(s.size() - pos - 1);
    }
};
