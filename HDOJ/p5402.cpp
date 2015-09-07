#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 110;
const int INF = 0x3f3f3f3f;

int fx[] = {-1, 0, 0, 1};
int fy[] = {0, -1, 1, 0};
char fc[] = "ULRD";

vector<int> ffa = {0, 1, 2, 3};
vector<int> ffb = {3, 0, 2, 1};

int a[MAXN][MAXN];
bool vis[MAXN][MAXN];
int n, m, sum;

bool can_move(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= m && !vis[x][y];
}

bool go(int &x, int &y, int f) {
    int newx = x + fx[f], newy = y + fy[f];
    if(can_move(newx, newy)) {
        putchar(fc[f]);
        x = newx;
        y = newy;
        return true;
    }
    return false;
}

void plan(vector<int> ff, int flag = 0) {
    int x = 1, y = 1;
    while(x != n || y != m) {
        vis[x][y] = true;
        if(flag && flag < n) {
            if(x == flag && go(x, y, 3)) continue;
            if(x == flag + 1 && go(x, y, 0)) continue;
        } else if(flag == n) {
            if(x == flag - 1 && go(x, y, 3)) continue;
            if(x == flag && go(x, y, 0)) continue;
        }
        for(int f : ff) {
            if(go(x, y, f)) break;
        }
    }
    puts("");
}

void need_cut() {
    int mint = INF;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) if((i + j) & 1)
            mint = min(mint, a[i][j]);
    printf("%d\n", sum - mint);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) if((i + j) & 1)
            if(a[i][j] == mint) {
                vis[i][j] = true;
                plan(ffa, i);
                return ;
            }
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        sum = 0;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                scanf("%d", &a[i][j]), vis[i][j] = false, sum += a[i][j];
        if(n % 2 == 0 && m % 2 == 0) need_cut();
        else {
            printf("%d\n", sum);
            if(n & 1) plan(ffa);
            else plan(ffb);
        }
    }
}
