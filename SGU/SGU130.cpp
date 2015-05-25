#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

LL f[33];

int n;
int main() {
    f[0] = f[1] = 1;
    scanf("%d", &n);
    for(int i = 2; i <= n; ++i)
        for(int j = 0; j < i; ++j) f[i] += f[j] * f[i - 1 - j];
    printf("%I64d %d\n", f[n], n + 1);
    //for(int i = 1; i <= n; ++i) printf("%d : %I64d\n", i, f[i]);
}
