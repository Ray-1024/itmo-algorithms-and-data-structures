#include<iostream>
#include<vector>
#include <queue>

class Civilization {
private:
#define INF 1000000000
    using i32 = int32_t;

    i32 w{}, h{}, sx{}, sy{}, fx{}, fy{};
    std::vector<std::string> world;
    std::vector<std::vector<i32> > len;


    [[nodiscard]] bool checkCoords(const i32 &x, const i32 &y) const {
        return x >= 0 && x <= w && y >= 0 && y < h;
    }


    static i32 _x(const i32 &x, const i32 &i) {
        static const i32 dx[4] = {0, 1, 0, -1};
        return x + dx[i];
    }


    static i32 _y(const i32 &y, const i32 &i) {
        static const i32 dy[4] = {-1, 0, 1, 0};
        return y + dy[i];
    }


    static i32 cost(const uint8_t &ch) {
        switch (ch) {
            case '.':
                return 1;
            case 'W':
                return 2;
            default:
                return INF;
        }
    }


    void bfs() {
        len[sy][sx] = 0;
        std::queue<i32> q;
        q.push(sx);
        q.push(sy);

        while (!q.empty()) {
            i32 x = q.front();
            q.pop();
            i32 y = q.front();
            q.pop();
            for (int32_t i = 0; i < 4; ++i)
                if (checkCoords(_x(x, i), _y(y, i)) &&
                    len[_y(y, i)][_x(x, i)] > len[y][x] + cost(world[_y(y, i)][_x(x, i)])) {
                    len[_y(y, i)][_x(x, i)] = len[y][x] + cost(world[_y(y, i)][_x(x, i)]);
                    q.push(_x(x, i));
                    q.push(_y(y, i));
                }
        }
    }

    void path() {
        static const std::string directions = "SWNE";

        std::cout << len[fy][fx] << '\n';
        std::vector<uint8_t> ans;
        i32 x = fx, y = fy;

        do {
            for (int32_t i = 0; i < 4; ++i)
                if (checkCoords(_x(x, i), _y(y, i)) &&
                    len[_y(y, i)][_x(x, i)] == len[y][x] - cost(world[y][x])) {
                    ans.emplace_back(directions[i]);
                    x = _x(x, i);
                    y = _y(y, i);
                    break;
                }
        } while (len[y][x] > 0);
        for (i32 i = ans.size() - 1; i >= 0; --i)std::cout << ans[i];
    }

public:
    Civilization() {
        std::cin >> h >> w >> sy >> sx >> fy >> fx;
        --sx, --sy, --fx, --fy;
        world.resize(h);
        for (auto &line: world)std::cin >> line;

        len.resize(h, std::vector<i32>(w, INF));

        bfs();
        if (len[fy][fx] == INF)std::cout << "-1";
        else path();
    }

};

int main() {
    Civilization civilization;
    return 0;
}
