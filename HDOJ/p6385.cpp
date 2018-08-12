#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 1000010;

int mx, my, T, n;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &mx, &my, &n);
        LL res = 0;
        for (int i = 0, x, y; i < n; ++i) {
            scanf("%d%d", &x, &y);
            res += min(min(mx - x, x), min(my - y, y));
        }
        cout << res << endl;
    }
}
