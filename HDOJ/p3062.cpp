////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-07-07 23:43:21
////Compiler: Visual C++
//////////////////////////////////////////////////////
////Problem ID: 3062
////Problem Title: 
////Run result: Accept
////Run time:312MS
////Run memory:844KB
//////////////////System Comment End//////////////////
#include <cstdio>
 #include <cstring>
 using namespace std;

 const int MAXN = 2010;
 const int MAXM = 1010*1010*2;

 struct TwoSAT{
     int n, ecnt, dfs_clock, scc_cnt;
     int St[MAXN], c;//ÊÖ¶¯Õ»
     int head[MAXN], lowlink[MAXN], pre[MAXN], sccno[MAXN];
     int next[MAXM], to[MAXM];

     void dfs(int u){
         pre[u] = lowlink[u] = ++dfs_clock;
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
             scc_cnt++;
             while(true){
                 int x = St[c--];
                 sccno[x] = scc_cnt;
                 if(x == u) break;
             }
         }
     }

     void init(int n){
         this->n = n;
         ecnt = 2; dfs_clock = scc_cnt = 0;
         memset(head,0,sizeof(head));
         memset(sccno,0,sizeof(sccno));
         memset(pre,0,sizeof(pre));
     }

     void addEdge1(int x, int y){//x*y=false
         to[ecnt] = y^1; next[ecnt] = head[x]; head[x] = ecnt++;
         to[ecnt] = x^1; next[ecnt] = head[y]; head[y] = ecnt++;
     }

     bool solve(){
         int i;
         for(i = 0; i < n; ++i)
             if(!pre[i]) dfs(i);
         for(i = 0; i < n; i += 2)
             if(sccno[i] == sccno[i^1]) return false;
         return true;
     }
 } G;

 int main(){
     int n, m, a, b, c, d;
     while(scanf("%d%d",&n,&m)!=EOF){
         G.init(2*n);
         while(m--){
             scanf("%d%d%d%d",&a,&b,&c,&d);
             G.addEdge1(a*2 + c, b*2 + d);
         }
         if(G.solve()) printf("YES\n");
         else printf("NO\n");
     }
     return 0;
 }
