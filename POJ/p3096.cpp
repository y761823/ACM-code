#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
typedef long long LL;

pair<char, char> arr[88];
char str[88];

bool solve() {
    int n = strlen(str);
    for(int i = 1; i < n; ++i) {
        int cnt = 0;
        for(int j = 0; j + i < n; ++j)
            arr[cnt++] = make_pair(str[j], str[j + i]);
        sort(arr, arr + cnt);
        if(unique(arr, arr + cnt) != arr + cnt)
            return false;
    }
    return true;
}

int main() {
    while(scanf("%s", str) != EOF) {
        if(*str == '*') break;
        printf("%s is %ssurprising.\n", str, solve() ? "" : "NOT ");
    }
}
