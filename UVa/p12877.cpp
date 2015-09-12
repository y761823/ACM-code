#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <numeric>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 26;

char str[MAXN][MAXN];
int value[MAXN], len[MAXN];
bool use[MAXN];
int n, maxlen;

void init() {
    memset(value, -1, sizeof(value));
    memset(use, 0, sizeof(use));
    memset(str, 0, sizeof(str));
    maxlen = 0;
}

int dfs(int r, int c, int add) {
    if(c == maxlen && add == 0) return 1;
    if(!str[r][c]) return r < n ? dfs(r + 1, c, add) : 0;
    int a = str[r][c] - 'A';
    int res = 0;
    if(value[a] != -1) {
        if(c + 1 == len[r] && value[a] == 0) return 0;
        if(r < n) {
            res += dfs(r + 1, c, add + value[a]);
        } else {
            if(add % 10 == value[a])
                res += dfs(1, c + 1, add / 10);
        }
    } else {
        if(r < n) {
            for(int i = (c + 1 == len[r]); i < 10; ++i) if(!use[i]) {
                use[i] = true;
                res += dfs(r + 1, c, add + (value[a] = i));
                use[i] = false;
            }
        } else {
            value[a] = add % 10;
            if(!use[value[a]]) if(!(c + 1 == len[r] && value[a] == 0)) {
                use[value[a]] = true;
                res += dfs(1, c + 1, add / 10);
                use[value[a]] = false;
            }
        }
        value[a] = -1;
    }
    return res;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        init();
        for(int i = 1; i <= n; ++i) {
            scanf("%s", str[i]);
            len[i] = strlen(str[i]);
            reverse(str[i], str[i] + len[i]);
            maxlen = max(maxlen, len[i]);
        }
        printf("%d\n", dfs(1, 0, 0));
    }
}
