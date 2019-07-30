class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int n = equations.size();
        init(2 * n);
        
        for (int i = 0; i < n; ++i) {
            string a = equations[i].front(), b = equations[i].back();
            if (order.find(a) == order.end())
                order.insert(make_pair(a, order.size()));
            if (order.find(b) == order.end())
                order.insert(make_pair(b, order.size()));
            
            if (values[i] == 0)
                mul[order[a]] = 0;
            else
                merge(order[a], order[b], values[i]);
        }
        
        vector<double> res;
        for (auto& vec : queries) {
            res.push_back(count(vec.front(), vec.back()));
        }
        return res;
    }
    
private:
    double count(string sx, string sy) {
        if (order.find(sx) == order.end())
            return -1;
        if (order.find(sy) == order.end())
            return -1;
        return count(order[sx], order[sy]);
    }
    
    double count(int x, int y) {
        if (mul[y] == 0)
            return -1;
        if (mul[x] == 0)
            return 0;
        int fx = find_fa(x), fy = find_fa(y);
        return fx == fy ? mul[x] / mul[y] : -1;
    }
    
    void init(int n) {
        fa.reset(new int[n]);
        mul.reset(new double[n]);
        for (int i = 0; i < n; ++i) {
            fa[i] = i;
            mul[i] = 1;
        }
    }
    
    int find_fa(int x) {
        if (x == fa[x])
            return x;
        int ffa = find_fa(fa[x]);
        // ffa = fa / mul[fa], fa = a / mul[a]
        mul[x] *= mul[fa[x]];
        return fa[x] = ffa;
    }
    
    void merge(int x, int y, double div) {
        int fx = find_fa(x), fy = find_fa(y);
        if (fx != fy) {
            // x = y * div, fx = x / mul[x], fy = y / mul[y]
            // fx = fy * mul[y] * div / mul[x]
            mul[fy] = mul[x] / (mul[y] * div);
            fa[fy] = fx;
        }
    }
    
    std::unique_ptr<int[]> fa;
    std::unique_ptr<double[]> mul;
    unordered_map<string, int> order;
};
