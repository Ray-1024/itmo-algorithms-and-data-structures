#include<iostream>
#include<vector>
#include<algorithm>

struct LetterData {
    char letter;
    uint32_t count = 0;
    uint32_t weight;
};

std::vector<LetterData> readLettersData(const std::string &word) {
    std::vector<LetterData> letters(26);
    for (char c = 'a'; c <= 'z'; ++c) {
        letters[c - 'a'].letter = c;
        std::cin >> letters[c - 'a'].weight;
    }
    for (const char &currChar: word)
        ++letters[currChar - 'a'].count;
    return letters;
}

uint32_t getCountLettersIsBiggerThanOne(const std::vector<LetterData> &letters) {
    return std::count_if(letters.begin(), letters.end(), [](const LetterData &letter) { return letter.count > 1; });
}

void fillAnswer(std::vector<LetterData> &letters, std::string &word, uint32_t countLettersIsBiggerThanOne) {
    for (uint32_t i = 0; i < countLettersIsBiggerThanOne; ++i) {
        word[i] = letters[letters.size() - 1 - i].letter;
        word[word.length() - 1 - i] = word[i];
        letters[letters.size() - 1 - i].count -= 2;
    }
    for (uint32_t i = countLettersIsBiggerThanOne; i < word.length() - countLettersIsBiggerThanOne; ++i) {
        while (!letters.back().count)letters.pop_back();
        word[i] = letters.back().letter;
        --letters.back().count;
    }
}

int main() {
    std::string word;
    std::cin >> word;
    std::vector<LetterData> letters = readLettersData(word);
    std::stable_sort(letters.begin(), letters.end(), [](const LetterData &a, const LetterData &b) {
        return (a.weight * (a.count > 1)) < (b.weight * (b.count > 1));
    });
    fillAnswer(letters, word, getCountLettersIsBiggerThanOne(letters));
    std::cout << word;
    return 0;
}