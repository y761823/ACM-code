#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 110;

int a[MAXN][MAXN];
int won[MAXN];
int n, m;

int whowon(int a[]) {
    int res = 0;
    for(int i = 1; i < n; ++i)
        if(a[i] > a[res]) res = i;
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) scanf("%d", &a[i][j]);
    }
    for(int i = 0; i < m; ++i)
        won[whowon(a[i])]++;
    printf("%d\n", whowon(won) + 1);
}
