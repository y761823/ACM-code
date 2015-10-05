#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

stack<int> stk[3];

string op[6];

int solve(int n) {
    for(int i = 0; i < 3; ++i) while(!stk[i].empty()) stk[i].pop();
    for(int i = n; i > 0; --i) stk[0].push(i);

    int cnt = 0, last = -1;
    while(int(stk[2].size()) != n && int(stk[1].size()) != n) {
        for(int i = 0; i < 6; ++i) {
            int u = op[i][0] - 'A', v = op[i][1] - 'A';
            if(stk[u].empty() || u == last) continue;
            if(stk[v].empty() || stk[u].top() < stk[v].top()) {
                stk[v].push(stk[u].top()); stk[u].pop();
                last = v;
                break;
            }
        }
        cnt++;
    }
    return cnt;
}

LL power(LL x, int p) {
    LL res = 1;
    while(p--) res *= x;
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < 6; ++i) cin>>op[i];
    if(n <= 3) printf("%d\n", solve(n));
    else {
        int a = solve(2), b = solve(3);
        if(a == 3 && b == 7) cout<<power(2, n) - 1<<endl;
        if(a == 3 && b == 9) cout<<power(3, n - 1)<<endl;
        if(a == 5 && b == 17) cout<<2 * power(3, n - 1) - 1<<endl;
    }
}
