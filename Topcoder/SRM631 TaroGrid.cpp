#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
typedef long long LL;

class TaroGrid {
public:
    int getNumber(vector <string> grid) {
        int res = 0, n = grid.size();
        for(int c = 0; c < n; ++c) {
            int r = 0;
            while(r < n) {
                int t = r;
                while(t < n && grid[t][c] == grid[r][c]) t++;
                res = max(res, t - r);
                r = t;
            }
        }
        return res;
    }
};
