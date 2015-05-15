#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 105;

char s[MAXN];
int a[MAXN][MAXN];
int n, m;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) {
        scanf("%s", s);
        for(int j = 1; j <= m; ++j)
            a[i][j] = s[j - 1] - '0';
    }
    int ans = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(a[i][j]) ans += 2;
            for(int k = 1; k <= a[i][j]; ++k) {
                if(a[i - 1][j] < k) ++ans;
                if(a[i + 1][j] < k) ++ans;
                if(a[i][j - 1] < k) ++ans;
                if(a[i][j + 1] < k) ++ans;
            }
        }
    }
    printf("%d\n", ans);
}
