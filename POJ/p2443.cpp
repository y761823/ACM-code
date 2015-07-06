#include <cstdio>
#include <bitset>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1010;
const int MAXM = 10010;

int n;
bitset<MAXN> have[MAXM];

int main() {
    scanf("%d", &n);
    int sum, x, y;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &sum);
        while(sum--) {
            scanf("%d", &x);
            have[x].set(i);
        }
    }
    scanf("%d", &sum);
    while(sum--) {
        scanf("%d%d", &x, &y);
        if((have[x] & have[y]).any()) puts("Yes");
        else puts("No");
    }
}
