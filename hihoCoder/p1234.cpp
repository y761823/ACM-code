#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 1010;
const double EPS = 1e-12;

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

double k;
int n = 501, T;

int dfs(int dep, double pos) {
    int t = sgn(pos - 0.5);
    if(t < 0) return dep * 4;
    if(t == 0) return -1;
    if(dep == n) return dep * 4;
    return dfs(dep + 1, pos * 2 - 1);
}

int solve() {
    if(k == 0) return -1;
    return dfs(1, k * 2);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%lf", &k);
        printf("%d\n", solve());
    }
}
