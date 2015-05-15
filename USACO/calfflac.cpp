/*
ID: y7618231
PROG: calfflac
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <vector>
using namespace std;

typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 40010;
const int INF = 0x3f3f3f3f;

char src[MAXN], s[MAXN];
int spos[MAXN], p[MAXN];
int n, cnt;

void manacher() {
    int mx = 0, id;
    for(int i = 1; i < cnt; ++i) {
        if(mx > i) p[i] = min(p[2 * id - 1], mx - i);
        else p[i] = 1;
        while(s[i + p[i]] == s[i - p[i]]) ++p[i];
        if(i + p[i] > mx) {
            id = i;
            mx = i + p[i];
        }
    }
}

void print() {
    int id = 0;
    for(int i = 1; i < cnt; ++i)
        if(p[i] > p[id]) id = i;
    printf("%d\n", p[id] - 1);
    int l = (id - p[id] + 1) / 2, r = l + p[id] - 2;
    l = spos[l], r = spos[r];
    for(int i = l; i <= r; ++i) putchar(src[i]);
    puts("");
}

int main() {
#ifndef OYK_JUDGE
    freopen("calfflac.in", "r", stdin); freopen("calfflac.out", "w", stdout);
#endif // OYK_JUDGE
    char c;
    s[cnt++] = '!'; s[cnt++] = '#';
    int v = 0;
    while((c = getchar()) != EOF) {
        if(isalpha(c)) spos[v++] = n, s[cnt++] = tolower(c), s[cnt++] = '#';
        src[n++] = c;
    }
    s[cnt] = 0;
    manacher();
    print();
}
