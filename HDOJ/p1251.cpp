////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:55:49
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1251
////Problem Title: 
////Run result: Accept
////Run time:156MS
////Run memory:43880KB
//////////////////System Comment End//////////////////
//发现一条裸的trie?
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    Node* go[26];
    int sum;
    Node() {
        memset(go, 0, sizeof(go));
        sum = 0;
    }
};

void build(Node *root, char *str) {
    Node *p = root;
    for(int i = 0; str[i]; ++i) {
        int idx = str[i] - 'a';
        if(!p->go[idx]) p->go[idx] = new Node;
        p = p->go[idx]; ++p->sum;
    }
}

int query(Node *root, char *str) {
    Node *p = root;
    for(int i = 0; str[i]; ++i) {
        int idx = str[i] - 'a';
        p = p->go[idx];
        if(!p) return 0;
    }
    return p->sum;
}

char s[15];

int main() {
    Node *root = new Node;
    while(gets(s) && *s) build(root, s);
    while(gets(s) && *s) printf("%d\n", query(root, s));
}