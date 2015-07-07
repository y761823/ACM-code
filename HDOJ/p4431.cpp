////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-10-03 17:28:39
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4431
////Problem Title: 
////Run result: Accept
////Run time:265MS
////Run memory:364KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 13;

struct TILES {
    int P[MAXN], M[MAXN], S[MAXN], C[MAXN];

    void init() {
        #define CL(a) memset(a, 0, sizeof(a))
        CL(P), CL(M), CL(S), CL(C);
    }

    void read() {
        char str[5];
        for(int i = 0; i < 13; ++i) {
            scanf("%s", str);
            switch(str[1]) {
                case 'p':++P[str[0] - '0'];break;
                case 'm':++M[str[0] - '0'];break;
                case 's':++S[str[0] - '0'];break;
                case 'c':++C[str[0] - '0'];break;
            }
        }
    }

    bool special_judge1() {
        int cnt = 0;
        for(int i = 1; i <= 9; ++i) {
            cnt += (M[i] == 2);
            cnt += (S[i] == 2);
            cnt += (P[i] == 2);
            cnt += (C[i] == 2);
        }
        return cnt == 7;
    }

    bool special_judge2() {
        bool eyes = false;
        for(int i = 1; i <= 7; ++i) {
            if(C[i] == 0 || C[i] > 2) return false;
            if(C[i] == 2) eyes = true;
        }
        if(M[1] == 0 || M[1] > 2) return false;
        if(M[9] == 0 || M[9] > 2) return false;
        if(S[1] == 0 || S[1] > 2) return false;
        if(S[9] == 0 || S[9] > 2) return false;
        if(P[1] == 0 || P[1] > 2) return false;
        if(P[9] == 0 || P[9] > 2) return false;
        if(M[1] == 2 || M[9] == 2) eyes = true;
        if(S[1] == 2 || S[9] == 2) eyes = true;
        if(P[1] == 2 || P[9] == 2) eyes = true;
        return eyes;
    }

    int UP[MAXN], UM[MAXN], US[MAXN];

    bool isWin() {
        int x;
        for(int i = 1; i <= 9; ++i) {
            if(P[i] - UP[i] >= 3) UP[i] += 3;
            if(S[i] - US[i] >= 3) US[i] += 3;
            if(M[i] - UM[i] >= 3) UM[i] += 3;
            x = P[i] - UP[i];
            if(x != 0) {
                UP[i] += x;
                if((UP[i + 1] += x) > P[i + 1]) return false;
                if((UP[i + 2] += x) > P[i + 2]) return false;
            }
            x = S[i] - US[i];
            if(x != 0) {
                US[i] += x;
                if((US[i + 1] += x) > S[i + 1]) return false;
                if((US[i + 2] += x) > S[i + 2]) return false;
            }
            x = M[i] - UM[i];
            if(x != 0) {
                UM[i] += x;
                if((UM[i + 1] += x) > M[i + 1]) return false;
                if((UM[i + 2] += x) > M[i + 2]) return false;
            }
        }
        return true;
    }

    bool judge() {
        if(special_judge1() || special_judge2()) return true;
        bool eyes = false;
        for(int i = 1; i <= 7; ++i) {
            if(C[i] == 2) {
                if(!eyes) eyes = true;
                else return false;
            }
            if(C[i] == 1 || C[i] == 4) return false;
        }
        if(eyes) {
            CL(UP), CL(UM), CL(US);
            return isWin();
        }
        for(int i = 1; i <= 9; ++i) {
            if(P[i] >= 2) {
                CL(UP), CL(UM), CL(US);
                UP[i] = 2;
                if(isWin()) return true;
            }
        }
        for(int i = 1; i <= 9; ++i) {
            if(S[i] >= 2) {
                CL(UP), CL(UM), CL(US);
                US[i] = 2;
                if(isWin()) return true;
            }
        }
        for(int i = 1; i <= 9; ++i) {
            if(M[i] >= 2) {
                CL(UP), CL(UM), CL(US);
                UM[i] = 2;
                if(isWin()) return true;
            }
        }
        return false;
    }

    vector<int> ans2;
    vector<char> ans1;

    void solve() {
        ans1.clear();
        ans2.clear();
        for(int i = 1; i <= 9; ++i) {
            ++M[i];
            if(M[i] <= 4 && judge()) {
                ans1.push_back('m');
                ans2.push_back(i);
            }
            --M[i];
        }
        for(int i = 1; i <= 9; ++i) {
            ++S[i];
            if(S[i] <= 4 && judge()) {
                ans1.push_back('s');
                ans2.push_back(i);
            }
            --S[i];
        }
        for(int i = 1; i <= 9; ++i) {
            ++P[i];
            if(P[i] <= 4 && judge()) {
                ans1.push_back('p');
                ans2.push_back(i);
            }
            --P[i];
        }
        for(int i = 1; i <= 7; ++i) {
            ++C[i];
            if(C[i] <= 4 && judge()) {
                ans1.push_back('c');
                ans2.push_back(i);
            }
            --C[i];
        }
    }

    void print() {
        int len = ans1.size();
        if(len == 0) {
            puts("Nooten");
            return ;
        }
        printf("%d", len);
        for(int i = 0; i < len; ++i)
            printf(" %d%c", ans2[i], ans1[i]);
        puts("");
    }
} G;

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        G.init();
        G.read();
        G.solve();
        G.print();
    }
}
