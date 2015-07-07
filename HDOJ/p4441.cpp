////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-10-05 18:12:24
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4441
////Problem Title: 
////Run result: Accept
////Run time:796MS
////Run memory:7424KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 2 * 100010;
const int n = 100000;
int weight[MAXN], child[MAXN][2], size[MAXN], neg[MAXN], val[MAXN], pre[MAXN];
LL sum[MAXN];
int pos[MAXN];
int stk[MAXN], top, node_cnt;

int m, p, x, root;
char s[10];

priority_queue<int> Q;
int int_cnt;

void test(int x) {
    if(child[x][0]) test(child[x][0]);
    cout<<val[x]<<" "<<sum[x]<<" "<<x<<" "<<pre[x]<<" "<<(child[pre[x]][1] == x)<<endl;
    //cout<<val[x]<<endl;
    if(child[x][1]) test(child[x][1]);
}

void init() {
    while(!Q.empty()) Q.pop();
    int_cnt = top = node_cnt = 0;
}

int new_int() {
    if(!Q.empty()) {
        int ret = -Q.top(); Q.pop();
        return ret;
    }
    return ++int_cnt;
}

int new_node(int f, int v) {
    int x = (top ? stk[top--] : ++node_cnt);
    pre[x] = f;
    sum[x] = val[x] = v;
    if(v < 0) pos[n - v] = x;
    else pos[v] = x;
    size[x] = 1; neg[x] = (v < 0);
    weight[x] = rand();
    child[x][0] = child[x][1] = 0;
    return x;
}

void update(int x) {
    sum[x] = sum[child[x][0]] + sum[child[x][1]] + val[x];
    size[x] = size[child[x][0]] + size[child[x][1]] + 1;
    neg[x] = neg[child[x][0]] + neg[child[x][1]] + (val[x] < 0);
}

void rotate(int &x, int t) {
    int y = child[x][t];
    child[x][t] = child[y][t ^ 1];
    child[y][t ^ 1] = x;
    pre[y] = pre[x]; pre[x] = y;
    pre[child[x][t]] = x;
    update(x); update(y);
    x = y;
}

void insert1(int f, int &x, int k, int v) {
    if(x == 0) x = new_node(f, v);
    else {
        int t = (size[child[x][0]] + 1 <= k);
        insert1(x, child[x][t], k - t * (size[child[x][0]] + 1), v);
        if(weight[child[x][t]] < weight[x]) rotate(x, t);
    }
    update(x);
}

int cnt_pos(int x, int t) {
    if(!x) return 0;
    int ret = cnt_pos(pre[x], child[pre[x]][1] == x);
    if(t == 1) ret += size[child[x][0]] - neg[child[x][0]] + (val[x] > 0);
    return ret;
}

void insert2(int f, int &x, int k, int v) {
    if(x == 0) x = new_node(f, v);
    else {
        int t = (neg[child[x][0]] + (val[x] < 0) <= k);
        insert2(x, child[x][t], k - t * (neg[child[x][0]] + (val[x] < 0)), v);
        if(weight[child[x][t]] < weight[x]) rotate(x, t);
    }
    update(x);
}

void remove(int &x) {
    if(child[x][0] && child[x][1]) {
        int t = weight[child[x][0]] < weight[child[x][1]];
        rotate(x, t);
        remove(child[x][t ^ 1]);
    } else {
        stk[++top] = x;
        pre[child[x][0]] = pre[child[x][1]] = pre[x];
        x = child[x][0] + child[x][1];
    }
    if(x > 0) update(x);
}

LL query1(int x, int t) {
    if(!x) return 0;
    LL ret = query1(pre[x], child[pre[x]][1] == x);
    if(t == 0) ret += sum[child[x][1]] + val[x];
    return ret;
}

LL query2(int x, int t) {
    if(!x) return 0;
    LL ret = query2(pre[x], child[pre[x]][1] == x);
    if(t == 1) ret += sum[child[x][0]] + val[x];
    return ret;
}

LL query(int x, int a, int b) {
    LL ret = query1(pre[a], child[pre[a]][1] == a) + sum[child[a][1]];
    ret += query2(pre[b], child[pre[b]][1] == b) + sum[child[b][0]];
    return ret;
}

void update_parent(int t) {
    while(t) update(t), t = pre[t];
}

int main() {
    for(int t = 1; ; ++t) {
        if(scanf("%d", &m) == EOF) break;
        init();
        printf("Case #%d:\n", t);
        root = 0;
        while(m--) {
            scanf("%s%d", s, &x);
            if(*s == 'i') {
                int tmp = new_int();
                insert1(0, root, x, tmp);
                int k = cnt_pos(pos[tmp], 1) - 1;
                insert2(0, root, k, -tmp);
            }
            if(*s == 'r') {
                if(root == pos[x]) {
                    remove(root);
                }
                else {
                    int t = pos[x], p = pre[t];
                    remove(child[p][child[p][1] == t]);
                    update_parent(p);
                }
                int y = x + n;
                if(root == pos[y]) {
                    remove(root);
                }
                else {
                    int t = pos[y], p = pre[t];
                    remove(child[p][child[p][1] == t]);
                    update_parent(p);
                }
                Q.push(-x);
            }
            if(*s == 'q') {
                printf("%I64d\n", query(root, pos[x], pos[x + n]));
            }
                //test(root);
        }
    }
}
