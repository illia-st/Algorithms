#include <iostream>
#include <vector>

class Solution {
public:
    int maxIncreaseKeepingSkyline(std::vector<std::vector<int>>& grid) {
        size_t N {grid.size()};
        std::vector<int> max_rows(N), max_cols(N);
        // find rows and columns maximum values
        for(size_t i {}; i < N; ++i){
            int max_value {grid[i][0]};
            for(size_t j{ }; j < N; ++j){
                max_value = std::max(max_value, grid[i][j]);
            }
            max_rows[i] = max_value;
            max_value = {grid[0][i]};
            for(size_t j {}; j < N; ++j){
                max_value = std::max(max_value, grid[j][i]);
            }
            max_cols[i] = max_value;
        }
        // then we can easily iterate through the matrix and find tha answer
        int ans {};
        for(size_t i {}; i < N; ++i){
            for(size_t j {}; j < N; ++j){
                ans += (std::min(max_rows[i], max_cols[j]) - grid[i][j]);
            }
        }
        return ans;
    }
};

int main() {
    Solution sl;
    std::vector<std::vector<int>> grid{
            {3, 0, 8, 4},
            {2, 4, 5, 7},
            {9, 2, 6, 3},
            {0, 3, 1, 0}
    };
    std::cout << sl.maxIncreaseKeepingSkyline(grid) << std::endl;

    return 0;
}
