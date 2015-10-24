#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

int n, L, T;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &L, &n);
        int mint = 0, maxt = 0;
        for(int i = 0, pos; i < n; ++i) {
            scanf("%d", &pos);
            mint = max(mint, min(pos, L - pos));
            maxt = max(maxt, max(pos, L - pos));
        }
        printf("%d %d\n", mint, maxt);
    }
}
