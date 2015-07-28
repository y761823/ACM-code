#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
#include <cmath>
using namespace std;

bool vis[8][8][8][8][15];
double dp[8][8][8][8][15];
double avg;
int mat[8][8], sum[8][8];
int n = 8, m;

double getSum(int r1, int r2, int c1, int c2) {
    int res = sum[r2][c2];
    if(r1 > 0) res -= sum[r1 - 1][c2];
    if(c1 > 0) res -= sum[r2][c1 - 1];
    if(r1 > 0 && c1 > 0) res += sum[r1 - 1][c1 - 1];
    return (res - avg) * (res - avg);
}

double dfs(int r1, int r2, int c1, int c2, int k) {
    if(vis[r1][r2][c1][c2][k]) return dp[r1][r2][c1][c2][k];
    double &res = dp[r1][r2][c1][c2][k];
    vis[r1][r2][c1][c2][k] = true;
    res = 1e100;

    if(k == 1)
        return res = getSum(r1, r2, c1, c2);

    for(int i = r1; i < r2; ++i) {
        res = min(res, dfs(r1, i, c1, c2, k - 1) + getSum(i + 1, r2, c1, c2));
        res = min(res, dfs(i + 1, r2, c1, c2, k - 1) + getSum(r1, i, c1, c2));
    }

    for(int i = c1; i < c2; ++i) {
        res = min(res, dfs(r1, r2, c1, i, k - 1) + getSum(r1, r2, i + 1, c2));
        res = min(res, dfs(r1, r2, i + 1, c2, k - 1) + getSum(r1, r2, c1, i));
    }

    return res;
}

int main() {
    scanf("%d", &m);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            scanf("%d", &mat[i][j]);
            if(i == 0 && j == 0)
                sum[i][j] = mat[i][j];
            if(i == 0 && j != 0)
                sum[i][j] = sum[i][j - 1] + mat[i][j];
            if(i != 0 && j == 0)
                sum[i][j] = sum[i - 1][j] + mat[i][j];
            if(i != 0 && j != 0)
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + mat[i][j];
        }
    }
    avg = sum[n - 1][n - 1] / double(m);

    printf("%.3f\n", sqrt(dfs(0, 7, 0, 7, m) / m));
}
