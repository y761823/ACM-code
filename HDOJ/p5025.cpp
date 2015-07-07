////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-20 20:52:40
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5025
////Problem Title: 
////Run result: Accept
////Run time:562MS
////Run memory:14216KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 105;

int fx[] = {-1, 0, 1, 0};
int fy[] = {0, 1, 0, -1};

char mat[MAXN][MAXN];
int dp[MAXN][MAXN][32][10];
int n, m;

struct Node {
    int r, c, st, k, val;
    Node() {}
    Node(int r, int c, int st, int k, int val):
        r(r), c(c), st(st), k(k), val(val) {}
    bool operator < (const Node &rhs) const {
        return val > rhs.val;
    }
};

int num[MAXN][MAXN];
int pr[5], pc[5];
int sr, sc, er, ec;

void init() {
    int cnt = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(mat[i][j] == 'K') sr = i, sc = j;
            if(mat[i][j] == 'T') er = i, ec = j;
            if(mat[i][j] == 'S') {
                pr[cnt] = i, pc[cnt] = j;
                num[i][j] = cnt++;
            }
        }
    }
}

int solve() {
    init();
    memset(dp, 0x3f, sizeof(dp));
    dp[sr][sc][0][0] = 0;
    priority_queue<Node> que;
    que.push(Node(sr, sc, 0, 0, 0));
    while(!que.empty()) {
        Node u = que.top(); que.pop();
        if(dp[u.r][u.c][u.st][u.k] != u.val) continue;
        for(int f = 0; f < 4; ++f) {
            int r = u.r + fx[f], c = u.c + fy[f], st = u.st, k = u.k, d = u.val + 1;
            if(mat[r][c] == 0 || mat[r][c] == '#') continue;
            if(mat[r][c] == 'S' && (st & (1 << num[r][c])) == 0) {
                st |= (1 << num[r][c]);
                d++;
            }
            if(isdigit(mat[r][c]) && mat[r][c] - '0' == k + 1) {
                k++;
            }
            if(r == er && c == ec && k == m) {
                return d;
            }
            if(d < dp[r][c][st][k]) {
                dp[r][c][st][k] = d;
                que.push(Node(r, c, st, k, d));
            }
        }
    }
    return -1;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        memset(mat, 0, sizeof(mat));
        for(int i = 1; i <= n; ++i) scanf("%s", &mat[i][1]);
        int ans = solve();
        if(ans == -1) puts("impossible");
        else printf("%d\n", ans);
    }
}