#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

priority_queue<int> que;
int n;

int main() {
    scanf("%d", &n);
    for(int i = 0, x; i < n; ++i) {
        scanf("%d", &x);
        que.push(-x);
    }
    LL res = 0;
    for(int i = 1; i < n; ++i) {
        int x = -que.top(); que.pop();
        x += -que.top(); que.pop();
        res += x;
        que.push(-x);
    }
    cout<<res<<endl;
}
