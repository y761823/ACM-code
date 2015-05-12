#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
typedef long long LL;

class CatsOnTheLineDiv2 {
public:
    string getAnswer(vector <int> position, vector <int> count, int time) {
        int n = position.size();
        vector<pair<int, int> > a;
        for(int i = 0; i < n; ++i)
            a.push_back(make_pair(position[i], count[i]));
        sort(a.begin(), a.end());

        int left = -10000;
        for(int i = 0; i < n; ++i) {
            int tmp = max(left, a[i].first - time) + a[i].second - 1;
            if(a[i].first + time < tmp) return "Impossible";
            left = tmp + 1;
        }
        return "Possible";
    }
};
