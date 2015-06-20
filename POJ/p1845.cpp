#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
using namespace std;
#define forall(i, v) for(__typeof(v.begin()) i = v.begin(); i != v.end(); ++i)
typedef long long LL;

const int MAXN = 33;
const int MOD = 9901;

int x[MAXN], p[MAXN], total;
int a, b;

void getDivisors(int n) {
    for(int i = 2; i * i <= n; ++i) {
        if(n % i == 0) {
            while(n % i == 0) p[total]++, n /= i;
            x[total++] = i;
        }
    }
    if(n > 1) {
        p[total] = 1;
        x[total++] = n;
    }
}

int power(int x, int p) {
    int res = 1;
    while(p) {
        if(p & 1) res = res * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return res;
}
int powerSum(int x, int p) {
    if(p == 0) return 0;
    if(p & 1) return (x * powerSum(x, p - 1) + 1) % MOD;
    else return (power(x, p >> 1) + 1) * powerSum(x, p >> 1) % MOD;
}

int getAnswer() {
    if(a == 0) return 0;
    if(b == 0) return 1;
    getDivisors(a);
    int res = 1;
    for(int i = 0; i < total; ++i) {
        res = res * powerSum(x[i] % MOD, p[i] * b + 1) % MOD;
    }
    return res;
}

int main() {
    scanf("%d%d", &a, &b);
    printf("%d\n", getAnswer());
}
