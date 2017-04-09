class Solution {
    vector<vector<int>> edge;
    vector<int> degree;
public:
    vector<int> findOrder(int n, vector<pair<int, int>>& prerequisites) {
        edge.resize(n);
        degree.resize(n);
        for (auto& p : prerequisites) {
            edge[p.second].push_back(p.first);
            degree[p.first]++;
        }
        
        queue<int> que;
        for (int i = 0; i < n; ++i)
            if (!degree[i]) que.push(i);
            
        vector<int> res;
        while (!que.empty()) {
            int u = que.front(); que.pop();
            res.push_back(u);
            for (int v : edge[u])
                if (--degree[v] == 0) que.push(v);
        }
        return res.size() == n ? res : vector<int>();
    }
};
