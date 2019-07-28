class Solution {
public:
    inline bool isVowel(char c) {
        switch (tolower(c)) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                return true;
            default:
                return false;
        }
    }
    
    string reverseVowels(string s) {
        int l = 0, r = (int)s.size() - 1;
        while (l < r) {
            while (l < r && !isVowel(s[l])) l++;
            while (l < r && !isVowel(s[r])) r--;
            if (l < r)
                swap(s[l++], s[r--]);
        }
        return s;
    }
};
