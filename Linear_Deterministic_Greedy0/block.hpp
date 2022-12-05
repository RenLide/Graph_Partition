//
//  block.hpp
//  Linear_Deterministic_Greedy
//
//  Created by SleepyFish on 2022/10/25.
//

#ifndef block_hpp
#define block_hpp

#include <iostream>
#include <set>
using namespace std;
class Block {
private:
    float weights;
    float edges;
public:
    set<pair<int, int>> points;
    Block();
    void AddPoint(pair<int, int> p);
    void DeletePoint(pair<int, int> p);
    void SetWeights(float w);
    void SetEdges(float e);
    float GetWeights();
    float GetEdges();
};
#endif /* block_hpp */
