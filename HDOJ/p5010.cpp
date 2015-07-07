////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-10-14 16:07:43
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5010
////Problem Title: 
////Run result: Accept
////Run time:796MS
////Run memory:5056KB
//////////////////System Comment End//////////////////
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef unsigned long long ULL;

const int MOD = 1000007;

struct hashmap {
    int head[MOD];
    vector<ULL> to;
    vector<int> next;

    void clear() {
        memset(head, -1, sizeof(head));
        to.clear();
        next.clear();
    }

    void insert(ULL val) {
        int h = val % MOD;
        to.push_back(val); next.push_back(head[h]); head[h] = to.size() - 1;
    }

    bool find(ULL val) {
        int h = val % MOD;
        for(int p = head[h]; ~p; p = next[p])
            if(to[p] == val) return true;
        return false;
    }
} hash;

//debug
void print(char mat[8][10]) {
    puts("#debug");
    for(int i = 0; i <= 7; ++i) {
        for(int j = 0; j <= 9; ++j) putchar(mat[i][j]);
        puts("");
    }
}

const int M = 1;
const int S = 2;
const int P = 3;

char chr(int v) {
    if(v == M) return 'M';
    if(v == S) return 'S';
    if(v == P) return 'P';
    return '.';
}

int fight(char c) {
    if(c == 'P') return 5;
    if(c == 'S' || c == 'M') return 3;
    if(c == 'N') return 1;
    return 0;
}

const int MAXN = 6 + 2;
const int MAXM = 8 + 2;

int fx[] = {0, 1, 0, -1};
int fy[] = {1, 0, -1, 0};

char src[MAXN][MAXM];
char mat[MAXN][MAXM], tmp[MAXN][MAXM];
int pid[MAXN][MAXM], pcnt;
int px[55], py[55];
int n = 6, m = 8;

void set_state(ULL &st, int i, ULL v) {
    st &= ~(ULL(3) << (i << 1));
    st |= (v << (i << 1));
}

int get_state(ULL st, int i) {
    return st >> (i << 1) & 3;
}

ULL get_state(char a[MAXN][MAXM]) {
    ULL res = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(a[i][j] == 'M') set_state(res, pid[i][j], M);
            if(a[i][j] == 'S') set_state(res, pid[i][j], S);
            if(a[i][j] == 'P') set_state(res, pid[i][j], P);
        }
    }
    return res;
}

void set_state(char a[MAXN][MAXM], ULL st) {
    memcpy(a, mat, sizeof(mat));
    for(int i = 0; i < pcnt; ++i) {
        int v = get_state(st, i);
        if(v != 0) a[px[i]][py[i]] = chr(v);
    }
}

ULL run(ULL st, int pos, int f) {
    int mt = get_state(st, pos);
    set_state(st, pos, 0);
    set_state(tmp, st);

    bool eaten = false, eat = false;
    int r = px[pos], c = py[pos];
    while(true) {
        int nr = r + fx[f], nc = c + fy[f];
        if(tmp[nr][nc] != '.') break;
        r = nr, c = nc;

        for(int i = 0; i < 4; ++i) {
            char e = tmp[r + fx[i]][c + fy[i]];
            if(e == '#' || e == '.') continue;
            int flag = fight(e) - fight(chr(mt));
            if(flag > 0) {
                if(mt == S) return 0;
                eaten = true;
            }
        }
        if(eaten) break;

        for(int i = 0; i < 4; ++i) {
            char e = tmp[r + fx[i]][c + fy[i]];
            if(e == '#' || e == '.') continue;
            int flag = fight(e) - fight(chr(mt));
            if(flag < 0) {
                if(tmp[r + fx[i]][c + fy[i]] == 'N') return mt == S;
                eat = true;
                set_state(st, pid[r + fx[i]][c + fy[i]], 0);
            }
        }
        if(eat) break;
    }
    if(!eaten) set_state(st, pid[r][c], mt);
    return st;
}

int solve() {
    ULL st = get_state(src);
    //set_state(tmp, st); print(tmp);
    queue<pair<ULL, int> > que; que.push(make_pair(st, 0));
    hash.clear(); hash.insert(st);
    while(!que.empty()) {
        pair<ULL, int> u = que.front(); que.pop();
        for(int i = 0; i < pcnt; ++i) {
            int t = get_state(u.first, i);
            if(t == 0) continue;
            for(int f = 0; f < 4; ++f) {
                ULL r = run(u.first, i, f);
                if(r == u.first) continue;
                //set_state(tmp, u.first); print(tmp); set_state(tmp, r); print(tmp); printf("%d %d %d\n", px[i], py[i], r); system("pause");
                if(r == 1)
                    return u.second + 1;
                if(r != 0 && !hash.find(r)) {
                    hash.insert(r);
                    que.push(make_pair(r, u.second + 1));
                }
            }
        }
    }
    return -1;
}

int main() {
    while(true) {
        memset(src, 0, sizeof(src));
        if(scanf("%s", &src[1][1]) == EOF) break;
        for(int i = 2; i <= n; ++i) scanf("%s", &src[i][1]);

        memset(mat, '#', sizeof(mat));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) mat[i][j] = (src[i][j] == '#' ? '#' : '.');
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) if(src[i][j] == 'N') mat[i][j] = 'N';

        pcnt = 0;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(mat[i][j] != '.') continue;
                px[pcnt] = i, py[pcnt] = j;
                pid[i][j] = pcnt++;
            }
        }
        //printf("%d\n", pcnt);
        //print(mat);

        printf("%d\n", solve());
    }
}
