#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAXR = 2e6;

LL A, B, C;

LL next(LL x) {
    return (A * x + x % B) % C;
}

int main() {
    scanf("%I64d%I64d%I64d", &A, &B, &C);
    LL x = next(1), y = next(x);
    int v = 1;
    while(v <= MAXR && x != y)
        x = next(x), y = next(next(y)), v++;
    if(v > MAXR) {
        puts("-1");
        return 0;
    }

    x = 1;
    int mu = 0;
    while(x != y)
        x = next(x), y = next(y), mu++;

    int lam = 1;
    y = next(x);
    while(mu + lam <= MAXR && x != y) y = next(y), lam++;

    if(mu + lam <= MAXR) printf("%d\n", mu + lam);
    else puts("-1");
}
