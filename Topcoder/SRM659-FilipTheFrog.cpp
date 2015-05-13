#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
using namespace std;
typedef long long LL;

bool vis[55];

class FilipTheFrog {
public:
    int countReachableIslands(vector <int> positions, int L) {
        queue<int> que; que.push(0);
        memset(vis, 0, sizeof(vis)); vis[0] = true;
        int n = positions.size(), res = 0;

        while(!que.empty()) {
            int u = que.front(); que.pop();
            res++;
            for(int i = 0; i < n; ++i) if(!vis[i] && abs(positions[i] - positions[u]) <= L) {
                vis[i] = true;
                que.push(i);
            }
        }
        return res;
    }
};
