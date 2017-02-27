class Solution {
public:
    typedef string::iterator Iter;

    void init(string &s) {
        while (!s.empty() && s.back() == ' ') s.pop_back();
        reverse(s.begin(), s.end());
        while (!s.empty() && s.back() == ' ') s.pop_back();
        Iter p = s.begin();
        for (Iter it = s.begin(); it != s.end(); ++it)
            if (p == s.begin() || *(p - 1) != ' ' || *it != ' ') *p++ = *it;
        s.erase(p, s.end());
    }

    void reverseWords(string &s) {
        init(s);
        Iter a = s.begin();
        while (a != s.end()) {
            while (a != s.end() && *a == ' ')
                ++a;
            Iter b = a;
            while (b != s.end() && *b != ' ')
                ++b;
            reverse(a, b);
            a = b;
        }
    }
};
