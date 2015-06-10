#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 8;
const int INF = 0x3f3f3f3f;

int fx[] = {-1, -2, -3, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0};
int fy[] = {0, 0, 0, 1, 2, 3, 0, 0, 0, -1, -2, -3, 0};
char mat[MAXN][MAXN];
vector<pair<int, int> > tmp, ans;

void _flip(int x, int y) {
    static char t = '+' ^ '-';
    if(1 <= x && x <= 4 && 1 <= y && y <= 4)
        mat[x][y] ^= t;
}
void flip(int x, int y) {
    for(int i = 0; i < 13; ++i)
        _flip(x + fx[i], y + fy[i]);
}

void dfs(int dep) {
    if(dep == 16) {
        for(int i = 1; i <= 4; ++i)
            for(int j = 1; j <= 4; ++j)
                if(mat[i][j] != '-') return ;
        if(!ans.size() || tmp.size() < ans.size())
            ans = tmp;
    } else {
        int x = dep / 4 + 1, y = dep % 4 + 1;
        dfs(dep + 1);
        flip(x, y); tmp.push_back(make_pair(x, y));
        dfs(dep + 1);
        flip(x, y); tmp.pop_back();
    }
}

int main() {
    for(int i = 1; i <= 4; ++i) scanf("%s", mat[i] + 1);
    dfs(0);
    printf("%u\n", ans.size());
    for(vector<pair<int, int> >::iterator it = ans.begin(); it != ans.end(); ++it)
        printf("%d %d\n", it->first, it->second);
}
