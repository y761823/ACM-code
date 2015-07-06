#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;

const int MAXN = 10010;

char s[MAXN];
int src[MAXN], n;

void init() {
    int i;
    for(i = 0; s[i]; ++i)
        src[i] = isdigit(s[i]) * (s[i] - '0');
    n = i;
}

int best[MAXN];
int ans[MAXN][10];
int pos[10];
int stk[MAXN], top;

void next(int *arr, int n) {
    for(int i = 0; i < n; ++i)
        if(++arr[i] >= n) arr[i] = 0;
}

void solve(int n) {
    if(src[n] == 0) {
        best[n] = 1;
        stk[top++] = n;
        return ;
    }
    int &len = src[n];
    for(int i = 0; i < len; ++i) pos[i] = i;
    for(int i = 0; i < len; ++i) {
        int tmp = len;
        for(int j = 0; j < len; ++j)
            tmp = max(tmp, j + best[stk[top - len + pos[j]]]);
        if(best[n] == 0 || tmp < best[n]) {
            best[n] = tmp;
            for(int j = 0; j < len; ++j) ans[n][j] = stk[top - len + pos[j]];
        }
        next(pos, len);
    }
    top -= len;
    stk[top++] = n;
}

void dfs(int n) {
    for(int i = 0; i < src[n]; ++i)
        if(src[ans[n][i]]) dfs(ans[n][i]);
        else putchar('a');
    printf("%d", src[n]);
}

int main() {
    scanf("%s", s);
    init();
    for(int i = 0; i < n; ++i) solve(i);
    printf("%d\n", best[n - 1]);
    dfs(n - 1);
    puts("");
}
