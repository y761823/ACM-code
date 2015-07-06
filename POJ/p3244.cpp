#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 200010;

int a[MAXN], b[MAXN], c[MAXN];
int n;

int main() {
    while(scanf("%d", &n) && n) {
        for(int i = 0; i < n; ++i) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            a[i] = x - y;
            b[i] = y - z;
            c[i] = z - x;
        }
        sort(a, a + n);
        sort(b, b + n);
        sort(c, c + n);
        LL ans = 0;
        for(int i = 0; i < n; ++i)
            ans += (a[i] + b[i] + c[i]) * (2 * i - n + 1LL);
        cout<<ans / 2<<endl;
    }
}
