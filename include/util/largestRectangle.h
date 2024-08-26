#ifndef LARGEST_RECTANGLE_H
#define LARGEST_RECTANGLE_H

#include <vector>

namespace util {
    
/**
 * @brief Finds the largest rectangle in a histogram.
 * @param histogram A vector of integers representing the histogram.
 * @return A structure containing the lowest included index "from", the highest included index "to" and the area of the rectangle "area".
 */
extern auto largestRectInHisto(std::vector<int> histogram);

} // namespace util

#endif // LARGEST_RECTANGLE_H