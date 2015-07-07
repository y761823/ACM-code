////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-02 23:17:34
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4900
////Problem Title: 
////Run result: Accept
////Run time:1453MS
////Run memory:1068KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 310;
const int INF = 0x3f3f3f3f;

int mat[MAXN][MAXN], dif[MAXN][MAXN];
int label[MAXN], hash[MAXN], tmp[MAXN];
int n, k, T;

int head[MAXN], ecnt;
int to[MAXN << 1], next[MAXN << 1];

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

int que[MAXN], dis[MAXN];

void bfs(int st) {
    memset(dis + 1, 0x3f, n * sizeof(int));
    int l = 0, r = 0;
    dis[que[r++] = st] = 0;
    while(l != r) {
        int u = que[l++];
        for(int p = head[u]; ~p; p = next[p]) {
            int &v = to[p];
            if(dis[u] + 1 < dis[v]) {
                dis[v] = dis[u] + 1;
                que[r++] = v;
            }
        }
    }
    for(int i = 1; i <= n; ++i) mat[st][i] = dis[i];
}

int cnt[MAXN];

void dfs(int u, int f, int& c, int st) {
    if(++cnt[hash[u]] == 1) c++;
    dif[st][u] = c;
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        if(v == f) continue;
        dfs(v, u, c, st);
    }
    if(--cnt[hash[u]] == 0) c--;
}
//ÅÅÁÐ×éºÏ
double per[MAXN];
void initPer(int n = 300) {
    per[0] = log(1);
    for(int i = 1; i <= n; ++i)
        per[i] = per[i - 1] + log(i);
}
double c(int n, int k) {
    return per[n] - per[n - k] - per[k];
}

double calc(int a, int b) {
    int cnt = 2;
    for(int i = 1; i <= n; ++i) {
        if(i == a || i == b) continue;
        if(mat[i][a] > mat[a][b] || mat[i][b] > mat[a][b]) continue;
        if(mat[i][b] == mat[a][b] && i < a) continue;
        if(mat[i][a] == mat[a][b] && i < b) continue;
        cnt++;
    }
    if(cnt >= k) return dif[a][b] * exp(c(cnt - 2, k - 2) - c(n, k));
    else return 0;
}

double solve() {
    if(n < k || k == 0) return 0;
    if(k == 1) return 0;
    double res = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = i + 1; j <= n; ++j) {
            res += calc(i, j);
        }
    }
    return res;
}

int main() {
    initPer();
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        init();
        for(int i = 1, a, b; i < n; ++i) {
            scanf("%d%d", &a, &b);
            add_edge(a, b);
        }
        for(int i = 1; i <= n; ++i) bfs(i);

        for(int i = 1; i <= n; ++i) scanf("%d", &hash[i]);
        int cnt = 0;
        for(int i = 1; i <= n; ++i) tmp[cnt++] = hash[i];
        sort(tmp, tmp + cnt);
        cnt = unique(tmp, tmp + cnt) - tmp;
        for(int i = 1; i <= n; ++i) hash[i] = lower_bound(tmp, tmp + cnt, hash[i]) - tmp;
        for(int i = 1, c = 0; i <= n; ++i) dfs(i, 0, c, i);

        printf("%.10f\n", solve());
    }
}
