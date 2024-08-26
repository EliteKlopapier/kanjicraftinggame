#include "largestRectangle.h"
#include <cstdlib>
#include <stack>

namespace util {

auto largestRectInHisto(std::vector<int> histogram) {
    size_t n = histogram.size();
    int* left = (int*)malloc(sizeof(int) * n);
    int* right = (int*)malloc(sizeof(int) * n);
    int* area = (int*)malloc(sizeof(int) * n);
    std::stack<int> indexStack;

    for(int i = 0; i < n; i++) {
        while(!indexStack.empty() && histogram[indexStack.top()] >= histogram[i]) {
            indexStack.pop();
        }
        left[i] = indexStack.empty() ? 0 : indexStack.top() + 1;
        indexStack.push(i);
    }

    while (!indexStack.empty()) {
        indexStack.pop();
    }

    for(int i = n - 1; i >= 0; i--) {
        while(!indexStack.empty() && histogram[indexStack.top()] >= histogram[i]) {
            indexStack.pop();
        }
        right[i] = indexStack.empty() ? n - 1 : indexStack.top() - 1;
        indexStack.push(i);
    }

    for(int i = 0; i < n; i++) {
        area[i] = histogram[i] * (right[i] - left[i] + 1);
    }

    int maxArea = 0;
    int from = 0;
    int to = 0;
    for(int i = 0; i < n; i++) {
        if(area[i] > maxArea) {
            maxArea = area[i];
            from = left[i];
            to = right[i];
        }
    }

    free(left);
    free(right);
    free(area);
    
    struct {
        int from;
        int to;
        int area;
    } result{from, to, maxArea};
    return result;
}

} // namespace util