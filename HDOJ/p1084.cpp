////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-07 10:58:33
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1084
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:292KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Node {
    int t, id;
    bool operator < (const Node &rhs) const {
        return t < rhs.t;
    }
};

vector<Node> a[6];
vector<Node>::iterator it, mid;
Node t;
int ans[110];

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        if(n < 0) break;
        for(int i = 0; i <= 5; ++i) a[i].clear();
        for(int i = 0; i < n; ++i) {
            int x, aa, b, c;
            scanf("%d %d:%d:%d", &x, &aa, &b, &c);
            t.id = i;
            t.t = aa * 3600 + b * 60 + c;
            a[x].push_back(t);
        }
        for(int i = 0; i <= 5; ++i) sort(a[i].begin(), a[i].end());
        for(it = a[0].begin(); it != a[0].end(); ++it) ans[it->id] = 50;
        for(it = a[5].begin(); it != a[5].end(); ++it) ans[it->id] = 100;
        for(int i = 1; i <= 4; ++i) {
            if(a[i].size() == 1) {
                it = a[i].begin();
                ans[it->id] = i * 10 + 55;
                continue;
            }
            mid = a[i].begin() + a[i].size() / 2;
            //if(mid != a[i].end()) cout<<mid->id<<endl;
            for(it = a[i].begin(); it != a[i].end(); ++it) {
                if(it < mid) ans[it->id] = i * 10 + 55;
                else ans[it->id] = i * 10 + 50;
            }
        }
        for(int i = 0; i < n; ++i) printf("%d\n", ans[i]);
        puts("");
    }
}