#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long LL;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

struct State {
    State *par, *go[26];
    int val, first;
} *root, *last;
State statePool[MAXN << 1], *ptr = statePool;
State *end[MAXN];

char s[MAXN];
int n, k, T;

State* new_node(int val) {
    memset(ptr->go, 0, sizeof ptr->go);
    ptr->par = nullptr;
    ptr->val = val;
    ptr->first = -1;
    return ptr++;
}

void init_sam() {
    ptr = statePool;
    root = last = new_node(0);
}

void expend(int w) {
    State *p = last, *np = new_node(p->val + 1);
    while(p && !p->go[w])
        p->go[w] = np, p = p->par;
    if(!p) np->par = root;
    else {
        State *q = p->go[w];
        if(p->val + 1 == q->val) np->par = q;
        else {
            State *nq = new_node(p->val + 1);
            memcpy(nq->go, q->go, sizeof q->go);
            nq->par = q->par;
            q->par = nq;
            np->par = nq;
            while(p && p->go[w] == q)
                p->go[w] = nq, p = p->par;
        }
    }
    last = np;
}

int query(int pos, int &first) {
    State *p = root;
    int res = 0;
    while(pos + res < n) {
        int w = s[pos + res] - 'a';
        if(p->go[w] && p->go[w]->first - res < pos) {
            p = p->go[w];
            first = p->first;
            res++;
        } else {
            break;
        }
    }
    return res;
}

void solve() {
    init_sam();
    for(int i = 0; i < n; ++i) {
        expend(s[i] - 'a');
        end[i] = last;
    }
    for(int i = 0; i < n; ++i) {
        for(State *p = end[i]; p && p->first == -1; p = p->par)
            p->first = i;
    }

    int pos = 0;
    while(pos < n) {
        int first, add = query(pos, first);
        if(add) {
            printf("%d %d\n", add, first - add + 1);
            pos += add;
        } else {
            printf("-1 %d\n", s[pos++]);
        }
    }
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%s", s);
        n = strlen(s);
        printf("Case #%d:\n", t);
        solve();
    }
}
