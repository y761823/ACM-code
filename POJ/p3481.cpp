#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

struct Node {
    int key, id;
    bool operator < (const Node &rhs) const {
        return key < rhs.key;
    }
};

map<int, int> mymap;

int main() {
    int t, k, p;
    while(scanf("%d", &t) != EOF && t) {
        if(t == 1) {
            scanf("%d%d", &k, &p);
            mymap[p] = k;
        } else if(mymap.empty()) {
            puts("0");
        } else if(t == 2) {
            map<int, int>::iterator it = mymap.end();
            --it;
            printf("%d\n", it->second);
            mymap.erase(it);
        } else {
            map<int, int>::iterator it = mymap.begin();
            printf("%d\n", it->second);
            mymap.erase(it);
        }
    }
}
