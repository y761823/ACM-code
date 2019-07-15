class Solution {
public:
    string getHint(string secret, string guess) {
        int A = 0;
        int cnt[10] = {};
        for (size_t i = 0; i < secret.size(); ++i) {
            char a = secret[i], b = guess[i];
            if (a != b)
                cnt[a - '0']++, cnt[b - '0']--;
            else
                A++;
        }
        int B = secret.size() - A;
        for (int c : cnt)
            if (c > 0) B -= c;
        char str[256];
        snprintf(str, 256, "%dA%dB", A, B);
        return str;
    }
};
