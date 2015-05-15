#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 66666;

struct Node {
    int val, id;
    bool operator < (const Node &rhs) const {
        if(val != rhs.val) return val > rhs.val;
        return id > rhs.id;
    }
};

Node a[MAXN];
int tree[MAXN], n;

int lowbit(int x) {
    return x & -x;
}

void modify(int k, int val) {
    while(k <= n) {
        tree[k] += val;
        k += lowbit(k);
    }
}

int get_sum(int k) {
    int res = 0;
    while(k) {
        res += tree[k];
        k -= lowbit(k);
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &a[i].val), a[i].id = i;
    sort(a + 1, a + n + 1);
    LL res = 0;
    for(int i = 1; i <= n; ++i) {
        res += get_sum(a[i].id);
        modify(a[i].id, 1);
    }
    cout<<res<<endl;
}
