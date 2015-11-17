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

char str[MAXN];
int cost[26];
int n, T;


State* new_node(int val) {
    memset(ptr->go, 0, sizeof ptr->go);
    ptr->par = nullptr;
    ptr->val = val;
    ptr->first = -1;
    return ptr++;
}

void init() {
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

State *end[MAXN];
LL dp[MAXN];
int match[MAXN], A, B;
int que[MAXN], l, r;
/*
dp[i] = dp[i - 1] + cost[s[i] - 'a'];
dp[i] = min{ dp[j] + (i - j) * A + 2 * B }
      = min{ dp[j] - j * A} + i * A + 2 * B
*/
LL getval(int i) {
    return dp[i] - (LL)i * A;
}

LL solve() {
    init();
    for(int i = 0; i < n; ++i) {
        expend(str[i] - 'a');
        end[i] = last;
    }
    for(int i = 0; i < n; ++i) {
        for(State *p = end[i]; p && p->first == -1; p = p->par)
            p->first = i;
    }

    State *p = root;
    for(int i = 0, l = 0; i < n; ++i) {
        int w = str[i] - 'a';
        while(!p->go[w]) {
            p = p->par;
            l = p->val;
        }
        p = p->go[w];
        l++;
        while(p->first > i - l) {
            l--;
            if(p->par->val == l)
                p = p->par;
        }
        match[i] = l;
    }

    l = r = 0;
    for(int i = 0; i < n; ++i) {
        dp[i] = cost[str[i] - 'a'];
        if(i > 0) dp[i] += dp[i - 1];

        while(l != r && que[l] < i - match[i])
            ++l;
        if(l < r) {
            int j = que[l];
            dp[i] = std::min(dp[i], dp[j] + LL(i - j) * A + 2 * B);
        }
        while(l != r && getval(que[r - 1]) >= getval(i))
            --r;
        que[r++] = i;
    }
    return dp[n - 1];
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%s", str);
        n = strlen(str);
        for(int i = 0; i < 26; ++i)
            scanf("%d", &cost[i]);
        scanf("%d%d", &A, &B);
        printf("Case #%d: %I64d\n", t, solve());
    }
}
