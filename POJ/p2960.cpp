#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

const int MAXN = 10010;

int s[MAXN], sg[MAXN];
bool mex[110];
int k, m;

void build_sg() {
    for(int i = 0; i <= 10000; ++i) {
        memset(mex, 0, sizeof(mex));
        for(int j = 0; j < k; ++j) if(i - s[j] >= 0) mex[sg[i - s[j]]] = true;
        for(int j = 0; j <= k; ++j) if(!mex[j]) {sg[i] = j; break;};
    }
}

int main() {
    while(scanf("%d", &k) != EOF && k) {
        for(int i = 0; i < k; ++i) scanf("%d", &s[i]);
        build_sg();
        scanf("%d", &m);
        for(int i = 0; i < m; ++i) {
            int n, h, ans = 0;
            scanf("%d", &n);
            while(n--) scanf("%d", &h), ans ^= sg[h];
            putchar(ans ? 'W' : 'L');
        }
        puts("");
    }
}
