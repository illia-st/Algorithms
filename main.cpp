#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>

struct Point{
    int x;
    int y;
    bool left {};
    bool operator < (const Point& rhs) const{
        if(this->x == rhs.x && this->y == rhs.y){
            return left;
        }
        if(this->x == rhs.x){
            // first will be a higher point
            return this->y > rhs.y;
        }
        return this->x < rhs.x;
    }
    bool operator == (const Point& rhs) const{
        return this->x == rhs.x && this->y == rhs.y;
    }
};

std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>>& buildings){
    std::vector<std::vector<int>> skyline;

    std::multiset<Point> building_edges;
    size_t N {buildings.size()};
    for(const auto& bld: buildings){
        building_edges.insert(Point{bld[0], bld[2], true});
        building_edges.insert(Point{bld[1], bld[2], false});
    }
    // perform sweeping line
    std::multiset<int> unfinished_heights {};
    for(auto& point: building_edges){
        if(point.left && !unfinished_heights.empty()){
            // if new started line is higher than the highest
            if(point.y > *unfinished_heights.rbegin()){
                // then we need to add a new point to skyline
                skyline.push_back({point.x, point.y});
            }
            // add a new line to unfinished heights
            unfinished_heights.insert(point.y);
        }
        else if(point.left){
            skyline.push_back({point.x, point.y});
            unfinished_heights.insert(point.y);
        }
        else if(!point.left){
            // erase 1 unfinished height
            auto it = unfinished_heights.find(point.y);
            // check if the found value belongs to the highest roof
            int removed_value = *it;
            it = unfinished_heights.erase(it);
            // it is necessary to receive the last iterator
            // because in this case we can add a new point to the skyline
            if(it == unfinished_heights.end()){
                if(removed_value == skyline.back().back() && point.x == skyline.back().front()){
                    skyline.back().back() = (unfinished_heights.empty() ? 0 : *unfinished_heights.rbegin());
                }
                else if(unfinished_heights.empty()){
                    skyline.push_back({point.x, 0});
                }
                else{
                    skyline.push_back({point.x, *unfinished_heights.rbegin()});
                }
            }
            // we have other 2 cases
            // 1) if not the last element was removed
            // 2) or there is another the highest building in the multiset
        }
    }
    return skyline;
}


int main() {
    std::vector<std::vector<int>> buildings {
            {2, 9, 10},
            { 3, 7, 15 },
            { 5, 12, 12 },
            { 15, 20, 10 },
            { 19, 24, 8 }
    };
    std::vector<std::vector<int>> buildings2 {
            {0, 2, 3},
            {2, 5, 3}
    };
    std::vector<std::vector<int>> buildings3 {
            {4, 9, 10}, {4, 9, 15}, {4, 9, 12}, {10, 12, 10}, {10, 12, 8}
    };
    auto ans {getSkyline(buildings3)};
    for(const auto& point: ans){
        std::cout << "X - " << point.front() << "\n Y - " << point.back() << std::endl;
    }
    return 0;
}
