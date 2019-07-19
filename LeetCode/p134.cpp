class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        for (int st = 0; st < n; ) {
            int i = 0, sum = 0;
            for (; i < n; ++i) {
                int idx = (st + i) % n;
                sum += gas[idx] - cost[idx];
                if (sum < 0)
                    break;
            }
            if (i == n)
                return st;
            st = st + i + 1;
        }
        return -1;
    }
};
