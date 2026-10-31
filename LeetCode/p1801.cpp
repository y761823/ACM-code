class Solution {
public:
    enum Type : int {
        BUY,
        SELL,
    };

    // price, amount
    std::multimap<int, int> sells;
    std::multimap<int, int, std::greater<int>> buys;

    int getNumberOfBacklogOrders(std::vector<std::vector<int>>& orders) {
        for (auto &order : orders) {
            int price = order[0];
            int amount = order[1];
            int type = order[2];

            if (type == BUY) {
                auto it = sells.begin();
                while (it != sells.end() && amount > 0 && price >= it->first) {
                    if (amount < it->second) {
                        it->second -= amount;
                        amount = 0;
                    } else {
                        amount -= it->second;
                        it = sells.erase(it);
                    }
                }
                if (amount > 0) {
                    buys.emplace(price, amount);
                }
            } else {
                auto it = buys.begin();
                while (it != buys.end() && amount > 0 && price <= it->first) {
                    if (amount < it->second) {
                        it->second -= amount;
                        amount = 0;
                    } else {
                        amount -= it->second;
                        it = buys.erase(it);
                    }
                }
                if (amount > 0) {
                    sells.emplace(price, amount);
                }
            }
        }

        long long backlog = 0;
        for (auto [_, amount] : buys) {
            backlog += amount;
        }
        for (auto [_, amount] : sells) {
            backlog += amount;
        }
        int mod = 1'000'000'007;
        return backlog % mod;
    }
};
