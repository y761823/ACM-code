#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
using namespace std;
#define forall(i, v) for(__typeof(v.begin()) i = v.begin(); i != v.end(); ++i)
typedef long long LL;

const int MAXN = 250010;

bool flag[MAXN];
int p_cnt[MAXN];
int h;

void init(int n = 250001) {
    for(int i = 1; i <= n; ++i) {
        if(flag[i]) continue;
        int ii = 4 * i + 1;
        for(int j = ii + 4 * ii; j <= (n << 2); j += 4 * ii) {
            flag[j >> 2] = true;
            if(((j / ii) & 3) == 1 && j / ii <= ii && !flag[(j / ii) >> 2])
                p_cnt[j >> 2] = 1;
        }
    }
    partial_sum(p_cnt, p_cnt + n + 1, p_cnt);
}

int main() {
    init();
    while(scanf("%d", &h) && h)
        printf("%d %d\n", h, p_cnt[(h >> 2) - ((h & 3) == 0)]);
}
