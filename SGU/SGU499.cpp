#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <functional>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MAXV = 1000010;

int exist[MAXV];
int a[MAXN];
int n;

void solve(int x) {
    int ed = sqrt(x);
    while(ed * ed <= x) ++ed;
    for(int i = 1; i < ed; ++i) {
        if(x % i == 0) {
            ++exist[i];
            if(i * i == x) break;
            ++exist[x / i];
        }
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for(int i = 0; i < n; ++i) solve(a[i]);
    for(int i = 1000000; i > 0; --i) if(exist[i] > 1) {
        printf("%d\n", i);
        break;
    }
}
