#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

const int MAXV = 1010;

int sg[MAXV], outdeg[MAXV], tmp[MAXV];
int mat[MAXV][MAXV];
int ecnt, n, m;

void init() {
    memset(mat, 0, sizeof(mat));
    memset(outdeg, 0, sizeof(outdeg));
}

void add_edge(int u, int v) {
    mat[u][v] = 1; ++outdeg[u];
}

void build_sg() {
    stack<int> stk;
    for(int i = 0; i < n; ++i)
        if(outdeg[i] == 0) stk.push(i);
    while(!stk.empty()) {
        int u = stk.top(); stk.pop();
        memset(tmp, 0, sizeof(tmp));
        for(int v = 0; v < n; ++v)
            if(mat[u][v]) tmp[sg[v]] = true;
        for(int i = 0; i < n; ++i)
            if(!tmp[i]) {sg[u] = i; break;}
        for(int v = 0; v < n; ++v)
            if(mat[v][u] && --outdeg[v] == 0) stk.push(v);
    }
}

int main() {
    while(scanf("%d", &n) != EOF && n) {
        init();
        for(int i = 0; i < n; ++i) {
            int x, j;
            scanf("%d", &x);
            while(x--) scanf("%d", &j), add_edge(i, j);
        }
        build_sg();
        while(scanf("%d", &m) && m) {
            int ans = 0, x;
            while(m--) {
                scanf("%d", &x);
                ans ^= sg[x];
            }
            puts(ans ? "WIN" : "LOSE");
        }
    }
}
