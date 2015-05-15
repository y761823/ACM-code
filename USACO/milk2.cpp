/*
ID: y7618231
PROG: milk2
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
#include <algorithm>
using namespace std;

const int MAXN = 5010;

pair<int, int> op[MAXN << 1];
int n, cnt;

void solve() {
    int ans1 = 0, ans2 = 0, len1 = 0, len2 = 0;
    int i = 0, t = op[0].first, people = 0;
    while(true) {
        while(i < cnt && t == op[i].first) people += op[i++].second;
        if(i == cnt) break;
        len1 += op[i].first - t;
        len2 += op[i].first - t;
        t = op[i].first;
        if(people == 0) len1 = 0;
        else len2 = 0;
        ans1 = max(ans1, len1);
        ans2 = max(ans2, len2);
    }
    printf("%d %d\n", ans1, ans2);
}

int main() {
#ifndef OYK_JUDGE
    freopen("milk2.in", "r", stdin); freopen("milk2.out", "w", stdout);
#endif
    scanf("%d", &n);
    for(int i = 0, a, b; i < n; ++i) {
        scanf("%d%d", &a, &b);
        op[cnt++] = make_pair(a, 1);
        op[cnt++] = make_pair(b, -1);
    }
    sort(op, op + cnt);
    solve();
}
