#include <iostream>
#include<unordered_map>
#include <unordered_set>
#include<vector>
#include <algorithm>

bool isNumber(const std::string &str) {
    return std::all_of(str.begin() + (!str.empty() && str[0] == '-'), str.end(),
                       [](char curr) { return curr >= '0' && curr <= '9'; });
}

void
setValue(std::unordered_map<std::string, std::vector<std::string> > &vars,
         std::vector<std::unordered_set<std::string> > &stackFrames, const std::string &varName,
         const std::string &value) {
    if (stackFrames.back().find(varName) == stackFrames.back().end()) {
        stackFrames.back().insert(varName);
        vars[varName].emplace_back(value);
    } else vars[varName][vars[varName].size() - 1] = value;
}

int main() {
    std::string line;
    std::unordered_map<std::string, std::vector<std::string> > vars;
    std::vector<std::unordered_set<std::string> > stackFrames(1);

    while (std::cin >> line) {
        if (line == "{")
            stackFrames.emplace_back();
        else if (line == "}") {
            for (auto &varName: stackFrames.back()) {
                vars[varName].pop_back();
                if (vars[varName].empty())vars.erase(varName);
            }
            stackFrames.pop_back();
        } else {
            size_t splitIndex = line.find('=');
            std::string lVar = line.substr(0, splitIndex);
            std::string rVar = line.substr(splitIndex + 1);
            if (isNumber(rVar))
                setValue(vars, stackFrames, lVar, rVar);
            else {
                if (vars.find(rVar) == vars.end()) {
                    setValue(vars, stackFrames, lVar, "0");
                    std::cout << "0\n";
                } else {
                    setValue(vars, stackFrames, lVar, vars[rVar].back());
                    std::cout << vars[rVar].back() << '\n';
                }
            }
        }
    }
    return 0;
}
