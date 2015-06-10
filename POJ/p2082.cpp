#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

const int MAXN = 50010;

struct Rectangle {
    int w, h;
    void read() {
        scanf("%d%d", &w, &h);
    }
};

Rectangle a[MAXN], t;
int ans, n;

void solve() {
    ans = 0;
    int last = 0;
    stack<Rectangle> stk;
    for(int i = 0; i < n; ++i) {
        t.read();
        if(last < t.h) stk.push(t);
        else {
            int total = 0;
            while(!stk.empty() && stk.top().h > t.h) {
                total += stk.top().w;
                ans = max(ans, stk.top().h * total);
                stk.pop();
            }
            t.w += total;
            stk.push(t);
        }
        last = t.h;
    }
    int total = 0;
    while(!stk.empty()) {
        total += stk.top().w;
        ans = max(ans, stk.top().h * total);
        stk.pop();
    }
}

int main() {
    while(scanf("%d", &n) != EOF) {
        if(n == -1) break;
        solve();
        printf("%d\n", ans);
    }
}
