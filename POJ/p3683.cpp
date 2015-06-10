#include <cstdio>
#include <cstring>

const int MAXN = 1010*2;
const int MAXM = MAXN * MAXN * 4;

struct TwoSAT{
    int St[MAXN], c;
    int n, ecnt, dfs_clock, scc_cnt;
    int head[MAXN], sccno[MAXN], pre[MAXN], lowlink[MAXN];
    int next[MAXM], to[MAXM];

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

    void init(int nn){
        n = nn;
        ecnt = 2; dfs_clock = scc_cnt = 0;
        memset(head,0,sizeof(head));
        memset(pre,0,sizeof(pre));
        memset(sccno,0,sizeof(sccno));
    }

    void addEdge(int x, int y){//x, y clash
        to[ecnt] = y^1; next[ecnt] = head[x]; head[x] = ecnt++;
        to[ecnt] = x^1; next[ecnt] = head[y]; head[y] = ecnt++;
        //printf("%d<>%d\n",x,y);
    }

    bool solve(){
        for(int i = 0; i < n; ++i)
            if(!pre[i]) dfs(i);
        for(int i = 0; i < n; i += 2)
            if(sccno[i] == sccno[i^1]) return false;
        return true;
    }
} G;

const int MAXNN = 1010;

int a1[MAXNN], b1[MAXNN], a2[MAXNN], b2[MAXNN], a3[MAXNN], b3[MAXNN], c[MAXNN];

inline bool clash(int beg1, int end1, int beg2, int end2){
    if(end1 <= beg2 || end2 <= beg1) return false;
    return true;
}

int main(){
    int n;
    while(scanf("%d", &n)!=EOF){
        G.init(n*2);
        for(int i = 0; i < n; ++i) {
            scanf("%d:%d %d:%d %d", &a1[i], &a2[i], &b1[i], &b2[i], &c[i]);
            a3[i] = a1[i] * 60 + a2[i];
            b3[i] = b1[i] * 60 + b2[i];
        }
        for(int i = 0; i < n; ++i) for(int j = i+1; j < n; ++j) if(i != j){
            if(clash(a3[i], a3[i] + c[i], a3[j], a3[j] + c[j])) G.addEdge(i*2, j*2);
            if(clash(a3[i], a3[i] + c[i], b3[j] - c[j], b3[j])) G.addEdge(i*2, j*2+1);
            if(clash(b3[i] - c[i], b3[i], a3[j], a3[j] + c[j])) G.addEdge(i*2+1, j*2);
            if(clash(b3[i] - c[i], b3[i], b3[j] - c[j], b3[j])) G.addEdge(i*2+1, j*2+1);
        }
        if(G.solve()) printf("YES\n");
        else {printf("NO\n"); continue;}
        for(int i = 0; i < n; ++i){
            if(G.sccno[i * 2] < G.sccno[i * 2 + 1]) {
                b1[i] = a1[i]; b2[i] = a2[i] + c[i];
                while(b2[i] >= 60) ++b1[i], b2[i] -= 60;
            } else {
                a1[i] = b1[i]; a2[i] = b2[i] - c[i];
                while(a2[i] < 0) --a1[i], a2[i] += 60;
            }
            printf("%02d:%02d %02d:%02d\n", a1[i], a2[i], b1[i], b2[i]);
        }
    }
    return 0;
}
