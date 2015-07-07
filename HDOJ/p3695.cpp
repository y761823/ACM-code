////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-09-05 16:58:02
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3695
////Problem Title: 
////Run result: Accept
////Run time:1671MS
////Run memory:55420KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 5000010;
const int MAX = 1010;

struct Node {
    Node *go[26], *fail;
    int src;
    bool mark;
    Node(int _src) {
        src = _src;
        fail = 0;
        mark = 0;
        memset(go, 0, sizeof(go));
    }
    ~Node() {
        for(int i = 0; i < 26; ++i)
            if(go[i]) delete go[i];
    }
};

void build(Node *root, char *str, int id) {
    Node *p = root;
    for(int i = 0; str[i]; ++i) {
        int index = str[i] - 'A';
        if(!p->go[index]) p->go[index] = new Node(-1);
        p = p->go[index];
    }
    p->src = id;
}

void makeFail(Node *root) {
    queue<Node*> que;que.push(root);
    while(!que.empty()) {
        Node *tmp = que.front(); que.pop();
        for(int i = 0; i < 26; ++i) {
            if(!tmp->go[i]) continue;
            if(tmp == root) tmp->go[i]->fail = root;
            else {
                Node *p = tmp->fail;
                while(p) {
                    if(p->go[i]) {
                        tmp->go[i]->fail = p->go[i];
                        break;
                    }
                    p = p->fail;
                }
                if(!p) tmp->go[i]->fail = root;
            }
            que.push(tmp->go[i]);
        }
    }
    root->fail = root;
}

bool vis[1010];

void solve(Node *root, char *str) {
    Node *tmp = root;
    for(char *now = str; *now; ++now) {
        int index = *now - 'A';
        while(tmp != root && !tmp->go[index]) tmp = tmp->fail;
        if(tmp->go[index]) tmp = tmp->go[index];
        if(tmp->src != -1) {
            Node *q = tmp;
            while(q != root && !q->mark) {
                q->mark = true;
                if(q->src > 0) vis[q->src] = true;
                q = q->fail;
            }
        }
    }
}

int make_ans(int n) {
    int ret = 0;
    for(int i = 1; i <= n; ++i)
        ret += vis[i];
    return ret;
}

void trans(char *ss, char *tt) {
    for(int i = 0; ss[i]; ++i) {
        if(isalpha(ss[i])) *tt++ = ss[i];
        else {
            ++i;
            int t = 0;
            while(isdigit(ss[i])) t = t * 10 + ss[i] - '0', ++i;
            for(int j = 0; j < t; ++j) *tt++ = ss[i];
            ++i;
        }
    }
    *tt = 0;
}

char ss[MAXN], s[MAXN];
char tmp[MAX];

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        Node *root = new Node(-1);
        for(int i = 1; i <= n; ++i) {
            scanf("%s", tmp);
            build(root, tmp, i);
            reverse(tmp, tmp + strlen(tmp));
            build(root, tmp, i);
        }
        makeFail(root);
        scanf("%s", ss);
        trans(ss, s);
        //printf("%s\n", s);
        memset(vis, 0, sizeof(vis));
        solve(root, s);
        printf("%d\n", make_ans(n));
        delete root;
    }
}
