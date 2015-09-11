#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXV = 100010;

struct Node {
    Node *go[26], *fail;
    int add;
} statePool[MAXV];
int ncnt;

Node* new_node() {
    Node *x = statePool + ncnt++;
    memset(x, 0, sizeof(*x));
    return x;
}

void build(Node *rt, char str[]) {
    Node *p = rt;
    for(int i = 0; str[i]; ++i) {
        int idx = str[i] - 'a';
        if(!p->go[idx]) p->go[idx] = new_node();
        p = p->go[idx];
    }
    p->add++;
}

void make_fail(Node *rt) {
    queue<Node*> que;
    for(int i = 0; i < 26; ++i)
        if(rt->go[i]) rt->go[i]->fail = rt, que.push(rt->go[i]);
        else rt->go[i] = rt;
    while(!que.empty()) {
        Node *p = que.front(); que.pop();
        for(int i = 0; i < 26; ++i) {
            Node* &q = p->go[i];
            if(q) {
                que.push(q);
                q->fail = p->fail->go[i];
                q->add += q->fail->add;
            } else {
                q = p->fail->go[i];
            }
        }
    }
}

int solve(Node *rt, char str[]) {
    Node *p = rt;
    int res = 0;
    for(int i = 0; str[i]; ++i) {
        int idx = str[i] - 'a';
        p = p->go[idx];
        res += p->add;
    }
    return res;
}

char a[MAXV << 1], b[MAXV];
int beg[MAXV];
int T, n, m;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i) {
            beg[i] = (i ? beg[i - 1] + strlen(a + beg[i - 1]) + 1 : 0);
            scanf("%s", a + beg[i]);
        }
        ncnt = 0;
        Node *rt = new_node();
        for(int i = 0; i < m; ++i) {
            scanf("%s", b);
            build(rt, b);
        }
        make_fail(rt);
        for(int i = 0; i < n; ++i) {
            printf("%d\n", solve(rt, a + beg[i]));
        }
    }
}
