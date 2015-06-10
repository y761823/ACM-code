#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

map<string, int> mymap;

string str;
int cnt;

int main() {
    ios::sync_with_stdio(false);
    while(getline(cin, str)) {
        ++mymap[str];
        ++cnt;
    }
    map<string, int>::iterator it;
    cout.precision(4);
    for(it = mymap.begin(); it != mymap.end(); ++it) {
        cout<<it->first<<" "<<setiosflags(ios::fixed)<<it->second / double(cnt) * 100<<endl;
    }
}
