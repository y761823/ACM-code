#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 1000010;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

int readint() {
    char c = getchar();
    while(!isdigit(c) && c != '-') c = getchar();
    int flag = 1;
    if(c == '-') flag = -1, c = getchar();
    int res = 0;
    while(isdigit(c)) res = res * 10 + c - '0', c = getchar();
    return res * flag;
}

int a, b, n, T;

int main() {
    LL ninf = (1LL << 63);
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d", &n, &a, &b);
        LL res = ninf, maxa = ninf, maxb = ninf;
        for(int i = 0, x; i < n; ++i) {
            x = readint();
            if(i > 0) res = max(res, (LL)a * x * x + maxb);
            if(i > 0) res = max(res, maxa + (LL)b * x);
            maxa = max(maxa, (LL)a * x * x);
            maxb = max(maxb, (LL)b * x);
        }
        printf("Case #%d: %I64d\n", t, res);
    }
}
