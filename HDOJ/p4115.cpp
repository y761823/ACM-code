////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-07-09 10:42:56
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4115
////Problem Title: 
////Run result: Accept
////Run time:93MS
////Run memory:1444KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>

const int MAXN = 10010*6;
const int MAXM = 20*10010;
const int WE = 6;

struct TwoSAT{
    int n, ecnt, dfs_clock, scc_cnt;
    int St[MAXN], c;
    int head[MAXN], sccno[MAXN], pre[MAXN], lowlink[MAXN];
    int next[MAXM], to[MAXM];

    void init(int nn){
        n = nn;
        ecnt = 2; dfs_clock = scc_cnt = 0;
        memset(head,0,sizeof(head));
        memset(sccno,0,sizeof(sccno));
        memset(pre,0,sizeof(pre));
    }

    void addEdge(int x, int y){
        to[ecnt] = y; next[ecnt] = head[x]; head[x] = ecnt++;
        //printf("%d->%d\n",x,y);
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

    void test(){
        for(int i = 0; i < n; ++i){
            printf("%d\n",i+1);
            for(int p = head[i]; p; p = next[p]) printf("%d ", to[p]+1);
        }
    }

} G;

int B[MAXN];

int main(){
    int T, n, m, a, b, k;
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t){
        scanf("%d%d",&n,&m);
        G.init(n*WE);
        for(int i = 0; i < n; ++i){
            scanf("%d", &b);
            if(b == 1) {
                //G.addEdge(i*WE+2*2, i*WE+2*2+1);
                G.addEdge(i*WE+1*2+1, i*WE+0*2);
                G.addEdge(i*WE+0*2+1, i*WE+1*2);
            }
            if(b == 2) {
                //G.addEdge(i*WE+0*2, i*WE+0*2+1);
                G.addEdge(i*WE+1*2+1, i*WE+2*2);
                G.addEdge(i*WE+2*2+1, i*WE+1*2);
            }
            if(b == 3) {
                //G.addEdge(i*WE+1*2, i*WE+1*2+1);
                G.addEdge(i*WE+0*2+1, i*WE+2*2);
                G.addEdge(i*WE+2*2+1, i*WE+0*2);
            }
        }
        while(m--){
            scanf("%d%d%d", &a, &b, &k);
            --a, --b;
            if(k == 0){
                for(int i = 0; i < 3; ++i) {
                    G.addEdge2(a*WE+i*2, b*WE+i*2);
                    G.addEdge2(a*WE+i*2+1, b*WE+i*2+1);
                }
            }else{
                for(int i = 0; i < 3; ++i){
                    G.addEdge(a*WE+i*2, b*WE+i*2+1);
                    G.addEdge(b*WE+i*2, a*WE+i*2+1);
                }
            }
        }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < 3; ++j)
                for(int k = 0; k < 3; ++k) if(j != k){
                    G.addEdge(i*WE+j*2, i*WE+k*2+1);
                }
        if(G.solve()) printf("Case #%d: yes\n", t);
        else printf("Case #%d: no\n", t);
    }
    return 0;
}
