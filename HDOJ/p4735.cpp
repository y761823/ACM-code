////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-07-25 23:04:21
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4735
////Problem Title: 
////Run result: Accept
////Run time:1171MS
////Run memory:352KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 55;
const int MAXC = MAXN;
const int MAXR = MAXN;
const int MAXP = MAXR * MAXN + MAXC;

int boy[MAXN];
int mat[MAXN][MAXN];
int n, D, boys;

struct DLX {
    int n, sz;//列数，结点总数
    int sum[MAXC];//每列拥有的结点数
    int row[MAXP], col[MAXP];//结点所在的行和列
    int left[MAXP], right[MAXP], up[MAXP], down[MAXP];//十字链表
    int ans, anst[MAXR];

    void init(int nn) {
        n = nn;
        for(int i = 0; i <= n; ++i) {
            up[i] = down[i] = i;
            left[i] = i - 1; right[i] = i + 1;
            col[i] = i;
        }
        right[n] = 0; left[0] = n;
        sz = n + 1;
        memset(sum, 0, sizeof(sum));
    }

    void add_row(int r, vector<int> &columns) {
        int first = sz;
        for(int i = 0, len = columns.size(); i < len; ++i) {
            int c = columns[i];
            left[sz] = sz - 1; right[sz] = sz + 1; down[sz] = c; up[sz] = up[c];
            down[up[c]] = sz; up[c] = sz;
            row[sz] = r; col[sz] = c;
            ++sum[c]; ++sz;
        }
        right[sz - 1] = first; left[first] = sz - 1;
    }

    void remove(int c) {
        for(int i = down[c]; i != c; i = down[i]) {
            left[right[i]] = left[i];
            right[left[i]] = right[i];
        }
    }

    void restore(int c) {
        for(int i = down[c]; i != c; i = down[i]) {
            left[right[i]] = i;
            right[left[i]] = i;
        }
    }

    bool vis[MAXC];

    int A() {
        memset(vis, 0, sizeof(vis));
        int ret = 0;
        for(int i = right[0]; i != 0; i = right[i]) if(!vis[i]) {
            ++ret;
            for(int j = down[i]; j != i; j = down[j]) {
                for(int k = right[j]; k != j; k = right[k]) vis[col[k]] = true;
            }
        }
        return ret;
    }

    void dfs(int dep) {
        if(dep + A() > boys) return ;
        int tmp = 0;
        for(int i = 0; i < dep; ++i) tmp += boy[anst[i]];
        if(dep - tmp >= ans) return ;
        if(right[0] == 0) {
            ans = dep - tmp;
            return ;
        }
        int c = right[0];
        for(int i = right[0]; i != 0; i = right[i]) if(sum[i] < sum[c]) c = i;
        for(int i = down[c]; i != c; i = down[i]) {
            anst[dep] = row[i];
            remove(i);
            for(int j = right[i]; j != i; j = right[j]) remove(j);
            dfs(dep + 1);
            for(int j = left[i]; j != i; j = left[j]) restore(j);
            restore(i);
        }
        restore(c);
    }

    bool solve() {
        ans = n + 1;
        dfs(0);
        return ans != n + 1;
    }
} S;

void floyd() {
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i) if(mat[i][k] <= D)
            for(int j = 1; j <= n; ++j) if(mat[k][j] <= D)
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
}

int main() {
    int T; scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &D);
        memset(mat, 0x3f, sizeof(mat));
        boys = 0;
        for(int i = 1; i <= n; ++i) scanf("%d", &boy[i]), boys += boy[i];
        for(int i = 1; i < n; ++i) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            mat[u][v] = mat[v][u] = c;
        }
        for(int i = 1; i <= n; ++i) mat[i][i] = 0;
        floyd();
        S.init(n);
        for(int i = 1; i <= n; ++i) {
            vector<int> columns;
            for(int j = 1; j <= n; ++j) if(mat[i][j] <= D) columns.push_back(j);
            S.add_row(i, columns);
        }
        bool flag = S.solve();
        printf("Case #%d: ", t);
        if(flag) printf("%d\n", S.ans);
        else puts("-1");
    }
}