/*
ID: y7618231
PROG: ride
LANG: C++
*/
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

const int MAXN = 10;

char s1[MAXN], s2[MAXN];

int cal(char s[]) {
    int res = 1;
    for(int i = 0; s[i]; ++i)
        res *= (s[i] - 'A' + 1);
    return res % 47;
}

int main() {
    freopen("ride.in", "r", stdin);
    freopen("ride.out", "w", stdout);
    scanf("%s%s", s1, s2);
    puts(cal(s1) == cal(s2) ? "GO" : "STAY");
    return 0;
}
