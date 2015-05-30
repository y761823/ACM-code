#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
#include <functional>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
typedef long long LL;

const int MAXN = 10010;
const int INF = 0x3f3f3f3f;

__gnu_pbds::tree<int, __gnu_pbds::null_type, less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> bbt;
queue<int> que;
int T, n;

int main() {
    int kase = 0;
    while(scanf("%d", &n) != EOF) {
        printf("Case #%d:\n", ++kase);
        while(!que.empty()) que.pop();
        bbt.clear();

        char op[5];
        for(int i = 0, x; i < n; ++i) {
            scanf("%s", op);
            if(strcmp(op, "in") == 0) {
                scanf("%d", &x);
                que.push(x);
                bbt.insert(x);
            }
            if(strcmp(op, "query") == 0) {
                printf("%d\n", *bbt.find_by_order(bbt.size() / 2));
            }
            if(strcmp(op, "out") == 0) {
                bbt.erase(que.front());
                que.pop();
            }
        }
    }
}
