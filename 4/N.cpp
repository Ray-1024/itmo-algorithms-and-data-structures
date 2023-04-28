#include<iostream>
#include <vector>
#include <set>


class PiggyBanks {
private:
    using ui32 = uint32_t;

    ui32 n;
    std::vector<std::vector<ui32> > g;
    std::vector<ui32> color;

    void dfs(const ui32 &curr, const ui32 &col) {
        color[curr] = col;
        for (auto &child: g[curr])
            if (color[child] != col)
                dfs(child, col);
    }

public:
    PiggyBanks() {
        std::cin >> n;
        g.resize(n);
        color.resize(n);

        for (ui32 i = 0, where; i < n && std::cin >> where; ++i)
            g[where - 1].emplace_back(i);

        for (ui32 i = 0; i < n; ++i)
            if (color[i] == 0)dfs(i, i + 1);

        std::cout << std::set<ui32>(color.begin(), color.end()).size();
    }
};


int main() {
    PiggyBanks piggyBanks;
    return 0;
}
