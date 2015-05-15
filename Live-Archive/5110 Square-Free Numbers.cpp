#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

int T, n;

int calc(int n) {
    int res = 1;
    for(int i = 2; i * i <= n; ++i) {
        if(n % i == 0) {
            int cnt = 0;
            while(n % i == 0)
                n /= i, cnt++;
            res = max(res, cnt);
        }
    }
    return res;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        printf("%d\n", calc(n));
    }
}