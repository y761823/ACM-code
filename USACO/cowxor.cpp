/*
ID: y7618231
PROG: cowxor
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <cstdio>
#include <algorithm>

typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 700010;
const int INF = 0x3f3f3f3f;

struct Node {
    Node *go[2];
    int flag, id;
    void pushdown(int i) {
        if(flag) {
            if((flag >> i) & 1) std::swap(go[0], go[1]);
            REP(i, 2) if(go[i]) go[i]->flag ^= flag;
            flag = 0;
        }
    }
} StatePool[MAXN];
int cnt;

int ans = -1, ansl, ansr;
int n;

Node* newnode() {
    return &StatePool[cnt++];
}

void insert(Node *root, int x, int id) {
    Node *p = root;
    for(int i = 20; i >= 0; --i) {
        int idx = (x >> i) & 1;
        p->pushdown(i);
        if(!p->go[idx]) p->go[idx] = newnode();
        p = p->go[idx];
    }
    p->id = std::max(p->id, id);
}

void check(Node *root, int x, int id) {
    Node *p = root;
    int res = 0;
    for(int i = 20; i >= 0; --i) {
        int idx = (x >> i) & 1;
        p->pushdown(i);
        if(p->go[idx ^ 1]) p = p->go[idx ^ 1], res |= (1 << i);
        else p = p->go[idx];
    }
    if(res > ans) {
        ans = res;
        ansl = p->id;
        ansr = id;
    }
}

int main() {
#ifndef OYK_JUDGE
    freopen("cowxor.in", "r", stdin); freopen("cowxor.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &n);
    Node *root = newnode();
    for(int i = 1, x; i <= n; ++i) {
        scanf("%d", &x);
        if(x > ans) {
            ans = x;
            ansl = ansr = i;
        }

        if(i > 1) check(root, x, i);
        root->flag ^= x;
        insert(root, x, i);
    }
    printf("%d %d %d\n", ans, ansl, ansr);
}
