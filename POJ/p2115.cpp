#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define forall(i, v) for(__typeof(v.begin()) i = v.begin(); i != v.end(); ++i)
typedef long long LL;

void exgcd(LL a, LL b, LL &x, LL &y) {
    if(!b) x = 1, y = 0;
    else {
        exgcd(b, a % b, y, x);
        y -= x * (a / b);
    }
}

LL solve(LL a, LL b, LL c) {
    LL gcd = __gcd(a, b), x, y;
    exgcd(a / gcd, b / gcd, x, y);
    b /= gcd;
    return (x * (c / gcd) % b + b) % b;
}

LL A, B, C, k;
int main() {
    while(cin>>A>>B>>C>>k) {
        if(A == 0 && B == 0 && C == 0 && k == 0) break;
        k = 1LL << k;
        LL D = (B - A + k) % k;
        if(D % __gcd(C, k)) {
            puts("FOREVER");
        } else {
            cout<<solve(C, k, D)<<endl;
        }
    }
}
