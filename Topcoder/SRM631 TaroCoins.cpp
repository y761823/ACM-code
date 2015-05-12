#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
typedef long long LL;

LL dp[64][2];
int pre[64];

class TaroCoins {
public:
    long long getNumber(long long n) {
        n = n * 2 + 1;
        int last = 0;
        for(int i = 1; i < 63; ++i) {
            if((n >> i) & 1) {
                pre[i] = last;
                last = i;
            }
        }
        dp[0][0] = 1; dp[0][1] = 0;
        for(int i = 1; i <= last; ++i) {
            if((n >> i) & 1) {
                dp[i][0] = dp[pre[i]][0] + dp[pre[i]][1];
                dp[i][1] = (i - pre[i] - 1) * dp[i][0] + dp[pre[i]][1];
            }
        }
        return dp[last][0] + dp[last][1];
    }
};
