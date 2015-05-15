/*
ID: y7618231
PROG: cryptcow
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 77;
const int seed = 131;
const int MOD = 1000007;

char s[] = "COW";
char tar[MAXN] = "Begin the Escape execution at the Break of Dawn";
int ltar = strlen(tar), tarhash;

char src[MAXN];
int lsrc;
int maxdep, ans;
bool hashmap[MOD];

void move(char s[], char t[], int c, int o, int w) {
    int v = 0;
    for(int i = 0; i < c; ++i) t[v++] = s[i];
    for(int i = o + 1; i < w; ++i) t[v++] = s[i];
    for(int i = c + 1; i < o; ++i) t[v++] = s[i];
    for(int i = w + 1; s[i]; ++i) t[v++] = s[i];
    t[v] = 0;
    assert(strlen(s) - 3 == strlen(t));
}

int get_hash(char *s) {
    LL res = 0;
    while(*s) res = (res * seed + *s++) % MOD;
    return (int)res;
}

bool shouldCut(char *s, int len) {
    for(int i = 0; s[i] != 'C'; ++i) if(s[i] != tar[i]) return true;
    for(int i = len - 1, j = ltar - 1; s[i] != 'W'; --i, --j) if(j < 0 || s[i] != tar[j]) return true;
    static char tmp[MAXN];
    int i = 0;
    while(i < len) {
        int k = 0;
        while(i < len && strchr("COW", s[i]) == NULL) tmp[k++] = s[i++];
        tmp[k] = 0;
        if(strstr(tar, tmp) == NULL) return true;
        i++;
    }
    return false;
}

char tmp[10][MAXN];
bool dfs(char *s, int dep) {
    int hash = get_hash(s);
    if(hashmap[hash]) return false;
    hashmap[hash] = true;
    if(dep == maxdep && hash == tarhash) return true;

    int len = strlen(s);
    if(shouldCut(s, len)) return false;

    for(int o = 0; o < len; ++o) if(s[o] == 'O') {
        for(int c = 0; c < o; ++c) if(s[c] == 'C') {
            for(int w = len - 1; w > o; --w) if(s[w] == 'W') {
                move(s, tmp[dep], c, o, w);
                if(dfs(tmp[dep], dep + 1)) return true;
            }
        }
    }
    return false;
}

bool prejudge() {
    if(ltar > lsrc) return false;
    if((lsrc - ltar) % 3 != 0) return false;
    maxdep = (lsrc - ltar) / 3;
    if(count(src, src + lsrc, 'C') != maxdep) return false;
    if(count(src, src + lsrc, 'O') != maxdep) return false;
    if(count(src, src + lsrc, 'W') != maxdep) return false;
    for(int i = 0; i < ltar; ++i)
        if(count(src, src + lsrc, tar[i]) != count(tar, tar + ltar, tar[i])) return false;
    for(int i = 0; i < lsrc; ++i) if(strchr("COW", src[i]) == NULL)
        if(count(src, src + lsrc, src[i]) != count(tar, tar + ltar, src[i])) return false;
    return true;
}

int main() {
#ifndef OYK_JUDGE
    freopen("cryptcow.in", "r", stdin); freopen("cryptcow.out", "w", stdout);
#endif // OYK_JUDGE
    gets(src);
    lsrc = strlen(src);
    tarhash = get_hash(tar);
    if(prejudge() && dfs(src, 0)) printf("1 %d\n", maxdep);
    else puts("0 0");
}
