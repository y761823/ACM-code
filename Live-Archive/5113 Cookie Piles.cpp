#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

int T, n, a, d;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &a, &d);
        printf("%d\n", (a + a + (n - 1) * d) * n / 2);
    }
}