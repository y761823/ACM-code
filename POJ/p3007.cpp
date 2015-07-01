#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
typedef long long LL;

string s, arr[77 << 3];
char str[177];
int T;

string flip(string s) {
    reverse(s.begin(), s.end());
    return s;
}

int solve() {
    int cnt = 0;
    for(size_t i = 1; i < s.length(); ++i) {
        string a = s.substr(0, i), b = s.substr(i);
        string ra = flip(a), rb = flip(b);
        arr[cnt++] = (a + b);
        arr[cnt++] = (a + rb);
        arr[cnt++] = (ra + b);
        arr[cnt++] = (ra + rb);
        arr[cnt++] = (b + a);
        arr[cnt++] = (b + ra);
        arr[cnt++] = (rb + a);
        arr[cnt++] = (rb + ra);
    }
    sort(arr, arr + cnt);
    return unique(arr, arr + cnt) - arr;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%s", str);
        s = str;
        printf("%d\n", solve());
    }
}
