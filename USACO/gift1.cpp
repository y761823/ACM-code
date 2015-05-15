/*
ID: y7618231
PROG: gift1
LANG: C++
*/
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 10;
const int MAXL = 15;

char name[MAXN][MAXL];
int ans[MAXN];
int n;

void modify(char s[], int val) {
    for(int i = 0; i < n; ++i)
        if(strcmp(s, name[i]) == 0) ans[i] += val;
}

int main() {
    freopen("gift1.in", "r", stdin); freopen("gift1.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%s", name[i]);
    for(int i = 0, sum, cnt; i < n; ++i) {
        static char s[MAXL];
        scanf("%s", s);
        scanf("%d%d", &sum, &cnt);
        if(cnt) sum /= cnt, modify(s, -sum * cnt);
        for(int j = 0; j < cnt; ++j) {
            static char to[MAXL];
            scanf("%s", to);
            modify(to, sum);
        }
    }
    for(int i = 0; i < n; ++i)
        printf("%s %d\n", name[i], ans[i]);
}
