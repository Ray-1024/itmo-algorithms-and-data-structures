#include<iostream>
#include<deque>

int main() {
    uint32_t n;
    char command;
    std::deque<uint32_t> leftHalf, rightHalf;
    std::cin >> n;
    for (uint32_t i = 0, curr; i < n && std::cin >> command; ++i) {
        if (command == '-') {
            std::cout << leftHalf.front() << '\n';
            leftHalf.pop_front();
        } else {
            std::cin >> curr;
            if (command == '+') rightHalf.push_back(curr);
            else rightHalf.push_front(curr);
        }
        if (!rightHalf.empty() && rightHalf.size() > leftHalf.size()) {
            leftHalf.push_back(rightHalf.front());
            rightHalf.pop_front();
        }
    }
    return 0;
}
