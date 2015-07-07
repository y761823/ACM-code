////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-10-17 00:02:57
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5046
////Problem Title: 
////Run result: Accept
////Run time:656MS
////Run memory:392KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 66;
const int MAXC = MAXN;
const int MAXR = MAXN;
const int MAXP = MAXR * MAXC + MAXC;

struct DLX {
    int sum[MAXC];
    int col[MAXP];
    int left[MAXP], right[MAXP], up[MAXP], down[MAXP];
    int sz, n, k;

    void init(int n) {
        this->n = n;
        for(int i = 0; i <= n; ++i) {
            up[i] = down[i] = i;
            left[i] = i - 1; right[i] = i + 1;
            col[i] = i;
        }
        left[0] = n; right[n] = 0;
        sz = n + 1;
        memset(sum, 0, sizeof(sum));
    }

    void add_row(int r, vector<int> &columns) {
        int first = sz;
        for(size_t i = 0; i < columns.size(); ++i) {
            int c = columns[i];
            left[sz] = sz - 1; right[sz] = sz + 1; down[sz] = c; up[sz] = up[c];
            down[up[c]] = sz; up[c] = sz;
            col[sz] = c;
            ++sum[c]; ++sz;
        }
        right[sz - 1] = first; left[first] = sz - 1;
    }

    void remove(int c) {
        for(int i = down[c]; i != c; i = down[i]) {
            right[left[i]] = right[i];
            left[right[i]] = left[i];
        }
    }

    void restore(int c) {
        for(int i = up[c]; i != c; i = up[i]) {
            left[right[i]] = i;
            right[left[i]] = i;
        }
    }

    bool vis[MAXC];

    int estimate() {
        memset(vis, 0, sizeof(vis));
        int res = 0;
        for(int i = right[0]; i != 0; i = right[i]) if(!vis[i]) {
            res++;
            for(int j = down[i]; j != i; j = down[j])
                for(int k = right[j]; k != j; k = right[k]) vis[col[k]] = true;
        }
        return res;
    }

    bool dfs(int dep) {
        if(dep + estimate() > k) return false;
        if(right[0] == 0) return dep <= k;
        int c = right[0];
        for(int i = right[0]; i != 0; i = right[i]) if(sum[i] < sum[c]) c = i;
        for(int i = down[c]; i != c; i = down[i]) {
            remove(i);
            for(int j = right[i]; j != i; j = right[j]) remove(j);
            if(dfs(dep + 1)) return true;
            for(int j = left[i]; j != i; j = left[j]) restore(j);
            restore(i);
        }
        return false;
    }

    bool solve(int k) {
        this->k = k;
        return dfs(0);
    }
} solver;

struct Point {
    int x, y;
    void read() {
        scanf("%d%d", &x, &y);
    }
} p[MAXN];
int n, k, T;

LL dis(const Point &a, const Point &b) {
    return (LL)abs(a.x - b.x) + abs(a.y - b.y);
}

bool check(LL L) {
    solver.init(n);
    for(int i = 0; i < n; ++i) {
        vector<int> columns;
        for(int j = 0; j < n; ++j)
            if(dis(p[i], p[j]) <= L) columns.push_back(j + 1);
        solver.add_row(i, columns);
    }
    return solver.solve(k);
}

LL solve() {
    LL maxdis = 0;
    for(int i = 0; i < n; ++i)
        for(int j = i + 1; j < n; ++j) maxdis = max(maxdis, dis(p[i], p[j]));
    LL l = 0, r = maxdis;
    while(l < r) {
        LL mid = (l + r) >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &k);
        for(int i = 0; i < n; ++i) p[i].read();
        printf("Case #%d: %I64d\n", t, solve());
    }
}
