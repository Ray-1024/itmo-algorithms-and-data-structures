#include<iostream>
#include <set>
#include <vector>
#include <map>
#include <unordered_map>

class MyAllocator {
private:

    using ui32 = uint32_t;
    using block = std::pair<ui32, ui32>;

    std::unordered_map<ui32, ui32> blockLR;
    std::unordered_map<ui32, ui32> blockRL;
    std::map<ui32, std::unordered_map<ui32, ui32> > blocksBySize;

    std::unordered_map<ui32, block> blockByResponseNumber;
    uint32_t currentRequestNumber = 1;

    static ui32 blockSize(const block &b) {
        return b.second - b.first;
    }

    void eraseBlock(const block &curr) {
        blockLR.erase(curr.first);
        blockRL.erase(curr.second);
        blocksBySize[blockSize(curr)].erase(curr.first);
        if (blocksBySize[blockSize(curr)].empty())blocksBySize.erase(blockSize(curr));
    }

    void insertBlock(const block &curr) {
        blockLR[curr.first] = curr.second;
        blockRL[curr.second] = curr.first;
        blocksBySize[blockSize(curr)][curr.first] = curr.second;
    }

    block merge(const block &leftBlock, const block &rightBlock) {
        eraseBlock(leftBlock);
        eraseBlock(rightBlock);
        insertBlock({leftBlock.first, rightBlock.second});
        return {leftBlock.first, rightBlock.second};
    }

    block mergeIfBlockHasPreview(const block &curr) {
        if (blockRL.find(curr.first) == blockRL.end())return curr;
        return merge({blockRL[curr.first], curr.first}, curr);
    }

    block mergeIfBlockHasNext(const block &curr) {
        if (blockLR.find(curr.second) == blockLR.end()) return curr;
        return merge(curr, {curr.second, blockLR[curr.second]});
    }

public:

    explicit MyAllocator(const ui32 &initBlockSize, const ui32 &requestsCount = 0) {
        blockByResponseNumber.reserve(requestsCount);
        insertBlock({1, initBlockSize + 1});
    }

    ui32 allocate(const ui32 &query) {
        auto it = blocksBySize.lower_bound(query);
        if (it == blocksBySize.end()) {
            blockByResponseNumber[currentRequestNumber++] = {0, 0};
            return 0;
        }
        block curr = *it->second.begin();
        eraseBlock(curr);
        if (query < blockSize(curr))
            insertBlock(mergeIfBlockHasNext(mergeIfBlockHasPreview({curr.first + query, curr.second})));
        blockByResponseNumber[currentRequestNumber++] = {curr.first, curr.first + query};
        return curr.first;
    }

    void free(const ui32 &requestNumber) {
        ++currentRequestNumber;
        block curr = blockByResponseNumber[requestNumber];
        blockByResponseNumber.erase(requestNumber);
        if (curr.first == 0 || curr.second == 0)return;
        insertBlock(mergeIfBlockHasNext(mergeIfBlockHasPreview(curr)));
    }
};

int main() {
    uint32_t n, m;
    std::cin >> n >> m;
    MyAllocator myAllocator(n, m);

    for (int32_t query; m > 0; --m) {
        std::cin >> query;
        if (query >= 0) {
            uint32_t response = myAllocator.allocate(query);
            if (response == 0)std::cout << -1 << '\n';
            else std::cout << response << '\n';
        } else myAllocator.free(-query);
    }
    return 0;
}