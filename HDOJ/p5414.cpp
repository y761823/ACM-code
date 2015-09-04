#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

char a[MAXN], b[MAXN];
int T, n, m;

bool check_substring() {
    int i = 0, j = 0;
    while(i < n && j < m) {
        while(j < m && a[i] != b[j]) ++j;
        if(j < m) ++i, ++j;
    }
    return i == n;
}

bool check_pre() {
    int k = 1;
    while(k < m && b[k] == b[k - 1]) ++k;
    return k <= n && strncmp(a, b, k) == 0;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%s%s", a, b);
        n = strlen(a);
        m = strlen(b);
        puts(check_pre() && check_substring() ? "Yes" : "No");
    }
}
