#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <numeric>
using namespace std;

const int MAXN = 210;

int sum[MAXN];
int n, T;

void format(int a, int b) {
    if(a > b) swap(a, b);
    a = (a - 1) / 2;
    b = (b - 1) / 2;
    sum[a]++, sum[b + 1]--;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        memset(sum, 0, sizeof(sum));
        for(int i = 0, a, b; i < n; ++i) {
            scanf("%d%d", &a, &b);
            format(a, b);
        }
        partial_sum(sum, sum + 200, sum);
        printf("%d\n", *max_element(sum, sum + 200) * 10);
    }
}
