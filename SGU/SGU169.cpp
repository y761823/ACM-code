#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; ++i)

bool check_k_a(int k, int a) {
    if(a == 1) return true;
    int res = 1;
    for(int i = 1; i < k; ++i)
        res = (res * 10 + 1) % a;
    return res == 1;
}

bool flag[10];

int main() {
    int k, res = 0;
    scanf("%d", &k);
    for(int i = 1; i <= 9; ++i) flag[i] = check_k_a(k, i);
    res = 0;
    for(int i = 1; i < 9; ++i)
        res += (flag[i] && flag[i + 1]);
    printf("%d\n", res);
}
