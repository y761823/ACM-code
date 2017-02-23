class Solution {
public:
    bool isPalindrome(string s) {
        const char *l = s.c_str(), *r = l + s.length() - 1;
        while (l < r) {
            while (l < r && !isalnum(*l)) l++;
            while (l < r && !isalnum(*r)) r--;
            if (tolower(*l) != tolower(*r))
                return false;
            l++, r--;
        }
        return true;
    }
};
