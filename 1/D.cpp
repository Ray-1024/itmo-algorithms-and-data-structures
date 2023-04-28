#include <iostream>
#include <cstdint>
#include<algorithm>
#include<vector>

int main() {
    int32_t a, b, c, d;
    int64_t k;
    std::cin >> a >> b >> c >> d >> k;
    std::vector<int32_t> lastVisit(d + 1);
    for (int32_t i = 1; k && a; ++i, --k) {
        if (lastVisit[a]) {
            k %= (int64_t) (i - lastVisit[a]);
            break;
        }
        lastVisit[a] = i;
        a = std::max(0, std::min(a * b - c, d));
    }
    for (; k && a; --k)
        a = std::max(0, std::min(a * b - c, d));
    std::cout << a;
    return 0;
}
