////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-09-08 18:28:58
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4714
////Problem Title: 
////Run result: Accept
////Run time:2546MS
////Run memory:37828KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2000010;
const int MAXE = MAXN * 2;

int head[MAXN];
int stk[MAXN], stkp[MAXN], top;
int next[MAXE], to[MAXE];
int ecnt, n, T;

void init() {
    memset(head, 0, sizeof(head));
    ecnt = 1;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

int dp[MAXN][2];
//0:连0 or 1个子节点，1:连两个子节点
int solve() {
    top = 1;
    stk[top] = 1; stkp[top] = head[1];
    while(top > 0) {
        int &p = stkp[top], u = stk[top];
        if(to[p] == stk[top - 1]) p = next[p];
        if(p) {
            int &v = to[p];
            ++top; stk[top] = v; stkp[top] = head[v];
            p = next[p];
        }
        else {
            int min1 = MAXN, min2 = MAXN;
            dp[u][0] = 0;
            for(int q = head[u]; q; q = next[q]) {
                int &v = to[q];
                if(v == stk[top - 1]) continue;
                ++dp[u][0];
                dp[u][0] += min(dp[v][0], dp[v][1]);
                int x = dp[v][0] - min(dp[v][0], dp[v][1]);
                if(x < min1) {
                    min2 = min1;
                    min1 = x;
                }
                else min2 = min(min2, x);
            }
            int best = dp[u][0];
            dp[u][0] = min(dp[u][0], best - 1 + min1);
            dp[u][1] = min(dp[u][0], best - 2 + min1 + min2);
            --top;
        }
    }
    return 2 * min(dp[1][0], dp[1][1]) + 1;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        init();
        int u, v;
        for(int i = 1; i < n; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        printf("%d\n", solve());
    }
}
