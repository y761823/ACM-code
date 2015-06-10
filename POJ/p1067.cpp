#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const double x = (sqrt(5) + 1) / 2;
const double y = (sqrt(5) - 1) / 2;

int a, b;

int solve() {
    if(a > b) swap(a, b);
    int t = (b - a) * x;
    return t != a;
}

int main() {
    while(scanf("%d%d", &a, &b) != EOF)
        printf("%d\n", solve());
}
