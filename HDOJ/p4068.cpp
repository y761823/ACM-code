////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-30 18:54:38
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4068
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:348KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <string>
using namespace std;
typedef long long LL;
typedef map<string, int> Map;

const int MAXN = 7;

string name[MAXN], s;
bool mat[MAXN][MAXN];
int a[MAXN], b[MAXN];
int T, n, cnt;

void init() {
    memset(mat, 0, sizeof(mat));
    sort(name, name + n);
    //for(int i = 0; i < n; ++i) cout<<name[i]<<endl;
}

bool fight() {
    int i = 0, j = 0;
    while(i < n && j < n) {
        if(mat[b[j]][a[i]]) ++i;
        else ++j;
    }
    return i < n;
}

bool solve() {
    for(int i = 0; i < n; ++i) a[i] = i;
    while(true) {
        bool flag = true;
        for(int j = 0; j < n; ++j) b[j] = j;
        while(flag) {
            flag = fight();
            if(!next_permutation(b, b + n)) break;
        }
        if(flag) return true;
        if(!next_permutation(a, a + n)) break;
    }
    return false;
}

int main() {
    scanf("%d", &T);
    for(int kase = 1; kase <= T; ++kase) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) cin>>name[i];
        init();
        for(int j = 0, k; j < n; ++j) {
            scanf("%d", &k);
            while(k--) {
                cin>>s;
                for(int i = 0; i < n; ++i)
                    mat[j][i] |= (s == name[i]);
            }
        }
        if(!solve()) printf("Case %d: No\n", kase);
        else {
            printf("Case %d: Yes\n", kase);
            for(int i = 0; i < n - 1; ++i)
                cout<<name[a[i]]<<" ";
            cout<<name[a[n - 1]]<<"\n";
        }
    }
}