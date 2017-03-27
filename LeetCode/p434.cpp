class Solution {
public:
    int countSegments(string s) {
        bool last = false;
        int res = 0;
        for (char c : s) {
            if (!last && c != ' ')
                res++;
            last = (c != ' ');
        }
        return res;
    }
};
