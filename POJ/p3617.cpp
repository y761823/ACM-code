#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 2005;

char s[MAXN], res[MAXN];
int n;

bool check(int l, int r) {
    while(l < r && s[l] == s[r]) ++l, --r;
    return l < r && s[l] < s[r];
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        scanf(" %c", &s[i]);
    for(int l = 0, r = n - 1, c = 0; c < n; ++c) {
        if(check(l, r)) res[c] = s[l++];
        else res[c] = s[r--];
    }
    for(int i = 0; i < n; ++i) {
        if(i && i % 80 == 0) puts("");
        putchar(res[i]);
    }
    puts("");
}
