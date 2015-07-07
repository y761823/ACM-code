////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-07 10:49:22
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1093
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:296KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <cstring>
#include <numeric>
#include <vector>
using namespace std;
typedef long long LL;

int T, n;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        vector<int> vec(n);
        for(int i = 0; i < n; ++i)
            scanf("%d", &vec[i]);
        printf("%d\n", accumulate(vec.begin(), vec.end(), 0));
    }
}