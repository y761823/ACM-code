#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;

int vis[MAXN];
int x, y;

int main() {
    scanf("%d%d", &x, &y);
    memset(vis, -1, y * sizeof(int));
    x %= y;
    for(int cnt = 0; ; ++cnt) {
        if(x == 0) {
            printf("%d 0\n", cnt);
            break;
        }
        if(~vis[x]) {
            printf("%d %d\n", vis[x], cnt - vis[x]);
            break;
        }
        vis[x] = cnt;
        x = x * 10 % y;
    }
}
