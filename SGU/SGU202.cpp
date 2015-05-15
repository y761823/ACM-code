#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAXV = 69;
const int INF = 0x1f3f3f3f;

int dp[MAXV][MAXV];
int opera[MAXV][MAXV];

int solve(int n, int m) {
    if(m == 1) return INF;
    if(n == 1) return 1;
    int &res = dp[n][m];
    if(res == 0) {
        res = INF;
        for(int i = 1; i < n; ++i) {
            int tmp = 2 * solve(i, m) + solve(n - i, m - 1);
            if(tmp < res) {
                opera[n][m] = i;
                res = tmp;
            }
        }
    }
    return res;
}

stack<int> peg[MAXV];
bool vis[MAXV];
int n, m;

void move(int src, int tar) {
    if(peg[tar].empty())
        printf("move %d from %d to %d\n", peg[src].top(), src, tar);
    else
        printf("move %d from %d to %d atop %d\n", peg[src].top(), src, tar, peg[tar].top());
    peg[tar].push(peg[src].top()); peg[src].pop();
}

void print_path(int n, int m, int src, int tar) {
    if(n == 1) move(src, tar);
    else {
        int x = opera[n][m], v = 1;
        while(vis[v] || v == src || v == tar) ++v;
        print_path(x, m, src, v);
        vis[v] = true;
        print_path(n - x, m - 1, src, tar);
        vis[v] = false;
        print_path(x, m, v, tar);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    printf("%d\n", solve(n, m));

    for(int i = n; i >= 1; --i) peg[1].push(i);
    print_path(n, m, 1, m);
}
