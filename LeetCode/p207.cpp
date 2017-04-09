class Solution {
    vector<vector<int>> edge;
    vector<int> degree;
public:
    bool canFinish(int n, vector<pair<int, int>>& prerequisites) {
        edge.resize(n);
        degree.resize(n);
        for (auto& p : prerequisites) {
            edge[p.first].push_back(p.second);
            degree[p.second]++;
        }
        
        queue<int> que;
        for (int i = 0; i < n; ++i)
            if (!degree[i]) que.push(i);
        while (!que.empty()) {
            int u = que.front(); que.pop();
            for (int v : edge[u])
                if (--degree[v] == 0) que.push(v);
        }
        return all_of(degree.begin(), degree.end(), [](int u) {
            return u == 0;
        });
    }
};
