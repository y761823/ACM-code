/*
ID: y7618231
LANG: C++
TASK: msquare
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 365;
const int INF = 0x3f3f3f3f;

int transA(int src) {
    static char s[9];
    sprintf(s, "%d", src);
    for(int i = 0; i < 4; ++i) swap(s[i], s[i + 4]);
    sscanf(s, "%d", &src);
    return src;
}

int transB(int src) {
    static char s[9];
    sprintf(s, "%d", src);
    for(int i = 4 - 1; i > 0; --i) {
        swap(s[i - 1], s[i]);
        swap(s[i + 3], s[i + 4]);
    }
    sscanf(s, "%d", &src);
    return src;
}

int transC(int src) {
    static char s[9];
    sprintf(s, "%d", src);
    swap(s[1], s[2]); swap(s[1], s[6]); swap(s[1], s[5]);
    sscanf(s, "%d", &src);
    return src;
}

struct Node {
    int pre, step;
    char op;
    Node() {}
    Node(int pre, int step, char op): pre(pre), step(step), op(op) {}
};

map< int, Node > Oyk;
int src = 12348765, goal;

void bfs() {
    queue<int> que; que.push(src);
    Oyk[src] = Node(-1, 0, 0);
    while(!que.empty()) {
        int u = que.front(); que.pop();
        if(u == goal) break;
        int dis = Oyk[u].step + 1, v;

        v = transA(u);
        if(Oyk.find(v) == Oyk.end()) Oyk[v] = Node(u, dis, 'A'), que.push(v);

        v = transB(u);
        if(Oyk.find(v) == Oyk.end()) Oyk[v] = Node(u, dis, 'B'), que.push(v);

        v = transC(u);
        if(Oyk.find(v) == Oyk.end()) Oyk[v] = Node(u, dis, 'C'), que.push(v);
    }
}

void print(int u) {
    if(Oyk[u].pre != -1) {
        print(Oyk[u].pre);
        putchar(Oyk[u].op);
    }
}

int main() {
#ifndef OYK_JUDGE
    freopen("msquare.in", "r", stdin); freopen("msquare.out", "w", stdout);
#endif // OYK_JUDGE
    static char s[9];
    for(int i = 0; i < 4; ++i) scanf(" %c", &s[i]);
    for(int i = 7; i >= 4; --i) scanf(" %c", &s[i]);
    s[8] = 0;
    sscanf(s, "%d", &goal);
    bfs();
    printf("%d\n", Oyk[goal].step);
    print(goal);
    puts("");
}
