////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-14 18:37:01
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5012
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:400KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 6;
int n = 6;

namespace Solver {
    int ans[MAXN][MAXN][MAXN][MAXN][MAXN][MAXN];
    bool vis[MAXN][MAXN][MAXN][MAXN][MAXN][MAXN];

    //int left[] = {0, 1, 5, 4, 2, 3};
    //int right[] = {0, 1, 4, 5, 3, 2};
    int up[] = {5, 4, 2, 3, 0, 1};
    int down[] = {4, 5, 2, 3, 1, 0};
    int left[] = {3, 2, 0, 1, 4, 5};
    int right[] = {2, 3, 1, 0, 4, 5};

    void turn(int a[], int trans[]) {
        static int tmp[MAXN];
        for(int i = 0; i < n; ++i)
            tmp[trans[i]] = a[i];
        for(int i = 0; i < n; ++i)
            a[i] = tmp[i];
    }

    void get(int a[], int b[]) {
        for(int i = 0; i < n; ++i)
            b[i] = a[i];
    }

    #define pos(a) [a[0]][a[1]][a[2]][a[3]][a[4]][a[5]]

    struct Node {
        int a[MAXN];
        Node(int b[]) {
            for(int i = 0; i < n; ++i) a[i] = b[i];
        }
        bool operator < (const Node &rhs) const {
            for(int i = 0; i < n; ++i)
                if(a[i] != rhs.a[i]) return a[i] < rhs.a[i];
            return true;
        }
    };

    queue<Node> que;

    void push_back(int a[], int trans[]) {
        static int b[MAXN];
        get(a, b); turn(b, trans);
        if(!vis pos(b)) {
            vis pos(b) = true;
            ans pos(b) = ans pos(a) + 1;
            que.push(Node(b));
        }
    }

    void init() {
        int a[] = {0, 1, 2, 3, 4, 5};
        que.push(Node(a));
        ans pos(a) = 0;
        vis pos(a) = true;
        while(!que.empty()) {
            Node t = que.front(); que.pop();
            push_back(t.a, left);
            push_back(t.a, right);
            push_back(t.a, up);
            push_back(t.a, down);
        }
    }

    int get_ans(int a[], int b[]) {
        static int tmp[MAXN];
        for(int i = 0; i < n; ++i)
            --a[i], --b[i];
        for(int i = 0; i < n; ++i)
            tmp[a[i]] = i, a[i] = i;
        for(int i = 0; i < n; ++i)
            b[i] = tmp[b[i]];
        if(!vis pos(b)) return -1;
        return ans pos(b);
    }
};

int a[MAXN], b[MAXN];

int main() {
    Solver::init();
    while(scanf("%d", &a[0]) != EOF) {
        for(int i = 1; i < n; ++i) scanf("%d", &a[i]);
        for(int i = 0; i < n; ++i) scanf("%d", &b[i]);
        printf("%d\n", Solver::get_ans(a, b));
    }
}