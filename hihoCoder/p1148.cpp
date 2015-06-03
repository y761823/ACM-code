#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

string month[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November" , "December"};
int T, n;

int get_month(string s) {
    return find(month, month + 12, s) - month + 1;
}

int calc(int y) {
    return y / 4 - y / 100 + y / 400;
}

char str[15];
int yy, dd, mm;

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%s %d, %d", str, &dd, &yy);
        mm = get_month(str);
        int a = calc(yy + (mm > 2) - 1);

        scanf("%s %d, %d", str, &dd, &yy);
        mm = get_month(str);
        int b = calc(yy - (mm < 2 || (mm == 2 && dd < 29)));
        printf("Case #%d: %d\n", t, b - a);
    }
}
