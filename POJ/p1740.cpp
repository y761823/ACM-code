#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long LL;

int n;
int a[15];

bool solve() {
    if(n & 1) return true;
    sort(a, a + n);
    int last = 0;
    while(a[last] == 0 && last < n) ++last;
    a[n] = -1;
    for(int i = last + 1; i <= n; ++i) {
        if(a[i] != a[last]) {
            if((i - last) & 1) return true;
            last = i;
        }
    }
    return false;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        if(n == 0) break;
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        printf("%d\n", solve());
    }
}
