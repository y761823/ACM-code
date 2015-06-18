#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 66;

char str[10][MAXN], tmp[MAXN];
int n = 60, m, T;

void solve() {
    for(int len = n; len >= 3; --len) {
        int pos = -1;
        for(int i = 0; i + len - 1 < n; ++i) {
            strncpy(tmp, str[0] + i, len); tmp[len] = 0;
            bool flag = true;
            for(int j = 1; j < m && flag; ++j)
                if(strstr(str[j], tmp) == NULL) flag = false;
            if(flag) if(pos == -1 || strncmp(tmp, str[0] + pos, len) < 0)
                pos = i;
        }
        if(pos != -1) {
            for(int i = pos; i < pos + len; ++i) putchar(str[0][i]);
            puts("");
            return ;
        }
    }
    puts("no significant commonalities");
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &m);
        for(int i = 0; i < m; ++i) scanf("%s", str[i]);
        solve();
    }
}
