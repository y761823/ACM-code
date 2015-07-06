#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const LL MAX = 100000;

LL calc(LL i, LL j) {
    return i * i + MAX * i + j * j - MAX * j + i * j;
}

LL T, n, m;

LL cnt(LL x) {
    LL ret = 0;
    for(int i = 1; i <= n; ++i) {
        LL l = 1, r = n + 1;
        while(l < r) {
            LL mid = (l + r) >> 1;
            if(calc(mid, i) >= x) r = mid;
            else l = mid + 1;
        }
        ret += l - 1;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin>>T;
    while(T--) {
        cin>>n>>m;
        LL l = -1e12, r = 1e12;
        while(l < r) {
            LL mid = (l + r) >> 1;
            if(cnt(mid) >= m) r = mid;
            else l = mid + 1;
        }
        cout<<l - 1<<endl;
    }
}
