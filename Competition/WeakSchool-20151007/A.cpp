#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

int a[3];
int T, n = 3;

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        for(int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        printf("Case #%d:\n", t);
        sort(a, a + n);
        do {
            printf("%d %d %d\n", a[0], a[1], a[2]);
        } while(next_permutation(a, a + n));
    }
}
