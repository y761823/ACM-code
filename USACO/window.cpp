/*
ID: y7618231
PROG: window
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <numeric>
#include <set>
#include <deque>
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 5010;
const int seed = 313;
const int MOD = 1000000007;

struct Window {
    char id;
    int x1, y1, x2, y2;
    Window() {
        scanf("(%c,%d,%d,%d,%d)", &id, &x1, &y1, &x2, &y2);
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
    }
    Window(char id): id(id) {}
    bool operator == (const Window& rhs) const {
        return id == rhs.id;
    }
};

deque<Window> list;

int dfs(int x1, int x2, int y1, int y2, deque<Window>::iterator it) {
    while(it != list.end() && (it->x2 <= x1 || x2 <= it->x1 || it->y2 <= y1 || y2 <= it->y1)) ++it;
    if(it == list.end()) return (x2 - x1) * (y2 - y1);
    int res = 0;
    auto nxt = it; ++nxt;
    if(x1 < it->x1) { res += dfs(x1, it->x1, y1, y2, nxt); x1 = it->x1; }
    if(it->x2 < x2) { res += dfs(it->x2, x2, y1, y2, nxt); x2 = it->x2; }
    if(y1 < it->y1) { res += dfs(x1, x2, y1, it->y1, nxt); y1 = it->y1; }
    if(it->y2 < y2) { res += dfs(x1, x2, it->y2, y2, nxt); y2 = it->y2; }
    return res;
}

double solve(char id) {
    auto it = find(list.begin(), list.end(), Window(id));
    auto t = it;
    return dfs(it->x1, it->x2, it->y1, it->y2, ++t) / double((it->x2 - it->x1) * (it->y2 - it->y1));
}

Window erase() {
    char id;
    scanf("(%c)", &id);
    auto it = find(list.begin(), list.end(), Window(id));
    Window res = *it;
    list.erase(it);
    return res;
}

int main() {
#ifndef OYK_JUDGE
    freopen("window.in", "r", stdin); freopen("window.out", "w", stdout);
#endif // OYK_JUDGE
    char c, id;
    while(scanf(" %c", &c) != EOF) {
        if(c == 'w') {
            list.push_back(Window());
        } else if(c == 't') {
            list.push_back(erase());
        } else if(c == 'b') {
            list.push_front(erase());
        } else if(c == 'd') {
            erase();
        } else if(c == 's') {
            scanf("(%c)", &id);
            printf("%.3f\n", solve(id) * 100);
        }
    }
}
