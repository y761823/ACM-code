/*
ID: y7618231
PROG: friday
LANG: C++
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 7;

int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int cnt[MAXN], n;

bool isleap(int n) {
    return n % 400 == 0 || (n % 4 == 0 && n % 100 != 0);
}

int main() {
#ifndef OYK_JUDGE
    freopen("friday.in", "r", stdin); freopen("friday.out", "w", stdout);
#endif
    scanf("%d", &n);
    int daycnt = 0;
    for(int i = 1900; i < 1900 + n; ++i) {
        for(int j = 1; j <= 12; ++j) {
            cnt[(daycnt + 12) % 7]++;
            daycnt += days[j];
            if(j == 2 && isleap(i)) daycnt++;
        }
    }
    printf("%d %d %d %d %d %d %d\n", cnt[5], cnt[6], cnt[0], cnt[1], cnt[2], cnt[3], cnt[4]);
}
