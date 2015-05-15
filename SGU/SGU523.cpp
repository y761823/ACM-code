#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 105;

int n, m, f;
bool light[MAXN];
int order[MAXN];

int main() {
    scanf("%d%d", &n, &f);
    for(int i = 1; i <= n; ++i) scanf("%d", &order[i]);
    for(int i = 1; i <= n; ++i) light[order[i]] = true;
    bool flag = false;
    int cur = 0;
    while(++cur <= n) {
        if(!light[order[cur]]) continue;
        int to = order[cur] > f ? 1 : -1;
        while(f != order[cur]) {
            f += to;
            if(light[f]) {
                if(flag) printf(" ");
                else flag = true;
                printf("%d", f);
                light[f] = false;
            }
        }
        if(light[f]) {
            if(flag) printf(" ");
            else flag = true;
            printf("%d", f);
            light[f] = false;
        }
    }
    printf("\n");
}
