#include<iostream>
#include<vector>

bool check(const std::vector<uint32_t> &stalls, uint32_t cows, const uint32_t &minDistance) {
    --cows;
    for (uint32_t i = 1, last = stalls[0]; i < stalls.size(); ++i)
        if (stalls[i] - last >= minDistance) {
            last = stalls[i];
            if (!(--cows))return true;
        }
    return false;
}

uint32_t findMinDistance(const std::vector<uint32_t> &stalls, const uint32_t &cows) {
    uint32_t l = 0, r = stalls.back(), m;
    while (r - l > 1) {
        m = (l + r) >> 1;
        if (check(stalls, cows, m))l = m;
        else r = m;
    }
    if (check(stalls, cows, r))return r;
    return l;
}

int main() {
    uint32_t n, cows;
    std::cin >> n >> cows;
    std::vector<uint32_t> stalls(n);
    for (uint32_t &stall: stalls)
        std::cin >> stall;
    std::cout << findMinDistance(stalls, cows);
    return 0;
}
