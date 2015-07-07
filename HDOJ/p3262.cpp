////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:04:25
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3262
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:324KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 35;
const int MAXK = 55;

struct Node {
    int id, t, q;
    void read(int i) {
        int hh, mm;
        scanf("%d:%d %d", &hh, &mm, &q);
        t = hh * 60 + mm;
        id = i;
    }
    bool operator < (const Node &rhs) const {
        return t < rhs.t;
    }
};

Node a[MAXK];
int mat[MAXN][MAXN];
bool use[MAXN][MAXN];
int ans[MAXK][2], leave[MAXK];
int n, m, k;

void init() {
    memset(use, 0, sizeof(use));
}

bool check(int x, int y, int l) {
    for(int i = 0; i < l; ++i)
        if(use[x][y + i]) return false;
    return true;
}

void make_use(int x, int y, int l) {
    for(int i = 0; i < l; ++i)
        use[x][y + i] = true;
}

void solve() {
    int max_comf, ans_i, ans_j;
    bool flag;
    for(int x = 1; x <= k; ++x) {
        flag = false;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m - a[x].q + 1; ++j) {
                if(!flag || mat[i][j] > max_comf) {
                    if(!check(i, j, a[x].q)) continue;
                    flag = true;
                    ans_i = i; ans_j = j;
                    max_comf = mat[i][j];
                }
            }
        }
        if(flag) {
            leave[a[x].id] = false;
            ans[a[x].id][0] = ans_i;
            ans[a[x].id][1] = ans_j;
            make_use(ans_i, ans_j, a[x].q);
            continue;
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(!flag || mat[i][j] > max_comf) {
                    if(use[i][j]) continue;
                    flag = true;
                    ans_i = i; ans_j = j;
                    max_comf = mat[i][j];
                }
            }
        }
        if(flag) {
            leave[a[x].id] = false;
            ans[a[x].id][0] = ans_i;
            ans[a[x].id][1] = ans_j;
            use[ans_i][ans_j] = true;
            continue;
        }
        else leave[a[x].id] = true;
    }
}

int main() {
    while(scanf("%d%d%d", &n, &m, &k) != EOF) {
        if(n == 0 && m == 0 && k == 0) break;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) scanf("%d", &mat[i][j]);
        for(int i = 1; i <= k; ++i) a[i].read(i);
        sort(a + 1, a + k + 1);
        init();
        solve();
        for(int i = 1; i <= k; ++i) {
            if(leave[i]) puts("-1");
            else printf("%d %d\n", ans[i][0], ans[i][1]);
        }
    }
}