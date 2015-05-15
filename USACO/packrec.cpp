/*
ID: y7618231
PROG: packrec
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
#include <cctype>
#include <vector>
using namespace std;

typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 40010;
const int INF = 0x3f3f3f3f;

pair<int, int> p[4];
int list[4];
int n = 4;

vector<pair<int, int>> ans;
int minans = INF;

void update(int a, int b) {
    int area = a * b;
    if(area < minans) minans = area, ans.clear();
    if(area == minans) ans.push_back(make_pair(a, b));
}

#define A(i) p[list[i]].first
#define B(i) p[list[i]].second
void calc1() {
    int a = 0, b = 0;
    for(int i = 0; i < 4; ++i)
        a += A(i), b = max(b, B(i));
    update(a, b);
}

void calc2() {
    int a = max(A(0) + A(1) + A(2), A(3));
    int b = max(B(0), max(B(1), B(2))) + B(3);
    update(a, b);
}

void calc3() {
    int a = max(A(0) + A(1), A(3)) + A(2);
    int b = max(B(2), B(3) + max(B(0), B(1)));
    update(a, b);
}

void calc5() {
    int a = max(A(0), A(1)) + A(2) + A(3);
    int b = max(B(0) + B(1), max(B(2), B(3)));
    update(a, b);
}

void calc6() {
    int a = max(A(0), A(3)) + max(A(1), A(2));
    if(B(3) >= B(2) && (A(0) > A(3) || A(2) > A(1))) a = min(a, max(A(0) + A(1), A(2) + A(3)));
    int b = max(B(0) + B(3), B(1) + B(2));
    update(a, b);

    //for(int i = 0; i < 4; ++i) printf("%d %d\n", A(i), B(i));
}

void print() {
    for(auto &p : ans) if(p.first > p.second) swap(p.first, p.second);
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    printf("%d\n", minans);
    for(auto &p : ans)
        printf("%d %d\n", p.first, p.second);
}

int debug[] = {0, 3, 1, 2};

void solve() {
    iota(list, list + 4, 0);
    //memcpy(list, debug, sizeof(debug));
    do {
        for(int st = 0; st < (1 << 4); ++st) {
            for(int i = 0; i < 4; ++i) if((st >> i) & 1) swap(p[i].first, p[i].second);
            calc1();
            calc2();
            calc3();
            calc5();
            calc6();
            for(int i = 0; i < 4; ++i) if((st >> i) & 1) swap(p[i].first, p[i].second);
        }
    } while(next_permutation(list, list + 4));
}

int main() {
#ifndef OYK_JUDGE
    freopen("packrec.in", "r", stdin); freopen("packrec.out", "w", stdout);
#endif // OYK_JUDGE
    for(int i = 0; i < n; ++i)
        scanf("%d%d", &p[i].first, &p[i].second);
    solve();
    print();
}
