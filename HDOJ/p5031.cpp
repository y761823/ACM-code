////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-10-16 19:54:20
////Compiler: Visual C++
//////////////////////////////////////////////////////
////Problem ID: 5031
////Problem Title: 
////Run result: Accept
////Run time:906MS
////Run memory:252KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 55;

int mat[MAXN][MAXN], gcd[MAXN][MAXN];
int ans;
int n, m, T;

bool check(int r, int c) {
    return 1 <= r && r <= n && 1 <= c && c <= m;
}

void dfs(int dep, int remain) {
    if(dep >= ans) return ;
    if(remain == 0) {
        ans = dep;
        return ;
    }

    int cnt = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) cnt = max(cnt, mat[i][j]);
    if(dep + cnt >= ans) return ;

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(mat[i][j] == 0) continue;
            //column
            if(i == 1 && n >= 3) {
                cnt = 0;
                for(int k = 1; k <= n; ++k) cnt += (mat[k][j] > 0);
                if(cnt == n) {
                    for(int k = 1; k <= n; ++k) mat[k][j]--;
                    dfs(dep + 1, remain - cnt);
                    for(int k = 1; k <= n; ++k) mat[k][j]++;
                }
            }
            //row
            if(j == 1 && m >= 3) {
                cnt = 0;
                for(int k = 1; k <= m; ++k) cnt += (mat[i][k] > 0);
                if(cnt == m) {
                    for(int k = 1; k <= m; ++k) mat[i][k]--;
                    dfs(dep + 1, remain - cnt);
                    for(int k = 1; k <= m; ++k) mat[i][k]++;
                }
            }
            //else
            for(int r = i + 1; r <= n; ++r) {
                for(int c = 1; c <= m; ++c) if(c != j) {
                    if(mat[r][c] == 0) continue;
                    int x = r - i, y = c - j;
                    if(gcd[x][abs(y)] != 1 || check(i - x, j - y)) continue;
                    bool flag = true;
                    cnt = 0;
                    for(int nr = i, nc = j; flag && check(nr, nc); nr += x, nc += y) {
                        if(mat[nr][nc] == 0) flag = false;
                        cnt += (mat[nr][nc] > 0);
                    }
                    if(flag && cnt >= 3) {
                        for(int nr = i, nc = j; check(nr, nc); nr += x, nc += y) {
                            mat[nr][nc]--;
                        }
                        dfs(dep + 1, remain - cnt);
                        for(int nr = i, nc = j; check(nr, nc); nr += x, nc += y) {
                            mat[nr][nc]++;
                        }
                    }
                }
            }
            return ;
        }
    }
}

int get_gcd(int a, int b) {
    return b == 0 ? a : get_gcd(b, a % b);
}

int main() {
    for(int i = 1; i < MAXN; ++i)
        for(int j = 1; j < MAXN; ++j) gcd[i][j] = get_gcd(i, j);

    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        ++n, ++m;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) scanf("%d", &mat[i][j]);
        int sum = 0;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) sum += mat[i][j];
        ans = min(14, sum / 3);
        dfs(0, sum);
        printf("%d\n", ans);
    }
}
