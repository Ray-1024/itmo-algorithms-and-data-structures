#include <iostream>
#include <vector>
#include <algorithm>

class AirBubundia {
private:
    using ui32 = uint32_t;

    ui32 n, tmp;
    std::vector<std::vector<ui32>> g;
    std::vector<bool> used;

    void dfs(const ui32 &v, const ui32 &volume, const bool &invDfs = false) {
        used[v] = true;
        ++tmp;
        for (ui32 u = 0; u < n; ++u)
            if (!used[u] && ((invDfs ? g[u][v] : g[v][u]) <= volume)) dfs(u, volume, invDfs);
    }


    bool check(const ui32 &currentVolume) {
        used.assign(n, false);
        tmp = 0;
        dfs(0, currentVolume);
        if (tmp != n) return false;

        used.assign(n, false);
        tmp = 0;
        dfs(0, currentVolume, true);
        return (tmp == n);
    }

    ui32 findMinVolume() {
        ui32 l = 0, r = tmp, m;
        while (r - l > 1) {
            m = (l + r) / 2;
            if (check(m))r = m;
            else l = m;
        }
        if (check(l))return l;
        return r;
    }

public:
    AirBubundia() {
        std::cin >> n;

        g.resize(n, std::vector<ui32>(n));
        used.resize(n);

        for (auto &i: g)
            for (auto &j: i)
                std::cin >> j, tmp = std::max(tmp, j);

        std::cout << findMinVolume();
    }
};

int main() {
    AirBubundia airBubundia;
    return 0;
}
