#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

const int MAXV = 1000010;

vector<int> sons[MAXV];
int m[MAXV], l[MAXV];
int size[MAXV], cnt[MAXV];
int n;

bool cmp_size(int x, int y) {
    return size[x] < size[y];
}

void bfs_size() {
    queue<int> que;
    for(int i = 0; i < n; ++i)
        if(!cnt[i]) que.push(i);
    while(!que.empty()) {
        int u = que.front(); que.pop();
        size[u] = m[u];
        foreach(v, sons[u])
            size[u] += size[*v];
        if(--cnt[l[u]] == 0) que.push(l[u]);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d%d", &m[i], &l[i]);
        if(~l[i]) sons[l[i]].push_back(i), cnt[l[i]]++;
    }
    bfs_size();

    LL res = 0;
    for(int u = 0; u < n; ++u) {
        sort(sons[u].begin(), sons[u].end(), cmp_size);
        LL sum = 0;
        foreach(v, sons[u]) {
            res += sum;
            sum += size[*v];
        }
    }
    cout<<res<<endl;
}
