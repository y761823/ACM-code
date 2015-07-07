////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-13 19:45:16
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4787
////Problem Title: 
////Run result: Accept
////Run time:4718MS
////Run memory:7708KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MAXC = MAXN * 3;
const int sz = 2;

struct Node {
    Node *go[sz], *ch[sz], *fail;
    int val;
    bool flag;
} StatePool[MAXC];
int ncnt;

void init() {
    memset(StatePool, 0, ncnt * sizeof(Node));
    ncnt = 0;
}

Node* new_node() {
    return &StatePool[ncnt++];
}

void insert(Node *root, char s[]) {
    Node *p = root;
    for(int i = 0; s[i]; ++i) {
        int idx = s[i] - '0';
        if(!p->go[idx]) p->go[idx] = new_node();
        p = p->go[idx];
    }
    p->flag = true;
}

bool find(Node *root, char s[]) {
    Node *p = root;
    for(int i = 0; s[i]; ++i) {
        int idx = s[i] - '0';
        if(!p->go[idx]) return false;
        p = p->go[idx];
    }
    return p->flag;
}

queue<Node*> que;
void make_fail(Node *root) {
    for(int i = 0; i < sz; ++i) {
        if(root->go[i]) {
            root->go[i]->fail = root;
            root->go[i]->val = root->go[i]->flag;
            que.push(root->go[i]);
            root->ch[i] = root->go[i];
        } else {
            root->ch[i] = root;
        }
    }
    while(!que.empty()) {
        Node *p = que.front(); que.pop();
        for(int i = 0; i < sz; ++i) {
            if(p->go[i]) {
                p->ch[i] = p->go[i];
                p->go[i]->fail = p->fail->ch[i];
                p->go[i]->val = p->go[i]->fail->val + p->go[i]->flag;
                que.push(p->go[i]);
            } else {
                p->ch[i] = p->fail->ch[i];
            }
        }
    }
}

LL solve(Node *root, char s[]) {
    Node *p = root;
    LL res = 0;
    for(int i = 0; s[i]; ++i) {
        int idx = s[i] - '0';
        p = p->ch[idx];
        res += p->val;
    }
    return res;
}

char s[5000010], c;
int n, T, cnt;

void dfs(Node *root, Node *p, int pos) {
    if(p->flag) s[pos] = 0, insert(root, s);
    for(int i = 0; i < sz; ++i) {
        if(p->go[i]) {
            s[pos] = i + '0';
            dfs(root, p->go[i], pos + 1);
        }
    }
}

void merge(Node *rt1, Node *&rt2) {
    dfs(rt1, rt2, 0);
    make_fail(rt1);
    rt2 = new_node();
    cnt = 0;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        init();
        cnt = 0;
        Node *rt1 = new_node(), *rt2 = new_node();
        make_fail(rt1), make_fail(rt2);
        LL last = 0;
        printf("Case #%d:\n", t);
        for(int i = 0; i < n; ++i) {
            scanf(" %c%s", &c, s);
            int len = strlen(s);
            strncat(s + len, s, last % len);
            char *ss = s + last % len;
            if(c == '+') {
                if(find(rt1, ss) || find(rt2, ss)) continue;
                cnt += len;
                insert(rt2, ss);
                //if(cnt > 1000) merge(rt1, rt2);
                make_fail(rt2);
            } else {
                //printf("%s\n", s + last);
                last = solve(rt1, ss) + solve(rt2, ss);
                printf("%I64d\n", last);
            }
        }
    }
}
