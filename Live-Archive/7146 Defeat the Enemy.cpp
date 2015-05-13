#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;

const int MAXN = 100010;

struct Node {
    int atk, def;
    void read() {
        scanf("%d%d", &atk, &def);
    }
};

Node a[MAXN], b[MAXN];
int n, m, T;

int solve() {
    multiset<int> st;
    int res = 0;
    for(int i = 0, j = 0; j < m; ++j) {
        while(i < n && a[i].atk >= b[j].def)
            st.insert(a[i++].def);
        if(st.empty()) return -1;
        auto it = st.upper_bound(b[j].atk);
        if(it != st.end()) st.erase(it);
        else st.erase(st.begin()), res++;
    }
    return n - res;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i) a[i].read();
        for(int i = 0; i < m; ++i) b[i].read();
        sort(a, a + n, [](Node x, Node y) {
            return x.atk > y.atk;
        });
        sort(b, b + m, [](Node x, Node y) {
            return x.def > y.def;
        });
        printf("Case #%d: %d\n", t, solve());
    }
}
