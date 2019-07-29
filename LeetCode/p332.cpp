class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (const auto& edge : tickets)
            adj[edge.front()].insert(edge.back());
        dfs("JFK");
        reverse(res.begin(), res.end());
        return std::move(res);
    }
    
    void dfs(const string& from) {
        auto& nexts = adj[from];
        while (!nexts.empty()) {
            string to = *nexts.begin();
            nexts.erase(nexts.begin());
            dfs(to);
        }
        res.push_back(from);
    }
    
private:
    unordered_map<string, multiset<string>> adj;
    vector<string> res;
};
