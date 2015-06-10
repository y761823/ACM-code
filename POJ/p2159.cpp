#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

char s1[105], s2[105];

int main() {
    scanf("%s%s", s1, s2);
    vector<int> c1(26), c2(26);
    for(char *c = s1; *c; ++c) c1[*c - 'A']++;
    for(char *c = s2; *c; ++c) c2[*c - 'A']++;
    sort(c1.begin(), c1.end());
    sort(c2.begin(), c2.end());
    puts(c1 == c2 ? "YES" : "NO");
}
