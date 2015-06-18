#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
#define forall(i, v) for(__typeof(v.begin()) i = v.begin(); i != v.end(); ++i)
typedef long long LL;

const int MAXN = 5010;

char s[MAXN];
short dp[MAXN][MAXN];
int n;

int main() {
    scanf("%d%s", &n, s);
    for(int len = 2; len <= n; ++len) {
        for(int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            if(s[i] == s[j]) dp[i][j] = dp[i + 1][j - 1];
            else dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
        }
    }
    printf("%d\n", dp[0][n - 1]);
}
