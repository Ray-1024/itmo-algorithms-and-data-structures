#include<iostream>
#include<vector>
#include<algorithm>

int main() {
    uint32_t n, k, sum = 0;
    std::cin >> n >> k;
    std::vector<uint32_t> items(n);
    for (uint32_t &currItem: items) {
        std::cin >> currItem;
        sum += currItem;
    }
    std::stable_sort(items.begin(), items.end());
    for (; n >= k; n -= k)
        sum -= items[n - k];
    std::cout << sum;
    return 0;
}
