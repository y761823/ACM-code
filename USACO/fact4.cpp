/*
ID: y7618231
LANG: C++
TASK: fact4
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <numeric>
using namespace std;

int main () {
#ifndef OYK_JUDGE
    freopen("fact4.in", "r", stdin); freopen("fact4.out", "w", stdout);
#endif // OYK_JUDGE
    int n, res = 1, two = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        int t = i;
        while(t % 2 == 0) t /= 2, two++;
        while(t % 5 == 0) t /= 5, two--;

        res *= t;
        while(res % 10 == 0) res /= 10;
        res %= 10;
    }
    if(two > 0) for(int i = 0; i < two; ++i) res = (res * 2) % 10;
    if(two < 0) for(int i = 0; i < -two; ++i) res = (res * 5) % 10;
    printf("%d\n", res);
}
