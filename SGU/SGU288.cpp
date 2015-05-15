#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2010;

int mat[MAXN][MAXN];
int L[MAXN], R[MAXN];
int n, N;

void solve() {
    for(int i = 1; i <= N / 2; ++i) {
        L[i] = i;
        R[i] = N - i + 1;
    }
    for(int r = 1; r <= N - 1; ++r) {
        for(int i = 1; i <= N / 2; ++i)
            mat[L[i]][R[i]] = mat[R[i]][L[i]] = r;
        int tmp = R[1];
        for(int i = 2; i <= N / 2; ++i) R[i - 1] = R[i];
        R[N / 2] = L[N / 2];
        for(int i = N / 2 - 1; i >= 2; --i) L[i + 1] = L[i];
        L[2] = tmp;
    }
}

void check() {
    for(int i = 1; i <= n; ++i) {
        set<int> st;
        for(int j = 1; j <= n; ++j) st.insert(mat[i][j]);
        assert((int)st.size() == n);
    }
}

int main() {
    scanf("%d", &n);
    N = n + (n & 1);
    solve();

    printf("%d\n", n == 1 ? 0 : N - 1);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) printf("%d ", mat[i][j]);
        puts("");
    }
    //check();
}
