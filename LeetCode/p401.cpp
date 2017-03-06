class Solution {
public:
    vector<string> readBinaryWatch(int num) {
        if (!num) return {"0:00"};
        vector<string> res;
        int comb = (1 << num) - 1;
        while(comb < 1 << 10) {
            int h = comb >> 6, mins = comb & 0x3f;
            if (h < 12 && mins < 60)
                res.push_back(to_string(h) + (mins < 10 ? ":0" : ":") + to_string(mins));
                
            int x = comb & -comb, y = comb + x;
            comb = ((comb & ~y) / x >> 1) | y;
        }
        return res;
    }
};
