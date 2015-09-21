#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 510;
const int INF = 0x3f3f3f3f;

const int cost[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int dp[MAXN][2][4];
int T, n, mod;

void update_add(int &a, int b) {
    LL x = (LL)a + b;
    if(x >= mod) x -= mod;
    a = x;
}

int solve() {
    memset(dp, 0, (n + 1) * sizeof(dp[0]));
    dp[0][0][0] = 1;
    FOR(x, 0, n) FOR(y, 0, 1) FOR(z, 0, 3) if(dp[x][y][z]) {
        if(z == 3) {
            if(y == 1) update_add(dp[x + cost[1]][0][z], dp[x][y][z]);
            continue;
        }
        FOR(be, 0, 1) if((z & 1) <= be) FOR(b, be, 9) {
            if((z & 1) && b > 1) continue;
            FOR(ce, 0, 1) if((z >> 1) <= ce) FOR(c, ce, 9)  {
                if((z >> 1) && c > 1) continue;

                int newcost = x, newa = y;
                if(!(z & 1)) newcost += cost[b], newa += b;
                if(!(z & 2)) newcost += cost[c], newa += c;
                newcost += cost[newa % 10];
                if(newcost <= n) update_add(dp[newcost][newa / 10][be | (ce << 1)], dp[x][y][z]);
            }
        }
    }
    return dp[n][0][3];
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &mod);
        n -= 3;
        printf("Case #%d: %d\n", t, solve());
    }
}
