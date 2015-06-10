#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1000010;

void getFail(char *P, int m, int f[]) {
    f[0] = f[1] = 0;
    for(int i = 1; i < m; ++i) {
        int j = f[i];
        while(j && P[i] != P[j]) j = f[j];
        f[i + 1] = (P[i] == P[j] ? j + 1 : 0);
    }
}

char s[MAXN];
int fail[MAXN], n;

int main() {
    while(scanf("%s", s) != EOF) {
        if(*s == '.') break;
        n = strlen(s);
        getFail(s, n, fail);
        if(n % (n - fail[n]) == 0) printf("%d\n", n / (n - fail[n]));
        else puts("1");
    }
}
