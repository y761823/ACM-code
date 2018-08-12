#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAXV = 200010;

int degree[MAXV];
int n, m, k, T;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        memset(degree, 0, n * sizeof(int));
        for (int i = 0, a, b; i < m; ++i) {
            scanf("%d%d", &a, &b);
            degree[a]++;
            degree[b]++;
        }
        int maxdegree = *max_element(degree, degree + n);
        printf("%d\n", min(maxdegree + (n - m - 1) + k, n - 1));
    }
}
