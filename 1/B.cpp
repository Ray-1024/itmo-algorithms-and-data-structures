#include<iostream>
#include<vector>

bool isCage(const char &c) {
    return c >= 'A' && c <= 'Z';
}

bool isPair(const char &a, const char &b) {
    return isCage(a) ? (a - 'A') == (b - 'a') : (a - 'a') == (b - 'A');
}

int main() {
    std::string s;
    std::vector<std::pair<char, uint32_t> > stack;
    std::cin >> s;
    std::vector<uint32_t> cages(s.length() >> 1);
    for (uint32_t i = 0, animalID = 1, cageID = 0; i < s.length(); ++i) {
        if (stack.empty() || !isPair(stack.back().first, s[i]))
            stack.emplace_back(s[i], isCage(s[i]) ? (cageID++) : (animalID++));
        else {
            if (isCage(s[i]))
                cages[cageID++] = stack.back().second;
            else cages[stack.back().second] = animalID++;
            stack.pop_back();
        }
    }
    if (stack.empty()) {
        std::cout << "Possible\n";
        for (auto &i: cages)
            std::cout << i << ' ';
    } else std::cout << "Impossible";
    return 0;
}
