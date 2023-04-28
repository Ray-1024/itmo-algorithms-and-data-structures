#include<iostream>
#include <vector>
#include <algorithm>


class LKSH {
private:
    using ui32 = uint32_t;
    using ui8 = uint8_t;

#define FIRST_COLOR 0
#define SECOND_COLOR 1
#define UNKNOWN_COLOR 2

    ui32 n, m;
    std::vector<std::vector<ui32> > g;
    std::vector<ui8> color;

    bool dfs(const ui32 &curr, const ui8 &col) {
        color[curr] = col;
        return std::none_of(g[curr].begin(), g[curr].end(), [this, &col](const auto &child) {
            return color[child] == col ||
                   (color[child] == UNKNOWN_COLOR && !dfs(child, (col == FIRST_COLOR) ? SECOND_COLOR : FIRST_COLOR));
        });
    }

public:
    LKSH() {
        std::cin >> n >> m;
        g.resize(n);
        color.resize(n, UNKNOWN_COLOR);

        for (ui32 a, b; m > 0 && std::cin >> a >> b; --m) {
            g[a - 1].emplace_back(b - 1);
            g[b - 1].emplace_back(a - 1);
        }

        for (ui32 i = 0; i < n; ++i)
            if (color[i] == UNKNOWN_COLOR && !dfs(i, FIRST_COLOR)) {
                std::cout << "NO";
                return;
            }
        std::cout << "YES";
    }
};


int main() {
    LKSH lksh;
    return 0;
}
