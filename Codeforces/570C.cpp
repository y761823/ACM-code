#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

const int MAXN = 300010;

char s[MAXN];
int n, m, cnt;

int main() {
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);

    cnt = 0;
    for(int i = 1; i <= n; ++i)
        cnt += (s[i] == '.' && s[i - 1] == '.');

    int p; char c;
    while(m--) {
        scanf("%d %c", &p, &c);
        if(s[p] == '.') {
            cnt -= (s[p - 1] == '.');
            cnt -= (s[p + 1] == '.');
        }
        s[p] = c;
        if(s[p] == '.') {
            cnt += (s[p - 1] == '.');
            cnt += (s[p + 1] == '.');
        }
        printf("%d\n", cnt);
    }
}
