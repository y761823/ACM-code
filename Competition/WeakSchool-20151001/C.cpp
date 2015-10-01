#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 5000010;

void getFail(char P[], int m, int f[]) {
    f[0] = f[1] = 0;
    for(int i = 1; i < m; ++i) {
        int j = f[i];
        while(j && P[i] != P[j]) j = f[j];
        f[i + 1] = (P[i] == P[j] ? j + 1 : 0);
    }
}

char w[MAXN], p[MAXN];
int m, n;

int pos[MAXN], fail[MAXN];
int l;

void push_back(char c) {
    pos[l] = (l == 0 ? 0 : pos[l - 1]);
    int &i = pos[l];

    while(i && w[i] != c) i = fail[i];
    if(w[i] == c) i++;

    if(i == m) l -= m - 1;
    else p[l++] = c;
}

void solve() {
    getFail(w, m, fail);
    l = 0;
    for(int i = 0; i < n; ++i)
        push_back(p[i]);
    p[l] = 0;
    puts(p);
}

int main() {
    while(scanf("%s%s", w, p) != EOF) {
        m = strlen(w);
        n = strlen(p);
        solve();
    }
}
