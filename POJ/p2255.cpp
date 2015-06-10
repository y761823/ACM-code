#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <numeric>
using namespace std;

const int MAXN = 33;

char s1[MAXN], s2[MAXN];

void solve(char *a, char *b, int n) {
    if(n == 0) return ;
    char *c = strchr(b, *a);
    int ls = c - b;
    solve(a + 1, b, ls);
    solve(a + ls + 1, b + ls + 1, n - ls - 1);
    putchar(*a);
}

int main() {
    while(scanf("%s%s", s1, s2) != EOF) {
        solve(s1, s2, strlen(s1));
        puts("");
    }
}
