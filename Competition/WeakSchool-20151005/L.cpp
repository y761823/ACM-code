#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

const int MAXN = 5010;
const int MAXS = 32;
const int MAXV = MAXN * MAXS;
const int seed = 30011;
const int MOD = 1e9 + 7;

struct Node {
    Node *go[26];
    int size, hash, goal, dep;
} statePool[MAXV], *root;
int h[26];
int ncnt, n;

Node* new_node() {
    Node* x = statePool + ncnt++;
    x->hash = 1009;
    x->goal = 13001;
    return x;
}

char s[MAXS];
void insert(char s[]) {
    Node *p = root;
    for(int i = 0; s[i]; ++i) {
        int idx = s[i] - 'a';
        if(!p->go[idx]) p->go[idx] = new_node();
        p = p->go[idx];
    }
    p->goal = 4111;
}

set<pair<int, int> > hashset;
void dfs(Node *x) {
    x->size = 1;
    for(int i = 0; i < 26; ++i) if(x->go[i]) {
        dfs(x->go[i]);
        x->dep = max(x->dep, x->go[i]->dep);
        x->hash = (((LL)x->hash * seed) ^ ((LL)h[i] * x->go[i]->hash)) % MOD;
        if(hashset.find(make_pair(x->go[i]->dep, x->go[i]->hash)) == hashset.end()) {
            x->size += x->go[i]->size;
            hashset.insert(make_pair(x->go[i]->dep, x->go[i]->hash));
        }
    }
    x->dep++;
    x->hash = (LL)x->hash * x->goal % MOD;
}

int main() {
    for(int i = 0; i < 26; ++i) h[i] = rand() % 10333;
    scanf("%d", &n);
    root = new_node();
    for(int i = 0; i < n; ++i) {
        scanf("%s", s);
        insert(s);
    }
    dfs(root);
    printf("%d\n", root->size);
}
