#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 110;
const int MAXM = 510;
const int MOD = 258280327;

vector<pair<int, int> > L[MAXN], H[MAXN];
int src[MAXN][MAXN], tar[MAXN][MAXN];
char op[MAXM];
int x[MAXM], y[MAXM];
bool vis[MAXM];
int T, n, m;

stack<int> ans;

void init() {
    memset(vis + 1, 0, m * sizeof(bool));
    for(int i = 0; i < n; ++i) {
        L[i].clear();
        H[i].clear();
    }
}

void solve() {
    for(int i = 0; i < n; ++i) {
        sort(L[i].begin(), L[i].end());
        sort(H[i].begin(), H[i].end());
    }

    bool flag = true;
    while(flag) {
        flag = false;
        for(int i = 0; i < n; ++i) {
            int j = 0;
            while(j < n && tar[i][j] == 0) ++j;
            if(j == n) continue;

            int col = tar[i][j];
            auto it = lower_bound(H[i].begin(), H[i].end(), make_pair(col, 0));
            if(it == H[i].end()) continue;

            while(j < n && (tar[i][j] == 0 || tar[i][j] == col)) ++j;
            if(j == n) {
                flag = true;
                for(j = 0; j < n; ++j) tar[i][j] = 0;
                swap(*H[i].begin(), *it);
                for(auto p : H[i]) {
                    ans.push(p.second);
                    vis[p.second] = true;
                }
            }
        }

        for(int i = 0; i < n; ++i) {
            int j = 0;
            while(j < n && tar[j][i] == 0) ++j;
            if(j == n) continue;

            int col = tar[j][i];
            auto it = lower_bound(L[i].begin(), L[i].end(), make_pair(col, 0));
            if(it == L[i].end()) continue;

            while(j < n && (tar[j][i] == 0 || tar[j][i] == col)) ++j;
            if(j == n) {
                flag = true;
                for(j = 0; j < n; ++j) tar[j][i] = 0;
                swap(*L[i].begin(), *it);
                for(auto p : L[i]) {
                    ans.push(p.second);
                    vis[p.second] = true;
                }
            }
        }
    }
}

void print() {
    bool flag = false;
    for(int i = 1; i <= m; ++i) if(!vis[i]) {
        if(flag) putchar(' ');
        else flag = true;
        printf("%d", i);
    }
    while(!ans.empty()) {
        if(flag) putchar(' ');
        else flag = true;
        printf("%d", ans.top());
        ans.pop();
    }
    puts("");
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) scanf("%d", &src[i][j]);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) scanf("%d", &tar[i][j]);
        for(int i = 0; i < m; ++i) {
            scanf(" %c%d%d", &op[i], &x[i], &y[i]);
            if(op[i] == 'L') L[x[i] - 1].push_back(make_pair(y[i], i + 1));
            else H[x[i] - 1].push_back(make_pair(y[i], i + 1));
        }
        solve();
        print();
    }
}
