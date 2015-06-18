//only C++ can get Accept
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
using namespace std;
#define forall(i, v) for(__typeof(v.begin()) i = v.begin(); i != v.end(); ++i)

const int MAXN = 500010;

map<string, int> mymap, id;
char s1[11], s2[11];
int fa[MAXN], n;

int find_set(int x) {
    return !fa[x] ? x : fa[x] = find_set(fa[x]);
}
void merge(int a, int b) {
    a = find_set(a), b = find_set(b);
    if(a != b) fa[a] = b;
}

bool check1() {
    int one = 0;
    for(map<string, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
        one += (it->second & 1);
    return one <= 2;
}
bool check2() {
    for(int i = 1; i <= n; ++i)
        if(find_set(1) != find_set(i)) return false;
    return true;
}

int main() {
    while(scanf("%s%s", s1, s2) != EOF) {
        if(++mymap[s1] == 1) id[s1] = ++n;
        if(++mymap[s2] == 1) id[s2] = ++n;
        merge(id[s1], id[s2]);
    }
    puts(check1() && check2() ? "Possible" : "Impossible");
}
