class Solution {
public:
    int get(int n) {
        int res = 0;
        while (n) {
            int t = n % 10;
            n /= 10;
            res += t * t;
        }
        return res;
    }

    bool isHappy(int n) {
        bool exist[200] = {0};
        n = get(get(n));
        while (!exist[n]) {
            exist[n] = true;
            n = get(n);
        }
        return n == 1;
    }
};
