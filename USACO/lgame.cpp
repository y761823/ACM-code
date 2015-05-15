/*
ID: y7618231
PROG: lgame
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

const int MAXN = 40010;

int score[] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};
char dic[MAXN][8], s[8];
int cnt[26], n;

void solve() {
    for(int i = 0; s[i]; ++i) cnt[s[i] - 'a']++;
    vector<pair<int, int>> ans;
    int res = 0;
    for(int i = 0; i < n; ++i) {
        bool flag1 = true;
        int x = 0;
        for(int k = 0; dic[i][k]; ++k) {
            if(--cnt[dic[i][k] - 'a'] < 0) flag1 = false;
            x += score[dic[i][k] - 'a'];
        }

        if(flag1) {
            for(int j = i; j < n; ++j) {
                bool flag2 = true;
                int y = x;
                for(int k = 0; dic[j][k]; ++k) {
                    if(--cnt[dic[j][k] - 'a'] < 0) flag2 = false;
                    y += score[dic[j][k] - 'a'];
                }
                if(flag2) {
                    if(y > res) res = y, ans.clear();
                    if(y == res) ans.push_back(make_pair(i, j));
                }
                for(int k = 0; dic[j][k]; ++k)
                    ++cnt[dic[j][k] - 'a'];
            }

            if(x > res) res = x, ans.clear();
            if(x == res) ans.push_back(make_pair(i, -1));
        }

        for(int k = 0; dic[i][k]; ++k)
            ++cnt[dic[i][k] - 'a'];
    }

    printf("%d\n", res);
    for(auto p : ans) {
        if(p.second == -1) printf("%s\n", dic[p.first]);
        else printf("%s %s\n", dic[p.first], dic[p.second]);
    }
}

int main() {
#ifndef OYK_JUDGE
    freopen("lgame.in", "r", stdin); freopen("lgame.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%s", s);
    freopen("lgame.dict", "r", stdin);
    while(scanf("%s", dic[n]) != EOF && *dic[n] != '.') n++;
    solve();
}
