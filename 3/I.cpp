#include <deque>
#include <iostream>
#include <vector>
#include <set>

uint32_t getCarPosition(const std::vector<std::deque<uint32_t>> &carPositions, uint32_t car) {
    return carPositions[car].empty() ? UINT32_MAX : carPositions[car].front();
}

int main() {
    uint32_t n, k, p, ans = 0;
    std::cin >> n >> k >> p;

    std::vector<uint32_t> requestedCar(p);
    std::vector<bool> isCarOnTheFloor(n);
    std::vector<std::deque<uint32_t>> carPositions(n);
    std::set<std::pair<uint32_t, uint32_t>> nextCarPosition;

    for (uint32_t i = 0; i < p && std::cin >> requestedCar[i]; ++i)
        carPositions[--requestedCar[i]].push_back(i);

    for (const uint32_t &car: requestedCar) {
        if (!isCarOnTheFloor[car]) {
            carPositions[car].pop_front();
            if (nextCarPosition.size() == k) {
                isCarOnTheFloor[nextCarPosition.rbegin()->second] = false;
                nextCarPosition.erase(*nextCarPosition.rbegin());
            }
            isCarOnTheFloor[car] = true;
            nextCarPosition.insert({getCarPosition(carPositions, car), car});
            ++ans;
        } else {
            nextCarPosition.erase({getCarPosition(carPositions, car), car});
            carPositions[car].pop_front();
            nextCarPosition.insert({getCarPosition(carPositions, car), car});
        }
    }
    std::cout << ans;
    return 0;
}
