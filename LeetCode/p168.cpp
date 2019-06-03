// Z = A0
// AZ = B0
class Solution {
public:
    string convertToTitle(int n) {
        string res;
        while (n > 0) {
            int m = n % 26;
            if (m > 0) {
                res.push_back('A' + m - 1);
                n /= 26;
            } else {
                // borrow
                res.push_back('Z');
                n /= 26;
                n--;
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
