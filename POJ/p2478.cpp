#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 1000010;

LL phi[MAXN];

void phi_table(int n) {
    //for(int i = 2; i <= n; ++i) phi[i] = 0;
    phi[1] = 1;
    for(int i = 2; i <= n; ++i) if(!phi[i])
        for(int j = i; j <= n; j += i) {
            if(!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
}

int main() {
    phi_table(1000000);
    for(int i = 3; i <= 1000000; ++i) phi[i] += phi[i - 1];
    int n;
    while(scanf("%d", &n) != EOF) {
        if(n == 0) break;
        cout<<phi[n]<<endl;
    }
}
