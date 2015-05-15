/*
ID: y7618231
PROG: beads
LANG: C++
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 360;

char s[MAXN];
int n;

int cal(int st, int f) {
    int ans = 1;
    if(s[st] == 'w') {
        s[st] = 'b';
        ans = max(ans, cal(st, f));
        s[st] = 'r';
        ans = max(ans, cal(st, f));
        s[st] = 'w';
    } else {
        int i = st;
        while(true) {
            i = (i + f + n) % n;
            if(s[i] != 'w' && s[i] != s[st]) break;
            if(i == st) break;
            ans++;
        }
    }
    return ans;
}

int solve() {
    int res = 0;
    for(int i = 0; i < n; ++i)
        res = max(res, cal(i, -1) + cal((i + 1) % n, 1));
    return min(res, n);
}

int main() {
#ifndef OYK_JUDGE
    freopen("beads.in", "r", stdin); freopen("beads.out", "w", stdout);
#endif
    scanf("%d%s", &n, s);
    printf("%d\n", solve());
}
