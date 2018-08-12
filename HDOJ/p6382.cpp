#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

typedef long long LL;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;
const int SUMV = 2e5;
const int MOD = 1e9 + 7;

int inv(int a) {
    if (a == 1) return 1;
    return (LL(MOD - MOD / a) * inv(MOD % a)) % MOD;
}

int mul_mod(int a, int b) {
    return (LL)a * b % MOD;
}

int mul_mod(int a, int b, int c) { // a * b / c
    int res = mul_mod(a, b);
    return mul_mod(res, c);
}

struct Value {
    int a, b; // a / b
    int toInt() const {
        return mul_mod(a, inv(b));
    }
    bool operator < (const Value& rhs) const {
        return (LL)a * rhs.b < (LL)b * rhs.a;
    }
    bool operator > (const Value& rhs) const {
        return (LL)a * rhs.b > (LL)b * rhs.a;
    }
};

struct KSet {
    std::multiset<Value> maxk, other;
    size_t k;
    void init(int _k) {
        maxk.clear();
        other.clear();
        k = _k;
    }
    Value getMink() {
        return *maxk.begin();
    }
    void insert(Value v) {
        maxk.insert(v);
        if (maxk.size() > k) {
            auto it = maxk.begin();
            other.insert(*it);
            maxk.erase(it);
        }
    }
    void erase(Value v) {
        auto it = other.find(v);
        if (it != other.end()) {
            other.erase(it);
            return ;
        }
        maxk.erase(maxk.find(v));
        if (!other.empty()) {
            Value t = *other.rbegin();
            maxk.insert(t);
            other.erase(--other.end());
        }
    }
} values;

std::vector<std::pair<int, int>> sons[MAXN];
int result[MAXN];
int n, m, T;

void dfs(int u, int rest, int res) {
    if (sons[u].size()) {
        int maxv = 0;
        for (auto p : sons[u]) {
            if (p.second > maxv)
                maxv = p.second;
        }
        for (auto p : sons[u]) {
            int v = p.first;
            if (rest > 0) {
                values.insert(Value{maxv, p.second});
                dfs(v, rest - 1, mul_mod(res, maxv, inv(SUMV)));
                values.erase(Value{maxv, p.second});
            } else {
                Value it = values.getMink();
                //printf("%d %d %u\n", it->a, it->b, values.size());
                bool bLess = it < Value{maxv, p.second};
                int temp = bLess ? mul_mod(res, inv(it.toInt()), mul_mod(maxv, inv(SUMV))) : mul_mod(res, p.second, inv(SUMV));

                values.insert(Value{maxv, p.second});
                dfs(v, 0, temp);
                values.erase(Value{maxv, p.second});
            }
        }
    } else {
        result[u] = res;
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i)
            sons[i].clear();
        for (int i = 1, a, b, c; i < n; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            sons[a].push_back(std::make_pair(b, c));
        }
        memset(result, 0, n * sizeof(int));
        values.init(m);
        dfs(0, m, 1);
        for (int i = 0; i < n; ++i)
            if (sons[i].empty())
                printf("%d\n", result[i]);
    }
}
