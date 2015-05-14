#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;

int n, m, a, b, c, T;

LL solve1() {
    LL res = max(a, b) * LL(n - m - 1);
    res += LL(m) / 2 * max(a + c, b + b);
    if(m & 1) res += max(b, c);
    return res;
}

LL solve2() {
    LL res = min(b, c) * LL(m - 1);
    res += LL(n - m) / 2 * min(a + c, b + b);
    if((n - m) & 1) res += min(a, b);
    return res;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d%d%d", &n, &m, &a, &b, &c);
        if(a < c) swap(a, c);
        printf("Case #%d: " longformat " " longformat "\n", t, solve1(), solve2());
    }
}
