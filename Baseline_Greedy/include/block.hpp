//
//  block.hpp
//  Baseline_Greedy
//
//  Created by SleepyFish on 2022/11/24.
//

#ifndef block_hpp
#define block_hpp

#include "global.hpp"
#include <vector>
#include <set>
using namespace std;
class Block {
public:
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    int flag;
    float weights;
    float edges;
    vector<float> row_weights;
    vector<float> col_weights;
    set<pair<int, int> > points;
    Block(int xmin = X_MIN, int xmax = X_MAX, int ymin = Y_MIN, int ymax = Y_MAX, int flag = -1);
    void SetWeights(float w);
    void SetEdges(float e);
    float GetWeights();
    float GetEdges();
    void AddPoint(pair<int, int> p);
    void DeletePoint(pair<int, int> p);
    
};

#endif /* block_hpp */
