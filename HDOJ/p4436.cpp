////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-10-06 22:12:06
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4436
////Problem Title: 
////Run result: Accept
////Run time:406MS
////Run memory:14904KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 110000 + 10;
const int MOD = 2012;
char buf[MAXN];
struct State {
    State *fail, *go[11];
    int val, dp, cnt;
    bool mark;
    /*
    State() :
            fail(0), val(0) {
        memset(go, 0, sizeof go);
    }*/
}*root, *last;
State statePool[MAXN * 2], *cur;

void init() {
    memset(statePool, 0, sizeof(statePool));
    cur = statePool;
    root = last = cur++;
}

void extend(int w) {
    State *p = last, *np = cur++;
    np->val = p->val + 1;
    while (p && !p->go[w])
        p->go[w] = np, p = p->fail;
    if (!p) np->fail = root;
    else {
        State*q = p->go[w];
        if (p->val + 1 == q->val) np->fail = q;
        else {
            State *nq = cur++;
            memcpy(nq->go, q->go, sizeof q->go);
            nq->val = p->val + 1;
            nq->fail = q->fail;
            q->fail = nq;
            np->fail = nq;
            while (p && p->go[w] == q)
                p->go[w] = nq, p = p->fail;
        }
    }
    last = np;
}

inline void update_add(int &a, const int &b) {
    a = (a + b) % MOD;
}

struct Node {
    State *p;
    bool operator < (const Node &rhs) const {
        return p->val < rhs.p->val;
    }
} a[MAXN * 2];

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        init();
        for(int i = 1; i <= n; ++i) {
            scanf("%s", buf);
            for(char *pt = buf; *pt; ++pt)
                extend(*pt - '0');
            extend(10);
        }
        int m = 0, ans = 0;
        for(State *p = statePool; p != cur; ++p) a[m++].p = p;
        sort(a, a + m);
        root->cnt = 1;
        for(int i = 0; i < m; ++i) {
            State *pt = a[i].p;
            if(pt == root->go[0] || pt->mark) continue;
            update_add(ans, pt->dp);
            for(int j = 0; j < 10; ++j) {
                if(!pt->go[j]) continue;
                update_add(pt->go[j]->dp, 10 * pt->dp + pt->cnt * j);
                update_add(pt->go[j]->cnt, pt->cnt);
            }
            if(pt->go[10]) pt->go[10]->mark = true;
        }
        printf("%d\n", ans);
    }
}
