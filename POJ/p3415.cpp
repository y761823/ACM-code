#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long LL;

const int MAXN = 200010;

char s[MAXN];
int sa[MAXN], rank[MAXN], height[MAXN], c[MAXN], tmp[MAXN];
int n, apart, k;

void makesa(int m) {
    memset(c, 0, m * sizeof(int));
    for(int i = 0; i < n; ++i) ++c[rank[i] = s[i]];
    for(int i = 1; i < m; ++i) c[i] += c[i - 1];
    for(int i = 0; i < n; ++i) sa[--c[rank[i]]] = i;
    for(int k = 1; k < n; k <<= 1) {
        for(int i = 0; i < n; ++i) {
            int j = sa[i] - k;
            if(j < 0) j += n;
            tmp[c[rank[j]]++] = j;
        }
        int j = c[0] = sa[tmp[0]] = 0;
        for(int i = 1; i < n; ++i) {
            if(rank[tmp[i]] != rank[tmp[i - 1]] || rank[tmp[i] + k] != rank[tmp[i - 1] + k])
                c[++j] = i;
            sa[tmp[i]] = j;
        }
        memcpy(rank, sa, n * sizeof(int));
        memcpy(sa, tmp, n * sizeof(int));
    }
}

void calheight() {
    for(int i = 0, k = 0; i < n; height[rank[i++]] = k) {
        k -= (k > 0);
        int j = sa[rank[i] - 1];
        while(s[i + k] == s[j + k]) ++k;
    }
}

struct Node {
    int height, cnt;
    Node(int height = 0, int cnt = 0): height(height), cnt(cnt) {}
};

LL solve() {
    LL ans = 0, sum = 0;
    stack<Node> stk;

    for(int i = 1; i < n; ++i) {
        int cnt = 0;
        while(!stk.empty() && stk.top().height >= height[i]) {
            Node t = stk.top(); stk.pop();
            cnt += t.cnt;
            sum -= t.cnt * (t.height - k + 1LL);
        }
        if(height[i] >= k) {
            cnt += (sa[i - 1] < apart);
            if(cnt) stk.push(Node(height[i], cnt));
            sum += cnt * (height[i] - k + 1LL);
        }
        if(sa[i] > apart) ans += sum;
    }

    while(!stk.empty()) stk.pop();
    sum = 0;

    for(int i = 1; i < n; ++i) {
        int cnt = 0;
        while(!stk.empty() && stk.top().height >= height[i]) {
            Node t = stk.top(); stk.pop();
            cnt += t.cnt;
            sum -= t.cnt * (t.height - k + 1LL);
        }
        if(height[i] >= k) {
            cnt += (sa[i - 1] > apart);
            stk.push(Node(height[i], cnt));
            sum += cnt * (height[i] - k + 1LL);
        }
        if(sa[i] < apart) ans += sum;
    }

    return ans;
}

int main() {
    while(scanf("%d", &k) != EOF && k) {
        scanf("%s", s);
        apart = strlen(s);
        s[apart] = '$';
        scanf("%s", s + apart + 1);
        n = strlen(s) + 1;
        makesa(128);
        calheight();
        cout<<solve()<<endl;
    }
}
