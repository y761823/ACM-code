#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; ++i)

int n, A, B;

int main() {
    vector<pair<int, int> > ans;
    scanf("%d%d%d", &n, &A, &B);
    for(int i = 0; i < n; ++i)
        ans.push_back(make_pair((A * i) % n, (B * i) % n));
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    printf("%d\n", ans.size());
    for(vector<pair<int, int> >::iterator it = ans.begin(); it != ans.end(); ++it)
        printf("%d %d\n", it->first, it->second);
}
