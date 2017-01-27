class Solution {
public:
    int strStr(string haystack, string needle) {
        if (haystack.size() < needle.size()) return -1;
        for (size_t i = 0; i < haystack.size() - needle.size() + 1; ++i)
            if (strncmp(haystack.c_str() + i, needle.c_str(), needle.size()) == 0)
                return i;
        return -1;
    }
};
