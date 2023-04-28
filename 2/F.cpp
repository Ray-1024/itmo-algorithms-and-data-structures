#include<iostream>
#include<vector>
#include<algorithm>

int main() {
    std::vector<std::string> parts;
    for (std::string line; std::cin >> line;)
        parts.emplace_back(line);
    std::sort(parts.begin(), parts.end(), [](const std::string &a, const std::string &b) {
        return (a + b) > (b + a);
    });
    for (std::string &part: parts)
        std::cout << part;
    return 0;
}