/*
ID: y7618231
PROG: shuttle
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 28;

vector<int> ans;
int val[MAXN], goal[MAXN];
int n, m;

bool move(int i, int f) {
    if(!(1 <= i + f && i + f <= m)) return false;
    if(val[i] == val[i + f]) return false;
    if(val[i + f] == 0) swap(val[i], val[i + f]);
    else swap(val[i], val[i + f + f]);
    return true;
}

bool isgoal() {
    for(int i = 1; i <= m; ++i)
        if(val[i] != goal[i]) return false;
    return true;
}

void solve() {
    m = 2 * n + 1;
    for(int i = 1; i <= n; ++i) {
        goal[n + 1 + i] = val[i] = 1;
        goal[i] = val[n + 1 + i] = 2;
    }

    for(int k = 1; ; ++k) {
        if(k & 1) {
            int cnt = 0;
            for(int i = m; i > 0; --i) if(val[i] == 1) {
                if(move(i, 1)) ans.push_back(i);
                if(++cnt == k) break;
            }
        } else {
            int cnt = 0;
            for(int i = 1; i <= m; ++i) if(val[i] == 2) {
                if(move(i, -1)) ans.push_back(i);
                if(++cnt == k) break;
            }
        }
        if(isgoal()) break;
    }

    int cnt = 0;
    for(int x : ans) {
        if(cnt) putchar(cnt % 20 == 0 ? '\n' : ' ');
        printf("%d", x);
        cnt++;
    }
    puts("");
}

int main() {
#ifndef OYK_JUDGE
    freopen("shuttle.in", "r", stdin); freopen("shuttle.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &n);
    solve();
}
