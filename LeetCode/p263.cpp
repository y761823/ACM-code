class Solution {
public:
    bool isUgly(int num) {
        if (num <= 0)
            return false;
        for (int x : {2, 3, 5})
            while (num % x == 0) num /= x;
        return num == 1;
    }
};
