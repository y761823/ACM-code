class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        digits.back()++;
        for (int i = digits.size() - 1; i > 0; --i) {
            if (digits[i] < 10) break;
            digits[i - 1]++;
            digits[i] = 0;
        }
        if (digits.front() == 10) {
            digits.front() = 0;
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
};
