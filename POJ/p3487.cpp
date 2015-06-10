#include <cstdio>
#include <queue>
#include <cstring>
#include <map>
using namespace std;

const int MAXN = 100;

int pref[MAXN][MAXN], order[MAXN][MAXN], next[MAXN];
int future_husband[MAXN], future_wife[MAXN];
queue<int> que;
map<char, int> mp;

void engage(int man, int woman){
    int &m = future_husband[woman];
    if(m){
        future_wife[m] = 0;
        que.push(m);
    }
    future_husband[woman] = man;
    future_wife[man] = woman;
}

int n, T;

void GaleShapley(){
    while(!que.empty()){
        int man = que.front(); que.pop();
        int woman = pref[man][next[man]++];
        if(!future_husband[woman] || order[woman][man] < order[woman][future_husband[woman]])
            engage(man, woman);
        else que.push(man);
    }
    for(char c = 'a'; c <= 'z'; ++c) if(mp[c])
        printf("%c %c\n", c, future_wife[mp[c]] + 'A' - 1);
}

int main(){
    char s[MAXN], c[2];
    scanf("%d", &T);
    while(T--){
        if(!que.empty()) que.pop();
        mp.clear();
        memset(pref,0,sizeof(pref));
        memset(order,0,sizeof(order));
        memset(future_husband,0,sizeof(future_husband));
        memset(future_wife,0,sizeof(future_wife));
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%s", c), mp[c[0]] = i;
        for(int i = 1; i <= n; ++i) scanf("%s", c), mp[c[0]] = i;
        for(int i = 0; i < n; ++i){
            scanf("%s", s);
            for(int j = 2; s[j]; ++j) pref[mp[s[0]]][j-1] = mp[s[j]];
            next[mp[s[0]]] = 1;
            que.push(mp[s[0]]);
        }
        for(int i = 0; i < n; ++i){
            scanf("%s", s);
            for(int j = 2; s[j]; ++j) order[mp[s[0]]][mp[s[j]]] = j-1;
        }
/*
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) printf("%d ", pref[i][j]);
            printf("\n");
        }*/
        GaleShapley();
        if(T) printf("\n");
    }
}
