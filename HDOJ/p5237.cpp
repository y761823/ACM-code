#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 10010;

char str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char a[MAXN], b[MAXN];
int T, k;

void change() {
    int n = strlen(a), t = 0, c = 0;
    char *p = b;
    for(int i = 0; i < n; ++i) {
        for(int j = 7; j >= 0; --j) {
            t = (t << 1) | ((a[i] >> j) & 1);
            if(++c == 6) {
                *p++ = str[t];
                t = c = 0;
            }
        }
    }
    if(c != 0) *p++ = str[t << (6 - c)];
    if(c == 2) *p++ = '=';
    if(c == 2 || c == 4) *p++ = '=';
    *p = 0;
    strcpy(a, b);
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%s", &k, a);
        while(k--) change();
        printf("Case #%d: %s\n", t, a);
    }
}
