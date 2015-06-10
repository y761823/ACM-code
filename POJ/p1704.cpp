#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1010;

int p[MAXN], n, T;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d", &p[i]);
        sort(p + 1, p + n + 1);
        int ans = 0;
        for(int i = 2 - (n & 1); i <= n; i += 2) ans ^= p[i] - p[i - 1] - 1;
        puts(ans ? "Georgia will win" : "Bob will win");
    }
}
