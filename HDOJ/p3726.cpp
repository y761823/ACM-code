////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-07-26 23:56:38
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3726
////Problem Title: 
////Run result: Accept
////Run time:1609MS
////Run memory:5772KB
//////////////////System Comment End//////////////////
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXC = 500010;
const int MAXN = 20010;
const int MAXM = 60010;

int key[MAXN], weight[MAXN], child[MAXN][2], size[MAXN];
int stk[MAXN], top, poi_cnt;//not use point

inline int newNode(int k) {
    int x = (top ? stk[top--] : ++poi_cnt);
    key[x] = k;
    size[x] = 1;
    weight[x] = rand();
    child[x][0] = child[x][1] = 0;
    return x;
}

inline void update(int &x) {
    size[x] = size[child[x][0]] + size[child[x][1]] + 1;//size[0]=0
}

inline void rotate(int &x, int t) {
    int y = child[x][t];
    child[x][t] = child[y][t ^ 1];
    child[y][t ^ 1] = x;
    update(x); update(y);
    x = y;
}

void insert(int &x, int k) {
    if (x == 0) x = newNode(k);
    else {
        int t = (key[x] < k);
        insert(child[x][t], k);
        if (weight[child[x][t]] < weight[x]) rotate(x, t);
    }
    update(x);
}

void remove(int &x, int k) {
    if(key[x] == k) {
        if(child[x][0] && child[x][1]) {
            int t = weight[child[x][0]] < weight[child[x][1]];
            rotate(x, t); remove(child[x][t ^ 1], k);
        }
        else {
            stk[++top] = x;
            x = child[x][0] + child[x][1];
        }
    }
    else remove(child[x][key[x] < k], k);
    if(x > 0) update(x);
}

struct Command {
    char type;
    int x, p;
} commands[MAXC];

int n, m, value[MAXN], from[MAXM], to[MAXM], removed[MAXM];

int fa[MAXN];
int getfather(int x) {
    if(fa[x] == x) return x;
    else return fa[x] = getfather(fa[x]);
}

int root[MAXN];

void mergeto(int &x, int &y) {
    if(child[x][0]) mergeto(child[x][0], y);
    if(child[x][1]) mergeto(child[x][1], y);
    insert(y, key[x]);
    stk[++top] = x;
}

inline void addEdge(int x) {
    int u = getfather(from[x]), v = getfather(to[x]);
    if(u != v) {
        if(size[root[u]] > size[root[v]]) swap(u, v);
        fa[u] = v; mergeto(root[u], root[v]);
    }
}

int kth(int &x, int k) {
    if(x == 0 || k <= 0 || k > size[x]) return 0;
    int s = 0;
    if(child[x][1]) s = size[child[x][1]];
    if(k == s + 1) return key[x];
    if(k <= s) return kth(child[x][1], k);
    return kth(child[x][0], k - s - 1);
}

int query_cnt;
long long query_tot;

void query(int x, int k) {
    ++query_cnt;
    query_tot += kth(root[getfather(x)], k);
}

inline void change_value(int x, int v) {
    int u = getfather(x);
    remove(root[u], value[x]);
    insert(root[u], value[x] = v);
}

int main() {
    int kase = 0;
    size[0] = 0;
    while(scanf("%d%d", &n, &m) != EOF && n) {
        for(int i = 1; i <= n; ++i) scanf("%d", &value[i]);
        for(int i = 1; i <= m; ++i) scanf("%d%d", &from[i], &to[i]);
        memset(removed, 0, sizeof(removed));

        int c = 0;
        while(true) {
            char type;
            int x, p = 0, v = 0;
            scanf(" %c", &type);
            if(type == 'E') break;
            scanf("%d", &x);
            if(type == 'D') removed[x] = 1;
            if(type == 'Q') scanf("%d", &p);
            if(type == 'C') {
                scanf("%d", &v);
                p = value[x];
                value[x] = v;
            }
            commands[c++] = (Command) {type, x, p};
        }

        top = poi_cnt = 0;
        for(int i = 1; i <= n; ++i) {
            fa[i] = i;
            root[i] = newNode(value[i]);
        }
        for(int i = 1; i <= m; ++i) if(!removed[i]) addEdge(i);

        query_tot = query_cnt = 0;
        for(int i = c - 1; i >= 0; --i) {
            if(commands[i].type == 'D') addEdge(commands[i].x);
            if(commands[i].type == 'Q') query(commands[i].x, commands[i].p);
            if(commands[i].type == 'C') change_value(commands[i].x, commands[i].p);
        }
        printf("Case %d: %.6f\n", ++kase, query_tot/(double)query_cnt);
    }
    return 0;
}