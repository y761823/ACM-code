/*
ID: y7618231
PROG: transform
LANG: C++
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef vector<vector<char> > Mat;

Mat src, tar;
int n;

Mat rotate90(const Mat &src) {
    Mat res = src;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            res[j][n - i - 1] = src[i][j];
    return res;
}

Mat rotate180(const Mat &src) {
    return rotate90(rotate90(src));
}

Mat rotate270(const Mat &src) {
    return rotate90(rotate90(rotate90(src)));
}

Mat reflection(const Mat &src) {
    Mat res = src;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n / 2; ++j)
            swap(res[i][j], res[i][n - j - 1]);
    return res;
}

int solve() {
    if(rotate90(src) == tar) return 1;
    if(rotate180(src) == tar) return 2;
    if(rotate270(src) == tar) return 3;
    Mat tmp = reflection(src);
    if(tmp == tar) return 4;
    if(rotate90(tmp) == tar || rotate180(tmp) == tar || rotate270(tmp) == tar) return 5;
    if(src == tar) return 6;
    return 7;
}

int main() {
#ifndef OYK_JUDGE
    freopen("transform.in", "r", stdin); freopen("transform.out", "w", stdout);
#endif
    scanf("%d", &n);
    tar = src = Mat(n, vector<char>(n));
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) scanf(" %c", &src[i][j]);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) scanf(" %c", &tar[i][j]);
    printf("%d\n", solve());
}
