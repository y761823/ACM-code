#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 200010;
const int MAXT = MAXN << 1;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

vector<int> hashtable;

int gethash(int x) {
    return lower_bound(hashtable.begin(), hashtable.end(), x) - hashtable.begin() + 1;
}

int atree[MAXT], btree[MAXT];
int n, m;

int lowbit(int x) {
    return x & -x;
}

void modify(int tree[], int x, int val) {
    while(x <= n) {
        tree[x] += val;
        x += lowbit(x);
    }
}

int get_sum(int tree[], int x) {
    int res = 0;
    while(x) {
        res += tree[x];
        x -= lowbit(x);
    }
    return res;
}

int a[MAXN], b[MAXN], id[MAXN], len[MAXN];

int main() {
    int kase = 0;
    while(scanf("%d", &m) != EOF) {
        hashtable.clear();
        for(int i = 0, l = 1; i < m; ++i) {
            scanf("%d%d", &a[i], &b[i]);
            if(a[i] == 0) {
                hashtable.push_back(b[i]);
                hashtable.push_back(b[i] + l - 1);
                len[i] = l;
                id[l++] = i;
            }
        }
        sort(hashtable.begin(), hashtable.end());
        hashtable.erase(unique(hashtable.begin(), hashtable.end()), hashtable.end());
        n = hashtable.size();
        memset(atree + 1, 0, n * sizeof(int));
        memset(btree + 1, 0, n * sizeof(int));
        printf("Case #%d:\n", ++kase);
        for(int i = 0, l = 1; i < m; ++i) {
            if(a[i] == 0) {
                int u = gethash(b[i]), v = gethash(b[i] + l++ - 1);
                printf("%d\n", get_sum(btree, v) - get_sum(atree, u - 1));
                modify(atree, u, 1); modify(btree, v, 1);
            } else {
                int u = gethash(b[id[b[i]]]), v = gethash(b[id[b[i]]] + len[id[b[i]]] - 1);
                modify(atree, u, -1); modify(btree, v, -1);
            }
        }
    }
}
