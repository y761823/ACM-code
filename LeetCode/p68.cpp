class Solution {
public:
    typedef vector<string>::iterator Iter;

    static string buildLine(Iter st, Iter ed, int maxWidth) {
        if (ed - st == 1) {
            return *st + string(maxWidth - st->length(), ' ');
        }
        
        int sum = 0, cnt = ed - st;
        for (auto it = st; it != ed; ++it)
            sum += it->length();
        int a = (maxWidth - sum) / (cnt - 1), b = (maxWidth - sum) % (cnt - 1);
        string res;
        for (int i = 0; i < cnt; ++i) {
            res += *(st + i);
            if (i + 1 != cnt)
                res += string(a + (i < b), ' ');
        }
        return res;
    }
    
    static string buildLastLine(Iter st, Iter ed, int maxWidth) {
        string res;
        for (auto it = st; it != ed; ++it) {
            if (it != st) res += ' ';
            res += *it;
        }
        res += string(maxWidth - res.length(), ' ');
        return res;
    }

    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        Iter it = words.begin();
        while (it != words.end()) {
            int sum = it->length();
            Iter ed = it + 1;
            while (ed != words.end() && sum + 1 + ed->length() <= maxWidth)
                sum += 1 + (ed++)->length();
            res.push_back((ed != words.end() ? buildLine : buildLastLine)(it, ed, maxWidth));
            it = ed;
        }
        return res;
    }
};
