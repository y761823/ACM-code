#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iterator>
#include <vector>
using namespace std;

typedef long long LL;

LL modplus(LL a, LL b, LL mod) {
   LL res = a + b;
   return res < mod ? res : res - mod;
}

LL modminus(LL a, LL b, LL mod) {
   LL res = a - b;
   return res >= 0 ? res : res + mod;
}

LL mult(LL x, LL p, LL mod) {
    LL res = 0;
    while(p) {
        if(p & 1) res = modplus(res, x, mod);
        x = modplus(x, x, mod);
        p >>= 1;
    }
    return res;
}

LL power(LL x, LL p, LL mod) {
    LL res = 1;
    while(p) {
        if(p & 1) res = mult(res, x, mod);
        x = mult(x, x, mod);
        p >>= 1;
    }
    return res;
}

bool witness(LL n, LL p) {
   int t = __builtin_ctz(n - 1);
   LL x = power(p % n, (n - 1) >> t, n), last;
   while(t--) {
       last = x, x = mult(x, x, n);
       if(x == 1 && last != 1 && last != n - 1) return false;
   }
   return x == 1;
}

const int prime_n = 5;
int prime[prime_n] = {2, 3, 7, 61, 24251};

bool isPrime(LL n) {
   if(n == 1) return false;
   if(find(prime, prime + prime_n, n) != prime + prime_n) return true;
   if(n % 2 == 0) return false;
   for(int i = 0; i < prime_n; i++)
       if(!witness(n, prime[i])) return false;
   return true;
}

LL getDivisor(LL n) {
   int c = 1;
   while (true) {
       int i = 1, k = 2;
       LL x1 = 1, x2 = 1;
       while(true) {
           x1 = modplus(mult(x1, x1, n), c, n);
           LL d = __gcd(modminus(x1, x2, n), n);
           if(d != 1 && d != n) return d;
           if(x1 == x2) break;
           i++;
           if(i == k) x2 = x1, k <<= 1;
       }
       c++;
   }
}

void getFactor(LL n, vector<LL> &ans) {
    if(isPrime(n)) return ans.push_back(n);
    LL d = getDivisor(n);
    getFactor(d, ans);
    getFactor(n / d, ans);
}

int main() {
    int T; LL n;
    scanf("%d", &T);
    while(scanf("%I64d", &n) != EOF) {
        if(isPrime(n)) puts("Prime");
        else {
            vector<LL> ans;
            getFactor(n, ans);
            printf("%I64d\n", *min_element(ans.begin(), ans.end()));
        }
    }
}
