////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-07-20 19:45:07
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4039
////Problem Title: 
////Run result: Accept
////Run time:625MS
////Run memory:532KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <string>
#include <set>
using namespace std;
typedef long long LL;

const int MAXV = 2010;
const int MAXE = 4010;

map<string, int> oyk;
string name[MAXV];
int head[MAXV], ecnt;
int to[MAXE], next[MAXE];
int n, m, q, T;

void init() {
    memset(head, -1, 2 * m * sizeof(int));
    oyk.clear();
    ecnt = n = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

set<string> ans;
int cnt[MAXV], c;

void dfs1(int u) {
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        c = max(c, cnt[v] += (cnt[v] != -1));
    }
}

void dfs2(int u) {
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        if(cnt[v] == c) ans.insert(name[v]);
        cnt[v] = -1;
    }
}

void solve(int u) {
    memset(cnt, 0, n * sizeof(int));
    cnt[u] = -1;
    for(int p = head[u]; ~p; p = next[p])
        cnt[to[p]] = -1;
    c = 0;
    for(int p = head[u]; ~p; p = next[p])
        dfs1(to[p]);
    if(c > 0) {
        ans.clear();
        for(int p = head[u]; ~p; p = next[p])
            dfs2(to[p]);
        for(set<string>::iterator it = ans.begin(); it != ans.end(); ++it) {
            if(it == ans.begin()) cout<<*it;
            else cout<<" "<<*it;
        }
        cout<<endl;
    } else {
        cout<<"-"<<endl;
    }
}

string s1, s2;

int main() {
    ios::sync_with_stdio(false);
    cin>>T;
    for(int t = 1; t <= T; ++t) {
        cin>>m>>q;
        init();
        for(int i = 0; i < m; ++i) {
            cin>>s1>>s2;
            if(oyk.find(s1) == oyk.end()) { name[n] = s1; oyk[s1] = n++; }
            if(oyk.find(s2) == oyk.end()) { name[n] = s2; oyk[s2] = n++; }
            add_edge(oyk[s1], oyk[s2]);
        }
        cout<<"Case "<<t<<":"<<endl;
        for(int i = 0; i < q; ++i) {
            cin>>s1;
            solve(oyk[s1]);
        }
    }
}