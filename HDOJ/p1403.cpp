////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 20:43:15
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1403
////Problem Title: 
////Run result: Accept
////Run time:62MS
////Run memory:4448KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 200005
char S[MAXN], s2[MAXN];
int n, sa[MAXN], height[MAXN], rank[MAXN], tmp[MAXN], c[MAXN];
int apart;

void makesa(int m) { // O(MAXN * log MAXN)
    int i, j, k;
    memset(c, 0, m * sizeof(int));
    for(i = 0; i < n ; ++i) ++c[rank[i] = S[i]];
    for(i = 1; i < m; ++i) c[i] += c[i - 1];
    for(i = 0; i < n ; ++i) sa[--c[rank[i]]] = i;
	for(k = 1; k < n; k <<= 1) {
        for(i = 0; i < n; ++i) {
            j = sa[i] - k;
            if(j < 0) j += n;
            tmp[c[rank[j]]++] = j;
        }
        sa[tmp[c[0] = 0]] = j = 0;
        for(i = 1; i < n; i++) {
            if(rank[tmp[i]] != rank[tmp[i-1]] || rank[tmp[i] + k] != rank[tmp[i - 1] + k])
                c[++j] = i;
            sa[tmp[i]] = j;
        }
        memcpy(rank, sa, n * sizeof(int));
        memcpy(sa, tmp, n * sizeof(int));
        if(j >= n - 1) break;
    }
}

void calheight() {
    int i, j, k = 0;
    for(i = 0; i < n; height[rank[i++]] = k) {
        if(k > 0) --k;
        for(j = sa[rank[i] - 1]; S[i + k] == S[j + k]; ++k) ;
    }
}

int main() {
	while(scanf("%s%s", S, s2) != EOF) {
		apart = strlen(S);
		strcat(S, "*");
		strcat(S, s2);
		n = strlen(S);
		makesa(1 << 8);
		calheight();
		int ans = 0;
		for (int i = 1; i < n; ++i)
			if((sa[i - 1] < apart && sa[i] > apart) || (sa[i - 1] > apart && sa[i] < apart))
                if (height[i] > ans) ans = height[i];
                printf("%d\n",ans);
	}
	return 0;
}