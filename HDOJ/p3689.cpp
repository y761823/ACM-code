////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:50:52
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3689
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:268KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

struct Node {
    Node *go[26], *fail;
    int id;
    Node(int i = 0) {
        id = i;
        memset(go, 0, sizeof(go));
        fail = 0;
    }
};

void build(Node *root, char *str) {
    Node *p = root;
    for(int i = 0; str[i]; ++i) {
        int index = str[i] - 'a';
        if(!p->go[index]) p->go[index] = new Node(i + 1);
        p = p->go[index];
    }
}

void makeFail(Node *root) {
    queue<Node*> que; que.push(root);
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

void makeGo(Node *root, char *str) {
    Node *tmp = root;
    for(int i = 0; i < 26; ++i)
        if(i != str[0] - 'a') root->go[i] = root;
    for(int i = 0; str[i]; ++i) {
        int index = str[i] - 'a';
        tmp = tmp->go[index];
        for(int j = 0; j < 26; ++j) {
            Node *p = tmp;
            while(true) {
                if(p->go[j]) {
                    tmp->go[j] = p->go[j];
                    break;
                }
                p = p->fail;
                if(p == root) break;
            }
            if(p == root) tmp->go[j] = root->go[j];
        }
    }
}

int n, m;
char s[13];
double dp[2][13];
double pro[30];

double solve(Node *root) {
    int cur = 0, len = strlen(s);
    dp[cur][0] = 1;
    for(int i = 1; i <= len; ++i) dp[cur][i] = 0;
    for(int t = 0; t < m; ++t) {
        for(int i = 0; i <= len; ++i) dp[cur ^ 1][i] = 0;
        for(int i = 0; i < 26; ++i)
            dp[cur ^ 1][root->go[i]->id] += pro[i] * dp[cur][0];
        Node *tmp = root;
        for(int i = 0; i < len - 1; ++i) {
            int index = s[i] - 'a';
            tmp = tmp->go[index];
            for(int j = 0; j < 26; ++j)
                dp[cur ^ 1][tmp->go[j]->id] += pro[j] * dp[cur][i + 1];
        }
        cur ^= 1;
        //for(int i = 0; i <= len; ++i) printf("%.6f ", dp[cur][i]); printf("\n");
    }
    double ret = 0;
    for(int i = 0; i < len; ++i) {
        ret += dp[cur][i];
    }
    return 1 - ret;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        char c; double x;
        for(int i = 0; i < 26; ++i) pro[i] = 0;
        for(int i = 0; i < n; ++i)
            scanf(" %c%lf", &c, &x), pro[c - 'a'] = x;
        scanf("%s", s);
        Node *root = new Node;
        build(root, s);
        makeFail(root);
        makeGo(root, s);
        printf("%.2f%%\n", solve(root) * 100);
    }
}