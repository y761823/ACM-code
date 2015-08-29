#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 100010;

int a[MAXN], b[MAXN];
int m, k, na, nb;

bool solve() {
    return a[k - 1] < b[nb - m];
}

int main() {
    scanf("%d%d", &na, &nb);
    scanf("%d%d", &k, &m);
    for(int i = 0; i < na; ++i) scanf("%d", &a[i]);
    for(int i = 0; i < nb; ++i) scanf("%d", &b[i]);
    puts(solve() ? "YES" : "NO");
}
