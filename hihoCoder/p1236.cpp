#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <bitset>
using namespace std;
typedef long long LL;

const int MAXN = 50010;
const int N = 50000;
const int SQRT = 256;

struct Node {
    int val, id;
    Node(int val = 0): val(val), id(0) {}
    bool operator < (const Node &rhs) const {
        return val < rhs.val;
    }
} a[5][MAXN];
bitset<N> bits[5][MAXN / SQRT + 5];

int query[5];
int T, n, m, q;

void init() {
    for(int i = 0; i < 5; ++i)
        sort(a[i], a[i] + n);
    m = (n + SQRT - 1) / SQRT;
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < m; ++j) {
            if(j == 0) bits[i][j].reset();
            else bits[i][j] = bits[i][j - 1];
            for(int k = 0, offset = j * SQRT; k < SQRT; ++k) {
                if(k + offset >= n) break;
                bits[i][j].set(a[i][k + offset].id);
            }
        }
    }
}

int solve() {
    static bitset<N> res, tmp;
    res.set();
    for(int i = 0; i < 5; ++i) {
        int pos = upper_bound(a[i], a[i] + n, Node(query[i])) - a[i];
        if(pos == 0) return 0;
        int b = (pos - 1) / SQRT;
        if(b > 0) tmp = bits[i][b - 1];
        else tmp.reset();
        for(int j = b * SQRT; j < pos; ++j)
            tmp.set(a[i][j].id);
        res &= tmp;
    }
    return res.count();
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < 5; ++j) {
                scanf("%d", &a[j][i].val);
                a[j][i].id = i;
            }
        }
        init();
        scanf("%d", &q);
        for(int i = 0, last = 0; i < q; ++i) {
            for(int i = 0; i < 5; ++i) {
                scanf("%d", &query[i]);
                query[i] ^= last;
            }
            printf("%d\n", last = solve());
        }
    }
}
