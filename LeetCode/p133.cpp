/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
    unordered_map<int, UndirectedGraphNode*> m_map;
    
    UndirectedGraphNode* dfs(UndirectedGraphNode* p) {
        auto it = m_map.find(p->label);
        if (it != m_map.end()) {
            return it->second;
        } else {
            UndirectedGraphNode* newp = new UndirectedGraphNode(p->label);
            m_map.insert(make_pair(p->label, newp));
            for (auto s : p->neighbors)
                newp->neighbors.push_back(dfs(s));
            return newp;
        }
    }
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        return node ? dfs(node) : node;
    }
};
