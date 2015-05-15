#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define FOR(i, n) for(int i = 0; i < n; ++i)

const int MAXV = 11;

void read(vector<int> &vec) {
    int n, p;
    scanf("%d", &n);
    while(n--) scanf("%d", &p), vec.push_back(p);
}

void print(vector<int> &vec) {
    printf("%u", vec.size());
    for(size_t i = 0; i < vec.size(); ++i)
        printf(" %d", vec[i]);
    puts("");
}

bool exist(vector<int> &vec, int val) {
    return find(vec.begin(), vec.end(), val) != vec.end();
}

bool check(vector<int> &ask, vector<int> vec) {
    for(size_t i = 0; i < ask.size(); ++i)
        if(exist(vec, abs(ask[i])) != (ask[i] > 0)) return false;
    return true;
}

vector<int> seq[MAXV];
int n, m;

void query() {
    vector<int> ask, ans;
    read(ask);
    for(int i = 0; i < n; ++i)
        if(check(ask, seq[i])) ans.push_back(i);
    printf("%u\n", ans.size());
    for(size_t i = 0; i < ans.size(); ++i)
        print(seq[ans[i]]);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) read(seq[i]);
    while(m--) query();
}
