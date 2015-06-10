#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int work(int a, int b) {
    int t = b % a;
    if(t == 0) return true;
    if(t + a == b) return !work(t, a);
    else return true;
}

int main() {
    int a, b;
    while(scanf("%d%d", &a, &b) != EOF) {
        if(a == 0 && b == 0) break;
        if(a > b) swap(a, b);
        puts(work(a, b) ? "Stan wins" : "Ollie wins");
    }
}
