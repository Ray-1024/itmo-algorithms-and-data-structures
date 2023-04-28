#include<iostream>
#include<vector>
#include<deque>

int main() {
    int32_t n, k;
    std::cin >> n >> k;
    std::deque<std::pair<int32_t, int32_t>> minimums;
    for (int32_t curr, i = 0; i < n && std::cin >> curr; ++i) {
        while (!minimums.empty() && minimums.back().first >= curr)
            minimums.pop_back();
        minimums.emplace_back(curr, i);
        if (minimums.front().second <= i - k)minimums.pop_front();
        if (i >= k - 1)std::cout << minimums.front().first << ' ';
    }
    return 0;
}
