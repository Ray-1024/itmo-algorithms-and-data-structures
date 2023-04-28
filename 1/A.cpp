#include<iostream>

int main() {
    uint32_t n, answerLeft = 1, answerRight = 1;
    std::cin >> n;
    for (uint32_t currLeft = 1, currRight = 1, currFlower, previousFlower = 0, beforePreviousFlower = 0;
         currRight <= n; ++currRight, beforePreviousFlower = previousFlower, previousFlower = currFlower) {
        std::cin >> currFlower;
        if (currFlower == previousFlower && previousFlower == beforePreviousFlower)
            currLeft = currRight - 1;
        if (currRight - currLeft > answerRight - answerLeft)
            answerLeft = currLeft, answerRight = currRight;
    }
    std::cout << answerLeft << ' ' << answerRight;
    return 0;
}
