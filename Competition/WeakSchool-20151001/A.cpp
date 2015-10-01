#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

const int MAXN = 100010;
const double EPS = 1e-8;

int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

int n;

int main() {
    while(scanf("%d", &n) != EOF) {
        double sum = 0;
        for(int i = 0, a; i < n; ++i) {
            scanf("%d", &a);
            sum += sqrt(a);
        }
        puts(sgn(sum - round(sum)) == 0 ? "Yes" : "No");
    }
}
