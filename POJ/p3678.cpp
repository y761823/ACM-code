#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 2010;
const int MAXM = 1000010*4;

struct TwoSAT{
    int n, ecnt, dfs_clock, scc_cnt;
    int St[MAXN], c;
    int head[MAXN], sccno[MAXN], lowlink[MAXN], pre[MAXN];
    int next[MAXM], to[MAXM];

    void init(int nn){
        n = nn;
        ecnt = 2; dfs_clock = scc_cnt = 0;
        memset(head,0,sizeof(head));
    }

    void addEdge(int x, int y){
        to[ecnt] = y; next[ecnt] = head[x]; head[x] = ecnt++;
    }

    void addEdge2(int x, int y){
        addEdge(x,y); addEdge(y,x);
    }

    void dfs(int u){
        lowlink[u] = pre[u] = ++dfs_clock;
        St[++c] = u;
        for(int p = head[u]; p; p = next[p]){
            int &v = to[p];
            if(!pre[v]){
                dfs(v);
                if(lowlink[u] > lowlink[v]) lowlink[u] = lowlink[v];
            }else if(!sccno[v]){
                if(lowlink[u] > pre[v]) lowlink[u] = pre[v];
            }
        }
        if(lowlink[u] == pre[u]){
            ++scc_cnt;
            while(true){
                int x = St[c--];
                sccno[x] = scc_cnt;
                if(x == u) break;
            }
        }
    }

    bool solve(){
        for(int i = 0; i < n; ++i)
            if(!pre[i]) dfs(i);
        for(int i = 0; i < n; i += 2)
            if(sccno[i] == sccno[i^1]) return false;
        return true;
    }

} G;

int main(){
    int n, m, a, b, c;
    char d[5];
    while(scanf("%d%d",&n,&m)!=EOF){
        G.init(2*n);
        while(m--){
            scanf("%d%d%d%s",&a,&b,&c,d);
            if(d[0] == 'A' && c == 0){//a&b=false
                G.addEdge(a*2, b*2+1);
                G.addEdge(b*2, a*2+1);
            }
            if(d[0] == 'A' && c == 1){//a&b=true
                //G.addEdge2(a*2, b*2);
                G.addEdge(a*2+1, a*2);
                G.addEdge(b*2+1, b*2);
            }
            if(d[0] == 'O' && c == 0){//a|b=false
                //G.addEdge2(a*2+1, b*2+1);
                G.addEdge(a*2, a*2+1);
                G.addEdge(b*2, b*2+1);
            }
            if(d[0] == 'O' && c == 1){//a|b=true
                G.addEdge(b*2+1, a*2);
                G.addEdge(a*2+1, b*2);
            }
            if(d[0] == 'X' && c == 0){//a^b=false
                G.addEdge2(a*2, b*2);
                G.addEdge2(a*2+1, b*2+1);
            }
            if(d[0] == 'X' && c == 1){//a^b=true
                G.addEdge2(a*2, b*2+1);
                G.addEdge2(a*2+1, b*2);
            }
        }
        if(G.solve()) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
