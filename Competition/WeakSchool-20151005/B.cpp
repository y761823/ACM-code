#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

const int MAXN = 65;
const int INF = 0x3f3f3f3f;

char op[MAXN];
char mat[2][MAXN][MAXN];
int n;

void solve() {
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            mat[0][i][j] = mat[1][j][i] = op[i];
    printf("%d %d %d\n", 2, n, n);
    for(int k = 0; k < 2; ++k) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j)
                putchar(mat[k][i][j]);
            puts("");
        }
        if(k < 1) puts("");
    }
}

int main() {
    char *p = op;
    for(int i = 0; i < 26; ++i) *p++ = 'a' + i;
    for(int i = 0; i < 26; ++i) *p++ = 'A' + i;
    scanf("%d", &n);
    solve();
}
