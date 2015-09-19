#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 1000010;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

char str[MAXN];
int cpos[MAXN], cnt;
int T, n;

int solve() {
    cnt = 0;
    for(int i = 0; i < n; ++i) {
        if(str[i] == 'c') cpos[cnt++] = i;
        else if(str[i] != 'f') return -1;
    }
    if(cnt == 0) return (n + 1) / 2;
    for(int i = 0; i + 1 < cnt; ++i)
        if(cpos[i + 1] - cpos[i] - 1 < 2) return -1;
    if(n - cpos[cnt - 1] + cpos[0] - 1 < 2) return -1;
    return cnt;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%s", str);
        n = strlen(str);
        printf("Case #%d: %d\n", t, solve());
    }
}
