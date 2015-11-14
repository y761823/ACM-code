#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

typedef long long LL;
const int MAXN = 108;

__gnu_pbds::cc_hash_table<int, int> dict_forward, dict_backward;
std::string a[100000], b[100000];
char str[MAXN];
std::string tmp1, tmp2;
int n;

int gethash(const std::string &str) {
    LL res = 0;
    for(char c : str)
        res = (res * 131 + c) % 1000000007;
    return res;
}

void myfind(const std::string &s, __gnu_pbds::cc_hash_table<int, int> &dict, std::string arr[]) {
    auto it = dict.find(gethash(s));
    if(it != dict.end()) {
        std::cout<<arr[it->second]<<std::endl;
    } else {
        puts("what?");
    }
}

int main() {
    int cnt = 0;
    while(gets(str) && strcmp(str, "@END@") != 0) {
        int pos = strchr(str, ']') - str;
        a[cnt] = std::string(str + 1, pos - 1);
        b[cnt] = std::string(str + pos + 2);
        dict_forward[gethash(a[cnt])] = cnt;
        dict_backward[gethash(b[cnt])] = cnt;
        cnt++;
    }
    scanf("%d", &n); getchar();
    for(int i = 0; i < n; ++i) {
        gets(str);
        if(*str == '[') {
            tmp1 = std::string(str + 1, strlen(str) - 2);
            myfind(tmp1, dict_forward, b);
        } else {
            myfind(str, dict_backward, a);
        }
    }
}
