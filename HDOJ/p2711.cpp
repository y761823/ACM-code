#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

const int MAXN = 8010;

__gnu_pbds::tree<int, __gnu_pbds::null_type, std::less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> tree;
int ans[MAXN], pre[MAXN];
int n;

int main() {
    while(scanf("%d", &n) != EOF) {
        for(int i = 2; i <= n; ++i) scanf("%d", &pre[i]);
        tree.clear();
        for(int i = 1; i <= n; ++i)
            tree.insert(i);
        for(int i = n; i > 0; --i) {
            int t = *tree.find_by_order(pre[i]);
            ans[i] = t;
            tree.erase(t);
        }
        for(int i = 1; i <= n; ++i)
            printf("%d\n", ans[i]);
    }
}
