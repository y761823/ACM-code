/*
ID: y7618231
PROG: humble
LANG: C++
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXK = 110;
const int MAXN = 100010;

struct Node {
    int p;
    set<int>::iterator it;
    Node() {}
    Node(int p, set<int>::iterator it): p(p), it(it) {}
    LL val() const {
        return (LL)p * *it;
    }
    bool operator < (const Node &rhs) const {
        return val() > rhs.val();
    }
};

priority_queue<Node> que;
set<int>::iterator idx[MAXK];
bool flag[MAXK];
int prime[MAXK];
int n, k;

void solve() {
    scanf("%d%d", &k, &n);
    for(int i = 0; i < k; ++i) scanf("%d", &prime[i]);
    set<int> st; st.insert(1);
    for(int i = 0; i < k; ++i)
        que.push(Node(prime[i], st.begin()));
    while((int)st.size() <= n) {
        Node a = que.top(); que.pop();
        st.insert(a.val());
        que.push(Node(a.p, ++a.it));
    }
    printf("%d\n", *st.rbegin());
}

int main() {
#ifndef OYK_JUDGE
    freopen("humble.in", "r", stdin); freopen("humble.out", "w", stdout);
#endif
    solve();
}
