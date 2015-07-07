////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-05-23 19:59:43
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4825
////Problem Title: 
////Run result: Accept
////Run time:312MS
////Run memory:12448KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int MAXT = 100005;

struct Node {
    Node* go[2];
} StatePool[MAXT * 32];
int ncnt = 0;

void init() {
    memset(StatePool, 0, sizeof(Node) * ncnt);
    ncnt = 0;
}

Node* newNode() {
    return &StatePool[ncnt++];
}

void insert(Node* root, unsigned int val) {
    Node* p = root;
    for(int i = 31; i >= 0; --i) {
        int t = (val >> i) & 1;
        if(!p->go[t]) p->go[t] = newNode();
        p = p->go[t];
    }
}

unsigned int solve(Node* root, unsigned int val) {
    Node* p = root;
    unsigned int res = 0;
    for(int i = 31; i >= 0; --i) {
        int t = (val >> i) & 1;
        if(p->go[!t]) {
            p = p->go[!t];
            res = (res << 1) | (!t);
        } else {
            p = p->go[t];
            res = (res << 1) | (t);
        }
    }
    return res;
}

int T, n, m;

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        init();
        Node* root = newNode();
        unsigned int k;
        for(int i = 0; i < n; ++i) {
            scanf("%u", &k);
            insert(root, k);
        }
        printf("Case #%d:\n", t);
        for(int i = 0; i < m; ++i) {
            scanf("%u", &k);
            printf("%u\n", solve(root, k));
        }
    }
}
