#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <numeric>
using namespace std;
#define forall(i, v) for(__typeof(v.begin()) i = v.begin(); i != v.end(); ++i)

const int MAXT = 1010;
const int MAXM = 33;

double gt0[MAXT], stn[MAXT];
double p[MAXT][MAXM];
int n, m, t;

double dp[MAXM][MAXM];
void get(int x) {
    dp[0][0] = 1;
    for(int i = 1; i <= m; ++i) {
        for(int j = 0; j <= i; ++j) {
            dp[i][j] = 0;
            if(j > 0) dp[i][j] += p[x][i] * dp[i - 1][j - 1];
            if(j < i) dp[i][j] += (1 - p[x][i]) * dp[i - 1][j];
        }
    }
    gt0[x] = 1 - dp[m][0];
    stn[x] = accumulate(dp[m] + 1, dp[m] + n, 0.0);
}

int main() {
    while(scanf("%d%d%d", &m, &t, &n) != EOF) {
        if(m == 0 && t == 0 && n == 0) break;
        for(int i = 0; i < t; ++i) {
            for(int j = 1; j <= m; ++j) scanf("%lf", &p[i][j]);
            get(i);
        }
        double r1 = 1, r2 = 1;
        for(int i = 0; i < t; ++i) {
            r1 *= gt0[i];
            r2 *= stn[i];
        }
        printf("%.3f\n", r1 - r2);
    }
}
